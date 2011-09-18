/* Exercises 6 to 15. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct map {
    int width;
    int height;
    char* data;
};

/* Exercise 6 */
bool is_line_break(char ch) {
    if (ch == '\n' || ch == '\r')
        return true;
    return false;
}

/* Exercise 7 */
unsigned int get_file_length(char* filename) {
    FILE* fptr;
    if ((fptr = fopen(filename, "r")) == NULL)
        return 0;

    fseek(fptr, 0, SEEK_END);
    unsigned int length = ftell(fptr);
    fclose(fptr);

    return length;
}

/* Exercise 8 */
char* load_data(char* filename) {
    FILE* fptr;
    if ((fptr = fopen(filename, "r")) == NULL)
        return NULL;

    int data_length = get_file_length(filename);
    char* data = malloc((data_length + 1)*sizeof(char));
    size_t chars_read = fread(data, sizeof(char), data_length, fptr);
    fclose(fptr);

    if (chars_read != (size_t) data_length) {
        free(data);
        return NULL;
    }

    return data;
}

/* Exercise 9 */
struct map *load_map(char* filename) {
    char* data = load_data(filename);
    if (!data)
        return NULL;
    struct map *new_map = malloc(sizeof(struct map));
    new_map->data = data;

    int width = 0;
    while (!is_line_break(data[width]))
        width++;
    new_map->width = width;

    unsigned int data_length = get_file_length(filename);
    int height = 1;
    for (unsigned int i = width; i < data_length; i++) {
        if (!is_line_break(data[i]) && is_line_break(data[i-1]))
            height++;
    }
    new_map->height = height;

    return new_map;
}

/* Exercise 10 */
void print_map(struct map* the_map) {
    printf("width: %d, height: %d\n%s", the_map->width, the_map->height,
        the_map->data);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: floodfill map_file_name\n");
        exit(1);
    }
    char* map_file = argv[1];
    struct map *map = load_map(map_file);
    print_map(map);

    exit(0);
}
