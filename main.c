#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#define BORDER_SIZE 12

int create_field(char ***field, int heigth);
void generate_field(char** field, int heigth);
int put_sand(char **field, int heigth, int x, int y);
void display_field(char **field, int height);
void destroy_field(char ***field);
int get_sand_coordinates(int *x, int *y);

int main(void) {

    char **field;
    int err_code = create_field(&field, BORDER_SIZE);
    if (err_code)
        return 1;

    generate_field(field, BORDER_SIZE);

    display_field(field, BORDER_SIZE);
    int x, y;

    while(1) {
        if (get_sand_coordinates(&x, &y) != 0)
            continue;

        put_sand(field, BORDER_SIZE, x, y);
    }

    getchar();

    destroy_field(&field);
    return 0;
}

int create_field(char ***field, int heigth) {
    *field = calloc(heigth, sizeof(char *));
    if (!*field) return 1;

    for (int i = 0; i < heigth; i++) {
        *(*field + i) = calloc(heigth + 1, sizeof(char));
        if (!*(*field + i)) {
            destroy_field(field);
            return 1;
        }
    }

    return 0;
}

void generate_field(char** field, int heigth) {
    for (int i = 0, j; i < heigth; i++) {
        for (j = 0; j < heigth; j++) {
            if (j == 0 || j == heigth - 1)
                *(*(field + i) + j) = '|';
            else if(i == 0 || i == heigth - 1)
                *(*(field + i) + j) = '_';
            else
                *(*(field + i) + j) = ' ';
        }

        *(*(field + i) + j + 1) = '\0';
    }
}

int get_sand_coordinates(int *x, int *y) {
    printf("Podaj wspolrzedne piasku x,y (ot 0 do 35):\n");

    if (scanf("%d %d", x, y) != 2) return 1;

    if (*x < 0 || *y < 0 || *x > BORDER_SIZE - 1 || *y > BORDER_SIZE + 1) return 1;

    return 0;
}

int put_sand(char **field, int heigth, int x, int y) {
    x += 1, y += 1;
    if (*(*(field + y) + x) == '.') return 1;

    *(*(field + y) + x) = '.';

    for (int i = y; i < heigth - 1; i++) {
        system("cls");
        // usleep(50);
        if (*(*(field + i + 1) + x) == '.') {
            *(*(field + i) + x) = '.';
            display_field(field, heigth);
            break;
        }
        *(*(field + i) + x) = ' ';
        *(*(field + i + 1) + x) = '.';
        display_field(field, heigth);
    }

   return 0;
}

void display_field(char **field, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++)
            printf("%c", *(*(field + i) + j));
        printf("\n");
    }
}

void destroy_field(char ***field) {
    if (!*field) return;

    for (int i = 0; *(*field + i); i++)
        free(*(*field + i));

    free(*field);
    *field = NULL;
}
