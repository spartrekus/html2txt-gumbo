/* gcc -O2 -Igumbo -static -o html2txt html2txt.c main.c -Lgumbo -lgumbo */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "html2txt.h"

static char *
read_stdin()
{
    char buffer[BUFSIZ];
    char *output;
    int extra;
    int length = 0;
    int bulk = 1024;

    output = (char *) malloc(bulk);
    memset(output, 0, bulk);
    while ((extra = fread(buffer, 1, BUFSIZ, stdin))) {
        while (length + extra > bulk - 1) {
            bulk += bulk >> 1;
            output = (char *) realloc(output, bulk);
        }
        strncat(output, buffer, extra);
        length += strlen(buffer);
    }
    return output;
}

int
main(int argc, char *argv[])
{
    char *raw_html, *text;

    if (argc != 1) {
        fprintf(stderr, "%s expects no arguments\n", argv[0]);
        return 1;
    }

    raw_html = read_stdin();
    text = html2text(raw_html);
    printf("%s\n", text);

    free(raw_html);
    free(text);

    return 0;
}
