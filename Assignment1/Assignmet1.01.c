#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 100  
#define ROW 21//21 //Y
#define COL 80 //X

#define BOULDER '%'
#define TREE '^'
#define ROAD '#'
#define MART 'M'
#define CENTER 'C'
#define GRASS ':'
#define CLEARING '.'
#define WATER '~'
//#define PLAYER '@'

char map[ROW][COL];
int queSize = 0;

int getQueSize(){
    return queSize;
}

//Prints map out to the terminal
void printMap(){
    int i;
    int j;
    for (i=0; i < ROW; i++){
        for(j=0; j < COL; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

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
    queSize++; 
}  
  
int dequeue(int coord[2], char *s) {  
    if (front == NULL) {  
        //free(front);
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
/////Que Implemntation////

//Code for creating roads and buildings
void makeRoads(){
    int entranceX1[2] = {0, rand() % (COL-2)+1};
    int entranceX2[2] = {ROW - 1, rand() % (COL-2)+1};
    int entranceY1[2] = {rand() % (ROW-2)+1, 0};
    int entranceY2[2] = {rand() % (ROW-2)+1, COL - 1};

    int randX = rand() % (ROW-2) + 1;
    int randY = rand() % (COL-2) + 1;

    int connectionX1[2] = {randX, entranceX1[1]};
    int connectionX2[2] = {randX, entranceX2[1]};
    int connectionY1[2] = {entranceY1[0], randY};
    int connectionY2[2] = {entranceY2[0], randY};

    int a,b;
    //build roads for cols
    //Go down
    for (a=entranceX1[0]; a <= connectionX1[0]; a++){
        map[a][entranceX1[1]] = '#';
        //printf("1  %d     %d\n", a, entranceX1[1]);
    }
    if(connectionX1[1] <= connectionX2[1]){ //go left
        for(b=connectionX1[1]; b<=connectionX2[1]; b++){
            map[connectionX2[0]][b] = '#';
            //printf("2  %d     %d\n", connectionX2[0], b);
        }
    } else { //Go right
        for(b=connectionX1[1]; b>=connectionX2[1]; b--){
            map[connectionX2[0]][b] = '#';
            //printf("2  %d     %d\n", connectionX2[0], b);
        }
    }
    //Go right
    
    //Go down
    for (a=connectionX2[0]; a <= entranceX2[0]; a++){
        map[a][connectionX2[1]] = '#';
        //printf("3  %d     %d\n", a, connectionX1[1]);
    }





    //Build rooads for rows
    //Go right
    for (a=entranceY1[1]; a <= connectionY1[1]; a++){
        map[entranceY1[0]][a] = '#';
        //printf("1  %d     %d\n", a, entranceX1[1]);
    }
    if(connectionY1[0] <= connectionY2[0]){ //go down
        for(b=connectionY1[0]; b<=connectionY2[0]; b++){
            map[b][connectionY1[1]] = '#';
            //printf("2  %d     %d\n", connectionX2[0], b);
        }
    } else { //Go up
        for(b=connectionY1[0]; b>=connectionY2[0]; b--){
            map[b][connectionY1[1]] = '#';
            //printf("2  %d     %d\n", connectionX2[0], b);
        }
    }
    
    //Go right
     for (a=connectionY2[1]; a <= entranceY2[1]; a++){
        map[connectionY2[0]][a] = '#';
        p//rintf("1  %d     %d\n", a, entranceX1[1]);
    }
    
}

void createMap(){
    //assign biomes
    int grass1[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int grass2[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int water[2] =      {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing1[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing2[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int forest[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int mountain[2] =   {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};

    /*
    1. make map with que
    2. make border
    3. make roads
    4. make buildings
    */

        // int arr[2]={1,2};
        // enqueue(arr, '%');
        // int retArr[2];
        
        // char *retC;
        // dequeue(retArr, &retC);
        // printf("%d    %c\n", retArr[1], retC);

    enqueue(grass1, GRASS);
    enqueue(water, WATER);
    enqueue(clearing1, CLEARING);
    enqueue(grass2, GRASS);
    enqueue(forest, TREE);
    enqueue(mountain, BOULDER);
    enqueue(clearing2, CLEARING);

    char *currSeed = (char*)malloc(sizeof(char));

    // while (getQueSize() > 0) {
    //     int currCoord[2];
        
    //     dequeue(currCoord, currSeed);
    //     //printf("%c", *currSeed);
    //     map[currCoord[0]][currCoord[1]] = *currSeed;
    //     // printMap();
    //     // printf("\n");
    //     //for loops variables
    //     if (currCoord[0]+1 < ROW-1){
    //         if (map[currCoord[0]+1][currCoord[1]] == '_'){
    //             int arr[2] = {currCoord[0]+1, currCoord[1]};
    //             enqueue(arr, *currSeed);
    //         }
    //     }
    //     if (currCoord[0]-1 > 0){
    //         if (map[currCoord[0]-1][currCoord[1]] == '_'){
    //             int arr[2] = {currCoord[0]-1, currCoord[1]};
    //             enqueue(arr, *currSeed);
    //         }
    //     }
    //     if (currCoord[1]+1 < COL-1){
    //         if (map[currCoord[0]][currCoord[1]+1] == '_'){
    //             int arr[2] = {currCoord[0], currCoord[1]+1};
    //             enqueue(arr, *currSeed);
    //         }
    //     }
    //     if (currCoord[1]-1 > 0){
    //         if (map[currCoord[0]][currCoord[1]-1] == '_'){
    //             int arr[2] = {currCoord[0], currCoord[1]-1};
    //             enqueue(arr, *currSeed);
    //         }
    //     }
    // }
    free(currSeed);

    makeRoads();

}

void setMap(){
    int i;
    int j;
    for(i = 0; i < ROW; i++){
        for(j=0; j < COL; j++){
            if (i == 0 || i == ROW-1 || j == 0 || j == COL-1){
                map[i][j] = '%';
                continue;
            }
            map[i][j] = '_';
        }
    }
}

int main(int argc, char *argv[]){

    srand(time(NULL));
    printf("hello0\n");
    setMap();
    printf("hello1\n");
    createMap();
    printf("hello2\n");
    printMap(map);
    printf("hello3\n");
    
    
    return 0;
}