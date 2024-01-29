#include <stdio.h>

#define HEIGHT 21
#define WIDTH 80

void printMap(char map[HEIGHT][HEIGHT]){
    int i;
    int j;
    for (i=0; i < HEIGHT; i++){
        for(j=0; j < WIDTH; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}



int main(int argc, char *argv[]){
    char map[HEIGHT][WIDTH];

    printMap(map);
    return 0;
}