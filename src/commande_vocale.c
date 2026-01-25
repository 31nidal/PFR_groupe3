#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ===================== CONFIG ===================== */
#define CMD_FILE   "data/commande.txt"
#define OUT_FILE   "data/action.txt"

#define DEFAULT_DISTANCE 50
#define DEFAULT_ANGLE    90

#define MAX_CMD    512
#define MAX_JSON   20000
#define MAX_WORDS  128

/* ===================== JSON FILES ===================== */
static const char *json_files[] = {
    "config/fr.json",
    "config/en.json",
    "config/es.json"
};

#define JSON_COUNT (sizeof(json_files) / sizeof(json_files[0]))

/* ===================== UTILITAIRES ===================== */

static char my_tolower(char c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    return c;
}

static int my_isdigit(char c) {
    return (c >= '0' && c <= '9');
}

static void to_lower(char *s) {
    for (; *s; s++) *s = my_tolower(*s);
}

static int is_number(const char *s) {
    if (!*s) return 0;
    for (; *s; s++)
        if (!my_isdigit(*s))
            return 0;
    return 1;
}

static int load_file(const char *path, char *buf) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;
    size_t n = fread(buf, 1, MAX_JSON - 1, f);
    buf[n] = '\0';
    fclose(f);
    return 1;
}

static int starts_with(const char *s, const char *prefix) {
    return strncmp(s, prefix, strlen(prefix)) == 0;
}

/* ===================== JSON MATCH ===================== */

static int json_match(const char *json,
                      const char *expr,
                      char *key_out)
{
    char *cmd = strstr(json, "\"commands\"");
    if (!cmd) return 0;

    cmd = strchr(cmd, '{') + 1;

    while (*cmd && *cmd != '}') {

        if (*cmd != '"') { cmd++; continue; }

        char key[64];
        sscanf(cmd + 1, "%63[^\"]", key);

        char *start = strchr(cmd, '[');
        char *end   = start ? strchr(start, ']') : NULL;
        if (!start || !end) { cmd++; continue; }

        for (char *v = start + 1; v < end; v++) {
            if (*v == '"') {
                char value[64];
                sscanf(v + 1, "%63[^\"]", value);
                if (!strcmp(value, expr)) {
                    strcpy(key_out, key);
                    return 1;
                }
            }
        }
        cmd = end + 1;
    }
    return 0;
}

/* ===================== UNITÉS ===================== */

static int is_meter_unit(char **words, int i, int n,
                         char jsons[JSON_COUNT][MAX_JSON])
{
    if (i + 1 >= n) return 0;

    /* Tolérance directe */
    if (!strcmp(words[i + 1], "m"))
        return 1;

    char key[64];
    for (size_t j = 0; j < JSON_COUNT; j++) {
        if (json_match(jsons[j], words[i + 1], key)) {
            if (!strcmp(key, "meters"))
                return 1;
        }
    }
    return 0;
}

/* ===================== FIND BALL ===================== */

static int detect_find_ball(char **words, int n,
                            char jsons[JSON_COUNT][MAX_JSON],
                            char *color_out)
{
    int found = 0, ball = 0;

    for (int i = 0; i < n; i++) {

        /* Tolérance "trouve / trouver / trouves" */
        if (starts_with(words[i], "trouv"))
            found = 1;

        char key[64];
        for (size_t j = 0; j < JSON_COUNT; j++) {
            if (json_match(jsons[j], words[i], key)) {

                if (!strcmp(key, "found")) found = 1;
                else if (!strcmp(key, "ball")) ball = 1;
                else if (!strcmp(key, "red") ||
                         !strcmp(key, "blue") ||
                         !strcmp(key, "green") ||
                         !strcmp(key, "yellow")) {
                    strcpy(color_out, key);
                }
            }
        }
    }

    return found && ball && *color_out;
}

/* ===================== PIPELINE ===================== */

void traiter_commande(void)
{
    char phrase[MAX_CMD];
    char jsons[JSON_COUNT][MAX_JSON];

    /* Charger JSON */
    for (size_t i = 0; i < JSON_COUNT; i++)
        if (!load_file(json_files[i], jsons[i])) return;

    /* Lire commande */
    FILE *f = fopen(CMD_FILE, "r");
    if (!f) return;
    if (!fgets(phrase, MAX_CMD, f)) {
        fclose(f);
        return;
    }
    fclose(f);

    phrase[strcspn(phrase, "\n")] = 0;
    to_lower(phrase);

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
    if (!out) return;

    /* ===== PRIORITÉ FIND BALL ===== */
    char color[16] = "";
    if (detect_find_ball(words, n, jsons, color)) {
        fprintf(out, "find_ball %s\n", color);
        printf("[ACTION] find_ball %s\n", color);
        fclose(out);
        return;
    }

    /* ===== COMMANDES CLASSIQUES ===== */
    for (int i = 0; i < n; i++) {

        char key[64];
        for (size_t j = 0; j < JSON_COUNT; j++) {

            if (!json_match(jsons[j], words[i], key))
                continue;

            if (!strcmp(key, "advance") || !strcmp(key, "retreat")) {

                /* advance to X Y */
                if (i + 3 < n) {
                    char tmp[64];
                    if (json_match(jsons[j], words[i + 1], tmp) && !strcmp(tmp, "to") &&
                        is_number(words[i + 2]) && is_number(words[i + 3])) {

                        int x = atoi(words[i + 2]);
                        int y = atoi(words[i + 3]);

                        fprintf(out, "%s to %d %d\n", key, x, y);
                        printf("[ACTION] %s to %d %d\n", key, x, y);
                        continue;
                    }
                }

                /* advance distance */
                int dist = DEFAULT_DISTANCE;

                for (int k = i; k < n - 1; k++) {
                    if (is_number(words[k]) &&
                        is_meter_unit(words, k, n, jsons)) {
                        dist = atoi(words[k]);
                        break;
                    }
                }

                fprintf(out, "%s %d meters\n", key, dist);
                printf("[ACTION] %s %d meters\n", key, dist);
            }


            /* TOURNER */
            if (!strcmp(key, "turn")) {

                char dir[16] = "right";
                int angle = DEFAULT_ANGLE;

                for (int k = i; k < n; k++) {

                    if (is_number(words[k]))
                        angle = atoi(words[k]);

                    char tmp[64];
                    for (size_t l = 0; l < JSON_COUNT; l++) {
                        if (json_match(jsons[l], words[k], tmp)) {
                            if (!strcmp(tmp, "left") ||
                                !strcmp(tmp, "right"))
                                strcpy(dir, tmp);
                        }
                    }
                }

                fprintf(out, "turn %s %d degrees\n", dir, angle);
                printf("[ACTION] turn %s %d degrees\n", dir, angle);
            }

        }
    }

    fclose(out);
}
