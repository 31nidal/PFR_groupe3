#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>

#include "commande_vocale.h"

/* ===================== CONFIG ===================== */

#define CONFIG_DIR "config"
#define FICHIER_COMMANDE "commande.txt"
#define FICHIER_ACTION   "action.txt"

#define MAX_JSON     8192
#define MAX_CMD      512
#define MAX_WORDS    64
#define MAX_ACTIONS  32

/* ===================== ACTIONS ABSTRAITES ===================== */

typedef enum {
    ACTION_ADVANCE,
    ACTION_RETREAT,
    ACTION_TURN_LEFT,
    ACTION_TURN_RIGHT,
    ACTION_STOP
} ActionType;

typedef struct {
    ActionType actions[MAX_ACTIONS];
    int count;
} ActionQueue;

/* ===================== UTILITAIRES ===================== */

static void to_lower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}

static int is_number(const char *s) {
    if (!s[0]) return 0;
    for (int i = 0; s[i]; i++)
        if (!isdigit((unsigned char)s[i]))
            return 0;
    return 1;
}

static int load_file(const char *path, char *buffer) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    int n = fread(buffer, 1, MAX_JSON - 1, f);
    buffer[n] = '\0';
    fclose(f);
    return 1;
}

/* ===================== FILE D’ACTIONS =*/

static void init_queue(ActionQueue *q) {
    q->count = 0;
}

static void enqueue_action(ActionQueue *q, ActionType action) {
    if (q->count < MAX_ACTIONS)
        q->actions[q->count++] = action;
}

/* ===================== TOKENS → ACTIONS ===================== */

static int token_to_action(const char *token, ActionType *action) {
    if (!strcmp(token, "advance")) {
        *action = ACTION_ADVANCE; return 1;
    }
    if (!strcmp(token, "retreat")) {
        *action = ACTION_RETREAT; return 1;
    }
    if (!strcmp(token, "left")) {
        *action = ACTION_TURN_LEFT; return 1;
    }
    if (!strcmp(token, "right")) {
        *action = ACTION_TURN_RIGHT; return 1;
    }
    if (!strcmp(token, "stop")) {
        *action = ACTION_STOP; return 1;
    }
    return 0;
}

/* Recherche UNIQUEMENT dans commands{} */

static int find_token_in_json(const char *json,
                              const char *expression,
                              char *token) {
    char *cmd = strstr(json, "\"commands\"");
    if (!cmd) return 0;

    cmd = strchr(cmd, '{');
    if (!cmd) return 0;
    cmd++;

    char *p = cmd;
    while (*p && *p != '}') {
        if (*p != '"') {
            p++;
            continue;
        }

        char key[64];
        sscanf(p + 1, "%63[^\"]", key);

        char *list_start = strchr(p, '[');
        if (!list_start) break;
        char *list_end = strchr(list_start, ']');
        if (!list_end) break;

        char values[1024];
        strncpy(values, list_start, list_end - list_start);
        values[list_end - list_start] = '\0';

        /* nombres */
        if (is_number(expression) && strcmp(key, "distance") == 0) {
            strcpy(token, "distance");
            return 1;
        }

        char quoted[128];
        snprintf(quoted, sizeof(quoted), "\"%s\"", expression);

        if (strstr(values, quoted)) {
            strcpy(token, key);
            return 1;
        }

        p = list_end + 1;
    }
    return 0;
}

/* ===================== SORTIE ABSTRAITE ===================== */

static void output_action(ActionType action) {
    FILE *f = fopen(FICHIER_ACTION, "a");
    if (!f) return;

    switch (action) {
        case ACTION_ADVANCE:
            fprintf(f, "advance ");
            printf("[ACTION] advance\n");
            break;
        case ACTION_RETREAT:
            fprintf(f, "retreat ");
            printf("[ACTION] retreat\n");
            break;
        case ACTION_TURN_LEFT:
            fprintf(f, "left ");
            printf("[ACTION] left\n");
            break;
        case ACTION_TURN_RIGHT:
            fprintf(f, "right ");
            printf("[ACTION] right\n");
            break;
        case ACTION_STOP:
            fprintf(f, "stop ");
            printf("[ACTION] stop\n");
            break;
    }
    fclose(f);
}

/* ===================== PIPELINE PRINCIPAL ===================== */

void traiter_commande(void) {
    char phrase[MAX_CMD];
    char json[MAX_JSON];

    FILE *f = fopen(FICHIER_COMMANDE, "r");
    if (!f) {
        printf("[ERREUR] commande.txt introuvable\n");
        return;
    }
    fgets(phrase, MAX_CMD, f);
    fclose(f);

    phrase[strcspn(phrase, "\n")] = '\0';
    to_lower(phrase);

    printf("[TRACE] Phrase recue : %s\n", phrase);

    /* découpage en mots */
    char *words[MAX_WORDS];
    int word_count = 0;

    char *tok = strtok(phrase, " ");
    while (tok && word_count < MAX_WORDS) {
        words[word_count++] = tok;
        tok = strtok(NULL, " ");
    }

    ActionQueue queue;
    init_queue(&queue);

    DIR *dir = opendir(CONFIG_DIR);
    if (!dir) {
        printf("[ERREUR] dossier config introuvable\n");
        return;
    }

    /* Fenêtre glissante : 3 mots → 2 mots → 1 mot */
    for (int i = 0; i < word_count; i++) {
        int matched = 0;

        for (int size = 3; size >= 1 && !matched; size--) {
            if (i + size > word_count) continue;

            char expr[128] = "";
            for (int k = 0; k < size; k++) {
                strcat(expr, words[i + k]);
                if (k < size - 1) strcat(expr, " ");
            }

            rewinddir(dir);
            struct dirent *entry;

            while ((entry = readdir(dir))) {
                if (!strstr(entry->d_name, ".json")) continue;

                char path[256];
                snprintf(path, sizeof(path), "%s/%s", CONFIG_DIR, entry->d_name);
                if (!load_file(path, json)) continue;

                char token[64];
                if (find_token_in_json(json, expr, token)) {
                    printf("[TOKEN] \"%s\" -> %s\n", expr, token);

                    ActionType action;
                    if (token_to_action(token, &action)) {
                        enqueue_action(&queue, action);
                    }
                    matched = 1;
                    i += size - 1; /* sauter les mots consommés */
                    break;
                }
            }
        }
    }
    closedir(dir);

    /* Exécution abstraite (ordre respecté) */
    for (int i = 0; i < queue.count; i++) {
        output_action(queue.actions[i]);
    }
}
