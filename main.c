#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minimize_inside(char *outbuf, char *inbuf, size_t len, size_t *i, size_t *j)
{
    int found_ws = 0;
    for(; *i < len; ++(*i), ++(*j)) {
        switch (inbuf[*i]) {
        case ' ':
            if(found_ws == 0) {
                found_ws = 1;
                outbuf[*j] = inbuf[*i];
            }
            break;

        case '>':
            // End of tag found, need to leave
            outbuf[(*j)++] = inbuf[*i];
            return;
            break;

        default:
            // We're inside an attribute
            outbuf[*j] = inbuf[*i];
            break;
        }
    }
}

void minimize(FILE *fp)
{
    char inbuf[BUFSIZ];
    char outbuf[BUFSIZ]; // = {0};
    size_t i;
    size_t j = 0;
    size_t len;

    while(fgets(inbuf, BUFSIZ, fp) != NULL) {
        int found_ws = 0;

        len = strlen(inbuf);
        for(i = 0, j = 0; i < len; ++i) {
            switch (inbuf[i]) {
            case '<':
                found_ws = 0;
                minimize_inside(outbuf, inbuf, len, &i, &j);
                break;

            case ' ':
            case '\n':
                // Skip whitespace and newline except
                // it's text like "Hello World"
                if((i+1) < len && inbuf[i+1] != '<' && inbuf[i+1] != ' ') {
                    outbuf[j++] = inbuf[i];
                }
                break;

            default:
                outbuf[j++] = inbuf[i];
                break;
            }
        }

        outbuf[j] = 0;

        // debug output
        printf("%s", outbuf);
    }

    // debug output
    printf("\n");
}

int main(int argc, char **argv)
{
    FILE *fp;

    if(argc < 2) {
        fprintf(stderr, "No file given. You need to pass an html file.\n");
        fprintf(stderr, "USAGE: %s <file.html>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Reading file: %s\n", argv[1]);

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Could not open the file");
        exit(EXIT_FAILURE);
    }

    minimize(fp);

    fclose(fp);
    return 0;
}
