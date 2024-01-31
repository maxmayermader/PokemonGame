#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 100  
#define HEIGHT 21 //X
#define WIDTH 80 //Y

#define BOULDER '%'
#define TREE '^'
#define ROAD '#'
#define MART 'M'
#define CENTER 'C'
#define GRASS ':'
#define CLEARING '.'
#define WATER '~'
//#define PLAYER '@'

char map[HEIGHT][WIDTH];
int queSize = 0;

/////Que Implemntation////
 struct Node {  
    int coord[2]; 
    char seed; 
    struct Node* next;  
};  
  
struct Node* front = NULL;  
struct Node* rear = NULL;  
  
void enqueue(int element[2], char seed) {  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    new_node->coord[0] = element[0];
    new_node->coord[1] = element[1];
    new_node->seed = seed;  
    new_node->next = NULL;  
    if (front == NULL && rear == NULL) {  
        front = rear = new_node;  
        return;  
    }  
    rear->next = new_node;  
    rear = new_node; 
    queSize ++; 
}  
  
int dequeue(int coord[2], char *s) {  
    if (front == NULL) {  
        printf("Queue is empty");  
        return -1;  
    }  
    struct Node* temp = front;  
    coord[0] = temp->coord[0]; 
    coord[1] = temp->coord[1]; 
    *s = temp->seed;
    if (front == rear) {  
        front = rear = NULL;  
    }  
    else {  
        front = front->next;  
    }  

    free(temp);  
    queSize --;
    return 0;  
}  





//TODO 7 biomes
//2 tall grass
//1 water region
//2 clearings
//1 forrest
//1 mountin
void createMap(){
    //assign biomes
    int grass1[2] = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};
    int grass2[2] = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};
    int water[2] = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};
    int clearing1[2] = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};
    int clearing2[2] = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};
    int forrest[2] = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};
    int mountin[2] = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};

    /*
    1. make map with que
    2. make border
    3. make roads
    4. make buildings
    */

//    int arr[2]={1,2};
//    enqueue(arr, '%');
//    enqueue(arr, '#');

    enqueue(grass1, ':');

    while 



}

//Prints map out to the terminal
void printMap(char map[HEIGHT][WIDTH]){
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

    srand(time(NULL));
    createMap();

    printMap(map);
    return 0;
}