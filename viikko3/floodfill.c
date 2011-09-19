/* Exercises 6 to 15. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BAD_CHAR 'X'

typedef struct map {
    int width;
    int height;
    char* data;
} Map;

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
    if (!data)
        return NULL;

    size_t chars_read = fread(data, sizeof(char), data_length, fptr);
    fclose(fptr);

    data[data_length] = '\0';

    if (chars_read != (size_t) data_length) {
        free(data);
        return NULL;
    }

    return data;
}

/* Removes newlines from the given data (mutates the original
memory area) and returns the length of the new data. */
int remove_newlines(char** data, int data_len) {
    int newlen = data_len;
    int i = 0;
    for (int j = 0; j <= data_len; j++) {
        if (is_line_break((*data)[j]))
            newlen--;
        else {
            (*data)[i] = (*data)[j];
            i++;
        }
    }
    *data = realloc(*data, newlen*sizeof(char));
    if (!data) {
        fprintf(stderr, "Ran out of memory.\n");
        exit(2);
    }

    return newlen;
}

/* Exercise 9 */
Map* load_map(char* filename) {
    char* data = load_data(filename);
    if (!data)
        return NULL;
    Map *new_map = malloc(sizeof(Map));
    if (!new_map)
        return NULL;

    int width = 0;
    while (!is_line_break(data[width]))
        width++;
    new_map->width = width;

    unsigned int data_length = get_file_length(filename);
    data_length = remove_newlines(&data, data_length);
    new_map->data = data;
    
    new_map->height = data_length/width;

    return new_map;
}

/* Exercise 10 */
void print_map(Map* the_map) {
    printf("width: %d, height: %d\n", the_map->width, the_map->height);
    for (int y = 0; y < the_map->height; y++) {
        for (int x = 0; x < the_map->width; x++) {
            int index = y * the_map->width + x;
            printf("%c", the_map->data[index]);
        }
        printf("\n");
    }
}

/* Exercise 13 */
bool valid_coordinates(Map *the_map, int x, int y) {
    if ((x >= 0 && x < the_map->width) &&
        (y >= 0 && y < the_map->height))
        return true;
    return false;
}

/* Exercise 11 */
char get_char_at(Map *the_map, int x, int y) {
    if (valid_coordinates(the_map, x, y)) {
        unsigned int coord = y * the_map->width + x;
        return the_map->data[coord];
    }
    return BAD_CHAR;
}

/* Exercise 12 */
void set_char_at(Map *the_map, int x, int y, char val) {
    if (!valid_coordinates(the_map, x, y))
        return;
    unsigned int coord = y * the_map->width + x;
    the_map->data[coord] = val;
}

char random_digit_symbol() {
    int random = rand()/((float) RAND_MAX)*9 + 1;
    char c = '0' + random;
    return c;
}

/* Exercise 14. Disregarded the unnecessary parameter wall
in the assignment. Despite the name, this is not flood fill.
A true procedural flood fill would have to use e.g. a queue
and also take the starting coordinates as parameters, but
the description in the assignment does not match a flood
fill algorithm. */
void flood_fill(Map *the_map) {
    for (int y = 0; y < the_map->height; y++)
        for (int x = 0; x < the_map->width; x++) {
            if (get_char_at(the_map, x, y) != ' ')
                continue;
            char c = random_digit_symbol();
            set_char_at(the_map, x, y, c);
            print_map(the_map);
        }
}

/* Exercise 15. Disregarded the unnecessary parameter wall in
the assignment. */
void rec_flood_fill(Map *the_map, int x, int y) {
    if (get_char_at(the_map, x, y) != ' ')
        return;
    char c = random_digit_symbol();
    set_char_at(the_map, x, y, c);
    print_map(the_map);
    rec_flood_fill(the_map, x-1, y);
    rec_flood_fill(the_map, x+1, y);
    rec_flood_fill(the_map, x, y-1);
    rec_flood_fill(the_map, x, y+1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: floodfill map_file_name\n");
        exit(1);
    }
    srand(time(NULL));
    char* map_file = argv[1];
    Map *map = load_map(map_file);
    if (!map) {
        fprintf(stderr, "Ran out of memory.\n");
        exit(2);
    }

    print_map(map);
    rec_flood_fill(map, 7, 3);

    exit(0);
}
