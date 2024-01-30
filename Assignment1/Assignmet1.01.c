#include <stdio.h>

#define MAX_SIZE 100  
#define HEIGHT 21
#define WIDTH 80

#define BOULDER '%'
#define TREE '^'
#define ROAD '#'
#define MART 'M'
#define CENTER 'C'
#define GRASS ':'
#define CLEARING '.'
#define WATER '~'
//#define PLAYER '@'



/////Que Implemntation////
int queue[MAX_SIZE];  
int front = -1;  
int rear = -1;  
  
void enqueue(int element) {  
    if (rear == MAX_SIZE - 1) {  
        printf("Queue is full");  
        return;  
    }  
    if (front == -1) {  
        front = 0;  
    }  
    rear++;  
    queue[rear] = element;  
}  
  
int dequeue() {  
    if (front == -1 || front > rear) {  
        printf("Queue is empty");  
        return -1;  
    }  
    int element = queue[front];  
    front++;  
    return element;  
}  





//TODO 7 biomes
//2 tall grass
//1 water region
//2 clearings
//1 forrest
//1 mountin
void createMap(char *map[HEIGHT][HEIGHT]){
    //assign biomes
    int grass1[2][1] = {rand() % (WIDTH+1), rand() % (HEIGHT+1)};
    int grass2[2][1] = {rand() % (WIDTH+1), rand() % (HEIGHT+1)};
    int water[2][1] = {rand() % (WIDTH+1), rand() % (HEIGHT+1)};
    int clearing1[2][1] = {rand() % (WIDTH+1), rand() % (HEIGHT+1)};
    int clearing2[2][1] = {rand() % (WIDTH+1), rand() % (HEIGHT+1)};
    int forrest[2][1] = {rand() % (WIDTH+1), rand() % (HEIGHT+1)};
    int mountin[2][1] = {rand() % (WIDTH+1), rand() % (HEIGHT+1)};

    /*
    1. make map with que
    2. make border
    3. make roads
    4. make buildings
    
    
    */


}

//Prints map out to the terminal
void printMap(char *map[HEIGHT][HEIGHT]){
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

    srand(time(NULL));


    createMap(map);

    printMap(map);
    return 0;
}