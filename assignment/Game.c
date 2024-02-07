#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100  
#define ROW 21//21 //Y
#define COL 80//80 //X 
#define worldXSize 401
#define worldYSize 401

#define BOULDER '%'
#define TREE '^'
#define ROAD '#'
#define MART 'M'
#define CENTER 'C'
#define GRASS ':'
#define CLEARING '.'
#define WATER '~'
//#define PLAYER '@'



//map struct for terrain. 21x80 map
typedef struct mapStruct{
	int gateN;//top
	int gateS;//bottom
	int gateW;//left
	int gateE;//right
	char terrain[ROW][COL];
}mapStruct;

//Global map. Array of map pointers
typedef struct worldMap{
    mapStruct* arr[worldYSize][worldXSize];
}worldMap;

//char startMap[ROW][COL];
int queSize = 0;

int getQueSize(){
    return queSize;
}


//func declerations
    void createMap(int x, int y, worldMap *wm);

//Prints map out to the terminal
void printMap(mapStruct *map){
    int i;
    int j;
    for (i=0; i < ROW; i++){
        for(j=0; j < COL; j++){
            printf("%c", map->terrain[i][j]);
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
struct Node* front = NULL;  ////front of que
struct Node* rear = NULL;    ////end of que
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
void makeRoads(mapStruct *map, int distanceFromCenter){
    //rand() % (max_number + 1 - minimum_number) + minimum_number
    int entranceX1[2] = {0, rand() % (COL-4+1-4)+4}; //North gate
    int entranceX2[2] = {ROW - 1, rand() % (COL-4+1-4)+4}; //South gate
    int entranceY1[2] = {rand() % (ROW-10+1-10)+10, 0};//West gate
    int entranceY2[2] = {rand() % (ROW-4+1-4)+4, COL - 1};//East Gate

    if(map->gateN != -1){
        int gateVal = map->gateN;
        entranceX1[1] = gateVal;
        //entranceY1[1] = 0;
    } else {
        map->gateN = entranceX1[1];
    }
    if(map->gateS != -1){
        int gateVal = map->gateS;
        entranceX2[1] = gateVal;
        //entranceY1[0] = 0;
    } else {
        map->gateS = entranceX2[1];
    }
    if(map->gateW != -1){
        int gateVal = map->gateW;
        entranceY1[0] = gateVal;
        //entranceY1[0] = ROW - 1;
    } else {
        map->gateW = entranceY1[0];
    }
    if(map->gateE != -1){
        int gateVal = map->gateE;
        entranceY2[0] = gateVal;
        //entranceY1[1] = COL - 1;
    } else {
        map->gateE = entranceY2[0];
    }

    int randX = rand() % (ROW-5+1-5) + 5;
    int randY = rand() % (COL-20+1-20) + 20;

    int connectionX1[2] = {randX, entranceX1[1]};
    int connectionX2[2] = {randX, entranceX2[1]};
    int connectionY1[2] = {entranceY1[0], randY};
    int connectionY2[2] = {entranceY2[0], randY};

    int a,b;
    //build roads for cols
    //Go down
    for (a=entranceX1[0]; a <= connectionX1[0]; a++){
        map->terrain[a][entranceX1[1]] = '#';
        //printf("1  %d     %d\n", a, entranceX1[1]);
    }
    //go sideways
    if(connectionX1[1] < connectionX2[1]){ //go left
        for(b=connectionX1[1]; b<=connectionX2[1]; b++){
            map->terrain[connectionX2[0]][b] = '#';
        }
    } else { //Go right
        for(b=connectionX1[1]; b>=connectionX2[1]; b--){
            map->terrain[connectionX2[0]][b] = '#';
        }
    }
    //Go down
    for (a=connectionX2[0]; a <= entranceX2[0]; a++){
        map->terrain[a][entranceX2[1]] = '#';
    }


    //Build rooads for rows
    //Go right
    for (a=entranceY1[1]; a <= connectionY1[1]; a++){
        map->terrain[entranceY1[0]][a] = '#';
    }
    //Go up or down
    if(connectionY1[0] < connectionY2[0]){ //go down
        for(b=connectionY1[0]; b<=connectionY2[0]; b++){
            map->terrain[b][connectionY1[1]] = '#';
        }
    } else { //Go up
        for(b=connectionY1[0]; b>=connectionY2[0]; b--){
            map->terrain[b][connectionY1[1]] = '#';
        }
    }    
    //Go right
     for (a=connectionY2[1]; a <= entranceY2[1]; a++){
        map->terrain[entranceY2[0]][a] = '#';
    }

    int oddsForBuilding = ((-45*distanceFromCenter)/200 + 50) / 100;

    //make pokemart
    int i, j;
    for(i = entranceX1[0]+1; i<entranceX1[0]+3; i++){
        for(j = entranceX1[1]+1; j<entranceX1[1]+3; j++){
            map->terrain[i][j] = 'M';
            // b++;
            // if (b == 4)
            //     break;
        }
    }

    for(i = entranceY1[0]+1; i<entranceY1[0]+3; i++){
        for(j = entranceY1[1]+1; j<entranceY1[1]+3; j++){
            map->terrain[i][j] = 'C';
            // b++;
            // if (b == 4)
            //     break;
        }
    }
    
}

void createTerrain(mapStruct *map){

    //assign biomes
    int grass1[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int grass2[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int water[2] =      {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing1[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing2[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int forest[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int mountain[2] =   {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};


    enqueue(grass1, GRASS);
    enqueue(water, WATER);
    enqueue(clearing1, CLEARING);
    enqueue(grass2, GRASS);
    enqueue(forest, TREE);
    enqueue(mountain, BOULDER);
    enqueue(clearing2, CLEARING);

    char currSeed;

    while (front != NULL) {
        int currCoord[2];
        int randVal = rand() % 10;
        
        dequeue(currCoord, &currSeed);
        //printf("%c", *currSeed);
        //map[currCoord[0]][currCoord[1]] = currSeed;
        // printMap();
        // printf("\n");
        //for loops variables
        if (randVal < 2){
            if (currCoord[0]+1 < ROW-1){
                if (map->terrain[currCoord[0]+1][currCoord[1]] == '_'){
                    int arr[2] = {currCoord[0]+1, currCoord[1]};
                    map->terrain[arr[0]][arr[1]] = currSeed;
                    enqueue(arr, currSeed);
                }
            }
            if (currCoord[0]-1 > 0){
                if (map->terrain[currCoord[0]-1][currCoord[1]] == '_'){
                    int arr[2] = {currCoord[0]-1, currCoord[1]};
                    map->terrain[arr[0]][arr[1]] = currSeed;
                    enqueue(arr, currSeed);
                }
            }
        }
        if (currCoord[1]+1 < COL-1){
            if (map->terrain[currCoord[0]][currCoord[1]+1] == '_'){
                int arr[2] = {currCoord[0], currCoord[1]+1};
                map->terrain[arr[0]][arr[1]] = currSeed;
                enqueue(arr, currSeed);
            }
        }
        if (currCoord[1]-1 > 0){
            if (map->terrain[currCoord[0]][currCoord[1]-1] == '_'){
                int arr[2] = {currCoord[0], currCoord[1]-1};
                map->terrain[arr[0]][arr[1]] = currSeed;
                enqueue(arr, currSeed);
            }
        }
    }

    

}

void setMap(mapStruct *map, int x, int y, worldMap *wm){
    int i;
    int j;
    for(i = 0; i < ROW; i++){
        for(j=0; j < COL; j++){
            if (i == 0 || i == ROW-1 || j == 0 || j == COL-1){
                map->terrain[i][j] = '%';
                continue;
            }
            map->terrain[i][j] = '_';
        }
    }
    map->gateN = -1;
    map->gateE = -1;
    map->gateW = -1;
    map->gateS = -1;

    if(x - 1 >= 0){
        if ((wm->arr[x-1][y]) != NULL){
            map->gateW = wm->arr[x-1][y]->gateE;
            printf("West Gate%d\n",wm->arr[x-1][y]->gateE);
        }
    }
    if(x + 1 < worldXSize){
        if ((wm->arr[x+1][y]) != NULL){
            map->gateE = wm->arr[x+1][y]->gateW;
            printf("East Gate%d\n",wm->arr[x+1][y]->gateW);
        }
    }
    if(y - 1 >= 0){
        if (wm->arr[x][y-1] != NULL){
            map->gateN = wm->arr[x][y-1]->gateS;
            printf("North Gate %d\n",wm->arr[x][y-1]->gateS);
        }
    }
    if(y + 1 < worldYSize){
        if (wm->arr[x][y+1] != NULL){
            map->gateS= wm->arr[x][y+1]->gateN;
            printf("South Gate %d\n",wm->arr[x][y+1]->gateN);

        }
    }
}

void createWorldMap(worldMap *wm){
    int i;
    int j;

    for(i=0; i<worldYSize; i++){
        for(j=0; j<worldXSize; j++){
            wm->arr[i][j] = NULL;
        }
    }
}



void createMap(int x, int y, worldMap *wm){
    
    mapStruct *newMap = malloc(sizeof(mapStruct));
    //char terrainMap[ROW][COL];
    //newMap->map = terrainMap;
    setMap(newMap, x, y, wm);;
    createTerrain(newMap);
    int distanceFromCenter = abs(x - 200) + abs(y - 200);
    makeRoads(newMap, distanceFromCenter);

    wm->arr[x][y] = newMap;


    printMap(newMap);
}

void fly(int x, int y, worldMap *wm){
    if (wm->arr[x][y] != NULL){
        printMap(wm->arr[x][y]);
    } else {
        createMap(x, y, wm);
    }
}

int main(int argc, char *argv[]){

    //srand(time(NULL));
    // setMap();
    // createTerrain();
    // printMap();
    worldMap wm;
    int currX = 200;
    int currY = 200;
    
    createWorldMap(&wm);
    createMap(currX, currY, &wm);

    char userChar;
    //userChar = getchar();
    printf("Move with 'e'ast, 'w'est, 'n'orth, 's'outh or 'f'ly x y.\n"
                        "Quit with 'q'.  and 'h' print this help message.\n");

    do{
        if (scanf(" %c", &userChar) != 1) {
            /* To handle EOF */
            putchar('\n');
            break;
        }
        switch (userChar) {
            case 'n':
                if(currY - 1 > -1){
                    currY--;
                    fly(currX, currY, &wm);
                } else {
                    printf("Can't go that way");
                }
                break;
            case 's':
                if(currY + 1 <  worldYSize){
                    currY++;
                    fly(currX, currY, &wm);
                } else {
                    printf("Can't go that way");
                }
                break;
            case 'e':
                if(currX + 1 < worldXSize){
                    currX++;
                    fly(currX, currY, &wm);
                } else {
                    printf("Can't go that way");
                }
                break;
            case 'w':
                if(currX - 1 > -1){
                    currX--;
                    fly(currX, currY, &wm);
                } else {
                    printf("Can't go that way");
                }
                break;
            case 'q':
                break;
            case 'f':
                int userX;
                int userY;
                printf("Enter x y coordinates\n");
                if (scanf(" %d %d", &userX, &userY) != 1) {
                    /* To handle EOF */
                    putchar('\n');
                    if(userX >= worldXSize || userX < 0 || userY >= worldYSize || userY < 0){
                        printf("invalid coordinates\n");
                    } else {
                        currX = userX;
                        currY = userY;
                        fly(currX, currY, &wm);
                    }
                    break;
                }
                break;
            case 'h':
                printf("Move with 'e'ast, 'w'est, 'n'orth, 's'outh or 'f'ly x y.\n"
                        "Quit with 'q'.  and 'h' print this help message.\n");
                break;
            default:
                fprintf(stderr, "%c: Invalid input.  Enter '?' for help.\n", userChar);
            break;
        }
    } while (userChar != 'q');
    
    
    return 0;
}