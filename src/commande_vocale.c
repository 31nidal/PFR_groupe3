#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <dirent.h>

/* ===================== CONFIG ===================== */
#define CONFIG_DIR "config"
#define CMD_FILE   "commande.txt"
#define OUT_FILE   "action.txt"

#define DEFAULT_DISTANCE 50
#define DEFAULT_ANGLE    90

#define MAX_CMD    512
#define MAX_JSON   20000
#define MAX_WORDS  128
#define MAX_FILES  8

/* ===================== UTILITAIRES ===================== */

static void to_lower(char *s) {
    for (; *s; s++)
        *s = tolower((unsigned char)*s);
}

static int is_number(const char *s) {
    if (!*s) return 0;
    for (; *s; s++)
        if (!isdigit((unsigned char)*s))
            return 0;
    return 1;
}

static int load_file(const char *path, char *buf) {
    FILE *f = fopen(path, "r");
    if (!f) {
        perror(path);
        return 0;
    }
    size_t n = fread(buf, 1, MAX_JSON - 1, f);
    buf[n] = '\0';
    fclose(f);
    return 1;
}

/* ===================== JSON MATCH ===================== */

static int json_match(const char *json,
                      const char *expr,
                      char *key_out)
{
    char *cmd = strstr(json, "\"commands\"");
    if (!cmd) return 0;

    cmd = strchr(cmd, '{');
    if (!cmd) return 0;
    cmd++;

    char *p = cmd;

    while (*p && *p != '}') {

        if (*p != '"') { p++; continue; }

        char key[64];
        sscanf(p + 1, "%63[^\"]", key);

        char *colon = strchr(p, ':');
        if (!colon) return 0;

        char *start = strchr(colon, '[');
        char *end   = start ? strchr(start, ']') : NULL;
        if (!start || !end) { p++; continue; }

        char *v = start + 1;
        while (v < end) {
            if (*v == '"') {
                char value[64];
                sscanf(v + 1, "%63[^\"]", value);
                if (strcmp(value, expr) == 0) {
                    strcpy(key_out, key);
                    return 1;
                }
            }
            v++;
        }
        p = end + 1;
    }
    return 0;
}

/* ===================== PIPELINE ===================== */

void traiter_commande(void)
{
    char phrase[MAX_CMD];
    char jsons[MAX_FILES][MAX_JSON];
    int json_count = 0;

    /* Charger les JSON */
    DIR *dir = opendir(CONFIG_DIR);
    if (!dir) {
        perror("config");
        return;
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) && json_count < MAX_FILES) {
        if (strstr(ent->d_name, ".json")) {
            char path[256];
            snprintf(path, sizeof(path), "%s/%s", CONFIG_DIR, ent->d_name);
            if (load_file(path, jsons[json_count]))
                json_count++;
        }
    }
    closedir(dir);

    if (json_count == 0) {
        printf("[ERREUR] Aucun JSON charge\n");
        return;
    }

    /* Lire commande */
    FILE *f = fopen(CMD_FILE, "r");
    if (!f) {
        perror("commande.txt");
        return;
    }

    if (!fgets(phrase, MAX_CMD, f)) {
        fclose(f);
        return;
    }
    fclose(f);

    phrase[strcspn(phrase, "\n")] = 0;
    to_lower(phrase);

    if (!*phrase) {
        printf("[INFO] Phrase vide ignoree\n");
        return;
    }

    printf("[TRACE] Phrase : %s\n", phrase);

    /* Découpage */
    char *words[MAX_WORDS];
    int n = 0;
    char *tok = strtok(phrase, " ");
    while (tok && n < MAX_WORDS) {
        words[n++] = tok;
        tok = strtok(NULL, " ");
    }

    FILE *out = fopen(OUT_FILE, "a");
    if (!out) {
        perror("action.txt");
        return;
    }

    int i = 0;

    while (i < n) {

        char key[64];
        int matched = 0;

        for (int size = 3; size >= 1 && !matched; size--) {
            if (i + size > n) continue;

            char expr[128] = "";
            for (int k = 0; k < size; k++) {
                strcat(expr, words[i + k]);
                if (k < size - 1) strcat(expr, " ");
            }

            for (int j = 0; j < json_count; j++) {

                if (!json_match(jsons[j], expr, key))
                    continue;

                /* ===== AVANCE / RECULE ===== */
                if (!strcmp(key, "advance") || !strcmp(key, "retreat")) {
                    int dist = DEFAULT_DISTANCE;

                    for (int k = i; k < n && k < i + 6; k++)
                        if (is_number(words[k]))
                            dist = atoi(words[k]);

                    fprintf(out, "%s %d meters\n", key, dist);
                    printf("[ACTION] %s %d meters\n", key, dist);
                    matched = 1;
                    break;
                }

                /* ===== TOURNER ===== */
                if (!strcmp(key, "turn")) {

                    char dir_str[16] = "right";   // FIX
                    int angle = DEFAULT_ANGLE;

                    for (int k = i; k < n && k < i + 6; k++) {

                        if (is_number(words[k]))
                            angle = atoi(words[k]);

                        char tmp[64];
                        for (int l = 0; l < json_count; l++) {
                            if (json_match(jsons[l], words[k], tmp)) {
                                if (!strcmp(tmp, "left") || !strcmp(tmp, "right")) {
                                    strcpy(dir_str, tmp);   // FIX
                                }
                            }
                        }
                    }

                    fprintf(out, "turn %s %d degrees\n", dir_str, angle);
                    printf("[ACTION] turn %s %d degrees\n", dir_str, angle);
                    matched = 1;
                    break;
                }
            }
        }

        i++;
    }

    fclose(out);
}
