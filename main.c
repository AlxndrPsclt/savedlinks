#include <stdio.h>
#include <yaml.h>
#include <string.h>

typedef enum { NONE, NAME, URL } State;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <yaml-file>\n", argv[0]);
        return 1;
    }

    FILE *fh = fopen(argv[1], "r");
    FILE *html = fopen("index.html", "w");

    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fputs("Failed to initialize parser!\n", stderr);
        return 1;
    }

    yaml_parser_set_input_file(&parser, fh);

    char* link_name = NULL;
    char* link_url = NULL;
    State state = NONE;

    fprintf(html, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(html, "<title>Links</title>\n");
    fprintf(html, "<link rel=\"stylesheet\" type=\"text/css\" href=\"styles.css\">\n");
    fprintf(html, "</head>\n<body>\n<h1>List of Links</h1>\n<div class=\"container\">\n<ul class=\"link-list\">\n");

    while (1) {
        if (!yaml_parser_parse(&parser, &event)) {
            printf("Parser error %d\n", parser.error);
            exit(EXIT_FAILURE);
        }

        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((char*) event.data.scalar.value, "name") == 0) {
                state = NAME;
            } else if (strcmp((char*) event.data.scalar.value, "url") == 0) {
                state = URL;
            } else {
                if (state == NAME) {
                    link_name = strdup((char*) event.data.scalar.value);
                } else if (state == URL) {
                    link_url = strdup((char*) event.data.scalar.value);
                }

                if (link_name != NULL && link_url != NULL) {
                    fprintf(html, "<li class=\"link-item\"><a href=\"%s\">%s</a></li>\n", link_url, link_name);
                    free(link_name);
                    free(link_url);
                    link_name = NULL;
                    link_url = NULL;
                }
            }
        }

        if (event.type == YAML_STREAM_END_EVENT) {
            break;
        }

        yaml_event_delete(&event);
    }

    fprintf(html, "</ul>\n</div>\n</body>\n</html>");

    yaml_parser_delete(&parser);
    fclose(fh);
    fclose(html);

    return 0;
}

