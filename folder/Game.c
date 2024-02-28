#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100  
#define ROW 21//21 //Y
#define COL 80//80 //X 
#define NPCROW (ROW - 2) //Y
#define NPCCOL (COL - 2) //X 
#define worldXSize 401
#define worldYSize 401
#define MAX_HEAP_SIZE 99999
#define INFINTY 99999

#define BOULDER '%'
#define TREE '^'
#define ROAD '#'
#define MART 'M'
#define CENTER 'C'
#define GRASS ':'
#define CLEARING '.'
#define WATER '~'
#define PLAYERCHAR '@'


//NPC struct
typedef struct NPC{
    int symb; //NPC type: Rival, Hiker etc
    int row; 
    int col;
    int weightArr[NPCROW][NPCCOL]; //weightMap. Might change it to pointer arr
}NPC;

//NPC Enums
typedef enum NPCSymb{
    HIKER,
    RIVAL,
    PACER,
    WANDERER,
    SENTRIES, 
    EXPLORERS
}NPCSymb;

//PC struct
typedef struct PC{
    int symb;
    int row;
    int col;
    int globalX;
    int globalY;
}PC;

//map struct for terrain. 21x80 map
typedef struct mapStruct{
	int gateN;//top
	int gateS;//bottom
	int gateW;//left
	int gateE;//right
	char terrain[ROW][COL];
    NPC* npcArray[NPCROW][NPCCOL];
    PC* playerT;
    int NPCSInit; 
}mapStruct;


//Global map. Array of map pointers
typedef struct worldMap{
    mapStruct* arr[worldYSize][worldXSize];
    PC* player;
}worldMap;

//char startMap[ROW][COL];
int queSize = 0;
int getQueSize(){
    return queSize;
}

//prototype declerations
    void createMap(int x, int y, worldMap *wm, int npcNum);
    void dijkstras(int row, int col, mapStruct* terrainMap, int weightArr[NPCROW][NPCCOL], int type);
    void printWeightMap(int weightArr[NPCROW][NPCCOL]);
    void moveCharecters(worldMap *wm, mapStruct *terrainMap, int numTrainers);
    int randomGenerator(int upper, int lower);
    int calcCost(int npc, char terrainType);
    
int randomGenerator(int upper, int lower){
  return (rand() % (upper - lower + 1)) + lower;
}

//Prints map out to the terminal
void printMap(mapStruct *map, PC *pc){
    int i;
    int j;
    for (i=0; i < ROW; i++){
        for(j=0; j < COL; j++){
            if(pc->row == i && pc->col == j){
                printf("%c", PLAYERCHAR);
                continue;
            } else if (i>0 && i<ROW-1 && j>0 && j<COL-1 && map->npcArray[i-1][j-1] != NULL){          
                char symbs[6] = {'h', 'r', 'p', 'w', 's', 'e'};
                int b;
                printf("%c", symbs[map->npcArray[i-1][j-1]->symb]);
                continue;
            }
            
            printf("%c", map->terrain[i][j]);
        }
        printf("\n");
    }

}


typedef struct heapNode {
    int weight;
    //for dijkstra
    int row;
    int col;
    int visited;
    //for moving
    NPC* npc;
    PC* pc;
} heapNode;

/*Begin heap implemantation*/
// Declare a heap structure
struct Heap {
    heapNode* arr[MAX_HEAP_SIZE];
    int size;
    //int capacity;
};
 // define the struct Heap name
typedef struct Heap heap;
 
// forward declarations
heap* createHeap();
void insertHelper(heap* h, int index);
void heapify(heap* h, int index);
heapNode* extractMin(heap* h);
void insert(heap* h, heapNode* data);
 
// Define a createHeap function
heap* createHeap()
{
    // Allocating memory to heap h
    heap* h = (heap*)malloc(sizeof(heap));
 
    // Checking if memory is allocated to h or not
    if (h == NULL) {
        printf("Memory error");
        return NULL;
    }
    // set the values to size and capacity
    h->size = 0;
    
    return h;
}
 
// Defining insertHelper function
void insertHelper(heap* hp, int index)
{
 
    // Store parent of element at index
    // in parent variable
    int parent = (index - 1) / 2;

    if(hp->arr[index]->row == 4251078){
        printf("bruhhhh\n");
    }
 
    if (hp->arr[parent]->weight > hp->arr[index]->weight) {
        // Swapping when child is smaller
        // than parent element
        heapNode* temp = hp->arr[parent];
        hp->arr[parent] = hp->arr[index];
        hp->arr[index] = temp;
 
        // Recursively calling insertHelper
        insertHelper(hp, parent);
    }
}
 
void heapify(heap* h, int index)
{
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;
 
    // Checking whether our left or child element
    // is at right index or not to avoid index error
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
 
    // store left or right element in min if
    // any of these is smaller that its parent
    if (left != -1 && h->arr[left]->weight < h->arr[index]->weight)
        min = left;
    if (right != -1 && h->arr[right]->weight < h->arr[min]->weight)
        min = right;
 
    // Swapping the nodes
    if (min != index) {
        heapNode* temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
 
        // recursively calling for their child elements
        // to maintain min heap
        heapify(h, min);
    }
}
 
 //potential leakage
 //TODO
heapNode* extractMin(heap* h){
    heapNode* deleteItem;
    
    // Checking if the heap is empty or not
    if (h->size == 0) {
        printf("\nHeap id empty.");
        return NULL;
    }
 
    // Store the node in deleteItem that
    // is to be deleted.
    deleteItem = h->arr[0];
 
    // Replace the deleted node with the last node
    h->arr[0] = h->arr[h->size - 1];
    // Decrement the size of heap
    //free(h->arr[h->size - 1]);
    h->size--;
 
    // Call minheapify_top_down for 0th index
    // to maintain the heap property
    //ret = deleteItem;
    heapify(h, 0);
    return deleteItem;
} 
 
// Define a insert function
void insert(heap* h, heapNode* data){
 
    // Checking if heap is full or not
    if (h->size < MAX_HEAP_SIZE) {
        // Inserting data into an array
        h->arr[h->size] = data;
        // Calling insertHelper function
        insertHelper(h, h->size);
        // Incrementing size of array
        h->size++;
    }
}

 
void printHeap(heap* h)
{
 
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->arr[i]->weight);
    }
    printf("\n");
}

void killHeap(heap* h){
    free(h);
}
/*End heap implementation*/

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
/////End Que Implemntation////




/*Code for creating roads and buildings*/
void makeRoads(mapStruct *map, int distanceFromCenter, int x, int y, worldMap* wm){
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
    
    //if(x == 200 && y == 200){
        wm->player->row = connectionX1[0];
        wm->player->col = connectionX1[1];
    //}

    //Close gates if at the edge
    if (y == 0)
        map->terrain[entranceX1[0]][entranceX1[1]] = '%';
    if(y == worldYSize-1)
        map->terrain[entranceX2[0]][entranceX2[1]] = '%';
    if (x == 0)
        map->terrain[entranceY1[0]][entranceY1[1]] = '%';
    if(x == worldXSize-1)
        map->terrain[entranceY2[0]][entranceY2[1]] = '%';


    int oddsForBuilding = ((-45*distanceFromCenter)/200 + 50);
    int chancesOutOf100 = rand() % 100 + 1;

    //Make pokemart
    if (distanceFromCenter == 0){
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
    } else if ( chancesOutOf100 <= oddsForBuilding && distanceFromCenter <= 200) { //away from center but distance is less than 200
        int i, j;
        for(i = entranceX1[0]+1; i<entranceX1[0]+3; i++){
            for(j = entranceX1[1]+1; j<entranceX1[1]+3; j++){
                map->terrain[i][j] = 'M';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    } else if (chancesOutOf100 <= 5){//flat 5% chance if 200 away from center
        int i, j;
        for(i = entranceX1[0]+1; i<entranceX1[0]+3; i++){
            for(j = entranceX1[1]+1; j<entranceX1[1]+3; j++){
                map->terrain[i][j] = 'M';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    }


    chancesOutOf100 = rand() % 100 + 1;
    //make Center
    if (distanceFromCenter == 0){//if at center
        int i, j;
        
        for(i = entranceY1[0]+1; i<entranceY1[0]+3; i++){
            for(j = entranceY1[1]+1; j<entranceY1[1]+3; j++){
                map->terrain[i][j] = 'C';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    } else if ( chancesOutOf100 <= oddsForBuilding && distanceFromCenter <= 200) { //away from center but distance is less than 200
        int i, j;
        
        for(i = entranceY1[0]+1; i<entranceY1[0]+3; i++){
            for(j = entranceY1[1]+1; j<entranceY1[1]+3; j++){
                map->terrain[i][j] = 'C';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    } else if (chancesOutOf100 <= 5){ //flat 5% chance if 200 away from center
        int i, j;
        
        for(i = entranceY1[0]+1; i<entranceY1[0]+3; i++){
            for(j = entranceY1[1]+1; j<entranceY1[1]+3; j++){
                map->terrain[i][j] = 'C';
                // b++;
                // if (b == 4)
                //     break;
            }
        }
    }
    
    
}

/*Randomly generate terrain*/
void createTerrain(mapStruct *map){

    //assign biomes or seeds
    int grass1[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int grass2[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int water[2] =      {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing1[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int clearing2[2] =  {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int forest[2] =     {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};
    int mountain[2] =   {rand() % (ROW - 2) + 1, rand() % (COL - 2) + 1};

    //add to que
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

/*Initilaize map to empty spaces and add border*/
void setMap(mapStruct *map, int x, int y, worldMap *wm){
    int i;
    int j;
    for(i = 0; i < ROW; i++){ //Set terrai  to null
        for(j=0; j < COL; j++){
            if (i == 0 || i == ROW-1 || j == 0 || j == COL-1){
                map->terrain[i][j] = '%';
                continue;
            }
            map->terrain[i][j] = '_';
        }
    }
    //set gates to NULL
    map->gateN = -1;
    map->gateE = -1;
    map->gateW = -1;
    map->gateS = -1;

    //check if there are gates to neighbours
    if(x - 1 >= 0){
        if ((wm->arr[x-1][y]) != NULL){
            map->gateW = wm->arr[x-1][y]->gateE;
            //printf("West Gate%d\n",wm->arr[x-1][y]->gateE);
        }
    }
    if(x + 1 < worldXSize){
        if ((wm->arr[x+1][y]) != NULL){
            map->gateE = wm->arr[x+1][y]->gateW;
            //printf("East Gate%d\n",wm->arr[x+1][y]->gateW);
        }
    }
    if(y - 1 >= 0){
        if (wm->arr[x][y-1] != NULL){
            map->gateN = wm->arr[x][y-1]->gateS;
            //printf("North Gate %d\n",wm->arr[x][y-1]->gateS);
        }
    }
    if(y + 1 < worldYSize){
        if (wm->arr[x][y+1] != NULL){
            map->gateS= wm->arr[x][y+1]->gateN;
            //printf("South Gate %d\n",wm->arr[x][y+1]->gateN);

        }
    }

    map->playerT = malloc(sizeof(PC));
    //set all NPCs to NULL
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            map->npcArray[i][j] = NULL;
        }
    }
    map->NPCSInit = 0;

}

/*Set all pointers to NULL*/
void createWorldMap(worldMap *wm){
    int i;
    int j;

    for(i=0; i<worldYSize; i++){
        for(j=0; j<worldXSize; j++){
            wm->arr[i][j] = NULL;
        }
    }
    //Initialize player
    wm->player = malloc(sizeof(PC));
    //wm->player->symb = 0;
    //wm->player->row = 10;
    //wm->player->col = 40;
    wm->player->globalX = 200;
    wm->player->globalY = 200;
}

/*spawns a pc in the terrain map*/
void spawnNPC(worldMap *wm, mapStruct *terrainMap, int npcType){
    int canPlace = -1;
    NPC* npc = malloc(sizeof(NPC));
    npc->symb = npcType;
    npcType = npcType == HIKER ? HIKER : 1;
    while (canPlace == -1){
        int row = randomGenerator(NPCROW-1, 0);
        int col = randomGenerator(NPCCOL-1, 0);
        if(calcCost(npcType, terrainMap->terrain[row+1][col+1]) != INFINTY){ //check of terrain is not infinty
            if((terrainMap->npcArray[row][col] == NULL)){ //&& (terrainMap->terrain[row+1][col+1] != 'M') && (terrainMap->terrain[row+1][col+1] != 'C')){ 
                terrainMap->npcArray[row][col] = npc;
                npc->row = row;
                npc->col = col;
                canPlace = 0;
            }
        }
    }
}

/*adds all npcs to terrain map array*/
void placeNPCS(worldMap *wm, mapStruct *terrainMap, int npcNum){
    if(npcNum>=2){
    spawnNPC(wm, terrainMap, HIKER);
    spawnNPC(wm, terrainMap, RIVAL);
    //if statements
    npcNum=npcNum-2;
    while (npcNum>0){
        if(npcNum == npcNum-100 || npcNum == 250-500 || npcNum == npcNum-750 || npcNum == npcNum-1000){
            printf("hello %d\n", npcNum);
        }
        printf("npcNum %d\n", npcNum);
        if(npcNum == 114){
            printf("bruh\n");
        }
      int npcType = randomGenerator(5,0);
      switch (npcType){
        case HIKER:
            spawnNPC(wm, terrainMap, HIKER);
            break;
        case RIVAL:
            spawnNPC(wm, terrainMap, RIVAL);
            break;
        case PACER:
            spawnNPC(wm, terrainMap, PACER);
            break;
        case WANDERER:
            spawnNPC(wm, terrainMap, WANDERER);
            break;
        case SENTRIES:
            spawnNPC(wm, terrainMap, SENTRIES);
            break;
        case EXPLORERS:
            spawnNPC(wm, terrainMap, EXPLORERS);
            break;
      }
         npcNum--;  

      }
  }else{
    while (npcNum>0){
      spawnNPC(wm, terrainMap, HIKER);
      npcNum--;  
    }
  }
    
}


/*Create a terrain map and add it to world map at position x y*/
void createMap(int x, int y, worldMap *wm, int npcNum){
    
    mapStruct *newMap = malloc(sizeof(mapStruct)); //malloc new mapStruct
    setMap(newMap, x, y, wm); //set mapStruct terrain to pseudo NULL values
    createTerrain(newMap); //create a terrain and set it to newMap
    int distanceFromCenter = abs(x - 200) + abs(y - 200);
    makeRoads(newMap, distanceFromCenter, x, y, wm);//add roads to map

    wm->arr[x][y] = newMap; //add new terrain map to world map

    //TODO : fix later
    newMap->playerT->row = wm->player->row;
    newMap->playerT->col = wm->player->col;

    if(newMap->NPCSInit == 0){
        placeNPCS(wm, newMap, npcNum);
        newMap->NPCSInit = 1;
    }

    printMap(newMap, wm->player); //print map and player
    
//     newMap->npcArray[0][0] = malloc(sizeof(NPC)); //Hiker
//     newMap->npcArray[0][1] = malloc(sizeof(NPC)); //Rival

//     newMap->npcArray[0][0]->symb = 0;
//     newMap->npcArray[0][1]->symb = 1;

//     dijkstras(wm->player->row, wm->player->col, wm->arr[x][y], newMap->npcArray[0][0]->weightArr, newMap->npcArray[0][0]->symb); //dijkstras for hiker
//     dijkstras(wm->player->row, wm->player->col, wm->arr[x][y], newMap->npcArray[0][1]->weightArr, newMap->npcArray[0][1]->symb); //dijkstras for rival

//     printf("Weights for hiker\n");
//     printWeightMap(wm->arr[x][y]->npcArray[0][0]->weightArr);

//     printf("Weights for rival\n");
//     printWeightMap(wm->arr[x][y]->npcArray[0][1]->weightArr);
}

/*Go to terrain map at x y*/
void fly(int x, int y, worldMap *wm, int npcNum){
    if (wm->arr[x][y] != NULL){
        printMap(wm->arr[x][y], wm->arr[x][y]->playerT);

        printf("Weights for hiker\n");
        printWeightMap(wm->arr[x][y]->npcArray[0][0]->weightArr);

        printf("Weights for rival\n");
        printWeightMap(wm->arr[x][y]->npcArray[1][0]->weightArr);
    } else {
        createMap(x, y, wm, npcNum);
    }
}

/*calc cost function. Get cost for NPC type*/
int calcCost(int npc, char terrainType){
    int terrainTypeInt;
    switch (terrainType){
        case ROAD:
            terrainTypeInt = 0;
            break;
        case 'M':
            terrainTypeInt = 1;
            break;
        case 'C':
            terrainTypeInt = 2;
            break;
        case GRASS:
            terrainTypeInt = 3;
            break;
        case CLEARING:
            terrainTypeInt = 4;
            break;
        case BOULDER:
            terrainTypeInt = 5;
            break;
        case TREE:
            terrainTypeInt = 6;
            break; 
        case WATER:
            terrainTypeInt = 7;
            break;
        default:
            printf("error. Uknown type of terrrain\n");
            break;
    }
                 // 0   1   2   3   4   5   6   7 
                 // P   M   C   T   S   M   F   W   
    int costArr[2][8] = {{10, 50, 50, 15, 10, 15, 15, INFINTY},               //Hiker
                         {10, 50, 50, 20, 10, INFINTY, INFINTY, INFINTY},};    //Rival and other

    return costArr[npc][terrainTypeInt];
}

/*Function for printing weightmap*/
void printWeightMap(int weightArr[NPCROW][NPCCOL]){
    int i,j;
    printf("\n");
    for(i=0; i<ROW; i++){
        for(j=0; j<COL; j++){
            if(i != 0 && i <= NPCROW && j != 0 && j <= NPCCOL){
                if(weightArr[i-1][j-1] != INFINTY){
                    printf("%2d ", weightArr[i-1][j-1]%100);
                } else {
                    printf("%2s ", "_");
                }
            } else {
                printf("%2s ", "B");
            }
        }
        printf("\n");
    }
}

/*Helper method for dijkstras. Sets all weigts to inity*/
void setWeights(int weightArr[NPCROW][NPCCOL]){
    int i,j;
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            weightArr[i][j] = INFINTY;
        }
    }
}

void makeHeapNodeData(heapNode* HN, int i, int j, int type, mapStruct* terrainMap){
    //heapNode HN;
  
    HN->row = i;
    HN->col = j;
    HN->weight = calcCost(type, terrainMap->terrain[i+1][j+1]);
    HN->visited = -1;
    //HN = HN1;
    //return &HN;
}

void initHeapNodeDatat(heapNode* HNArr[NPCROW][NPCCOL]){
    int i,j;
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            heapNode* HN = malloc(sizeof(heapNode));
            HN->row = -1;
            HN->col = -1;
            HN->weight = INFINTY;
            HN->visited = -1;
            HNArr[i][j] = HN;
        }
    }
}

/*Function for implemnting dijkstras algorthm. Finds all shortest paths staring at PC depending on NPC type*/
void dijkstras(int row, int col, mapStruct* terrainMap, int weightArr[NPCROW][NPCCOL], int type){
    //Initilaize var
    int i,j;
    heap* h = createHeap();
    heapNode* HNArr[NPCROW][NPCCOL]; //heapNodes array if pointers

    setWeights(weightArr); //Set all weights to infinty
    initHeapNodeDatat(HNArr); //Set all heap nodes to null
    
    

    //add all weights to heapNode
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            makeHeapNodeData(HNArr[i][j], i, j, type, terrainMap);
        }
    }

    //printWeightMap(weightArr);
    //Set player pos weight to 0
    weightArr[row-1][col-1] = 0;
    insert(h, HNArr[row-1][col-1]);
    //int heapRunCount=0;

    while(h->size > 0){
        heapNode* HN = extractMin(h);

        if(HN->visited == 0)//if visited skip
            continue;

        HN->visited = 0; //set node to visited

         // Check all neighboring nodes to see if their distances need to be updated.
        if (HN->row-1 >= 0){ //Up
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row-1][HN->col]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row-1][HN->col]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row-1][HN->col] = tentativeDistance;
                insert(h, HNArr[HN->row-1][HN->col]); //enque neighbour
            }
        }

        if (HN->row-1 >= 0 && HN->col+1 < NPCCOL){ //Diagonal up-right
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row-1][HN->col+1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row-1][HN->col+1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row-1][HN->col+1] = tentativeDistance;
                insert(h, HNArr[HN->row-1][HN->col+1]); //enque neighbour
            }
        }

        if (HN->col + 1 < NPCCOL){ //Right
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row][HN->col+1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row][HN->col+1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row][HN->col+1] = tentativeDistance;
                insert(h, HNArr[HN->row][HN->col+1]); //enque neighbour
            }
        }

        if (HN->row+1 < NPCROW && HN->col+1 < NPCCOL){ //Down right
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row+1][HN->col+1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row+1][HN->col+1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row+1][HN->col+1] = tentativeDistance;
                insert(h, HNArr[HN->row+1][HN->col+1]); //enque neighbour
            }
        }

        if (HN->row+1 < NPCROW){ //Down
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row+1][HN->col]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row+1][HN->col]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row+1][HN->col] = tentativeDistance;
                insert(h, HNArr[HN->row+1][HN->col]); //enque neighbour
            }
        }

        if (HN->row+1 < NPCROW && HN->col-1 >= 0){  //Down Left
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row+1][HN->col-1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row+1][HN->col-1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row+1][HN->col-1] = tentativeDistance;
                insert(h, HNArr[HN->row+1][HN->col-1]); //enque neighbour
            }
        }

        if (HN->col-1 >= 0){ //Left
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row][HN->col-1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row][HN->col-1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row][HN->col-1] = tentativeDistance;
                insert(h, HNArr[HN->row][HN->col-1]); //enque neighbour
            }
        }

        if (HN->row-1 >= 0 && HN->col-1 >= 0){ //Up left
            int tentativeDistance = weightArr[HN->row][HN->col] + HNArr[HN->row-1][HN->col-1]->weight; // Calculate the tentative distance to the neighbor through the current node.
            if(tentativeDistance < weightArr[HN->row-1][HN->col-1]){ // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
                weightArr[HN->row-1][HN->col-1] = tentativeDistance;
                insert(h, HNArr[HN->row-1][HN->col-1]); //enque neighbour
            }
        }
        //heapRunCount++;
    }
    killHeap(h);
}

void moveNPC(worldMap *wm, mapStruct *terrainMap, NPC* npc){

}

void moveEveryone(worldMap *wm, mapStruct *terrainMap, int numTrainers){
    /*
    init heap
    add player to heap
    init players if not
        add players to que

    move everyone based on move weight
        get next position
        get cost
    print when players turn
    move player in square for now
    */
    heap* h = createHeap();
    heapNode* hnNPC = malloc(sizeof(heapNode));
    hnNPC->npc=NULL;
    hnNPC->pc=wm->player;
    hnNPC->weight=0;
    insert(h, hnNPC);
    int i,j;
    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            if(terrainMap->npcArray[i][j] != NULL){
                heapNode* hn = malloc(sizeof(heapNode));
                hn->npc = terrainMap->npcArray[i][j];
                hn->pc = NULL;
                hn->weight = 0;
                insert(h, hn);
            }
        }
    }

    while(h->size > 0){
        heapNode* hn = extractMin(h);
        if(hn->pc != NULL){

        } else {
            moveNPC(wm, terrainMap, hn->npc);
        }
    }

    
return;
   
}

int main(int argc, char *argv[]){

    //srand(time(NULL));//random seed

   
    worldMap wm;
    int currX = 200;
    int currY = 200;
    int numTrainers = 1100;


    
    
    createWorldMap(&wm);
    createMap(currX, currY, &wm, numTrainers);
    printf("(%d, %d)\n", currX-200, currY-200);

    moveEveryone(&wm, wm.arr[200][200], numTrainers);


    // char userChar;
    // //userChar = getchar();
    // printf("Move with 'e'ast, 'w'est, 'n'orth, 's'outh or 'f'ly x y.\n"
    //                     "Quit with 'q'.  and 'h' print this help message.\n");

    // do{
    //     if (scanf(" %c", &userChar) != 1) {
    //         /* To handle EOF */
    //         putchar('\n');
    //         break;
    //     }
    //     switch (userChar) {
    //         case 'n':
    //             if(currY - 1 > -1){
    //                 currY--;
    //                 fly(currX, currY, &wm, numTrainers);
    //                 printf("(%d, %d)\n", currX-200, currY-200);
    //             } else {
    //                 printf("Can't go that way\n");
    //             }
    //             break;
    //         case 's':
    //             if(currY + 1 <  worldYSize){
    //                 currY++;
    //                 fly(currX, currY, &wm, numTrainers);
    //                 printf("(%d, %d)\n", currX-200, currY-200);
    //             } else {
    //                 printf("Can't go that way\n");
    //             }
    //             break;
    //         case 'e':
    //             if(currX + 1 < worldXSize){
    //                 currX++;
    //                 fly(currX, currY, &wm, numTrainers);
    //                 printf("(%d, %d)\n", currX-200, currY-200);
    //             } else {
    //                 printf("Can't go that way\n");
    //             }
    //             break;
    //         case 'w':
    //             if(currX - 1 > -1){
    //                 currX--;
    //                 fly(currX, currY, &wm, numTrainers);
    //                 printf("(%d, %d)\n", currX-200, currY-200);
    //             } else {
    //                 printf("Can't go that way\n");
    //             }
    //             break;
    //         case 'q':
    //             break;
    //         case 'f':
    //             int userX;
    //             int userY;
    //             printf("Enter x y coordinates\n");
    //             if (scanf(" %d %d", &userX, &userY) != 1) {
    //                 /* To handle EOF */
    //                 putchar('\n');
    //                 userX+=200;
    //                 userY+=200;
    //                 if(userX >= worldXSize || userX < 0 || userY >= worldYSize || userY < 0){
    //                     printf("invalid coordinates\n");
    //                 } else {
    //                     currX = userX;
    //                     currY = userY;
    //                     fly(currX, currY, &wm, numTrainers);
    //                 }
    //                 printf("(%d, %d)\n", currX-200, currY-200);
    //                 break;
    //             }
    //             break;
    //         case 'h':
    //             printf("Move with 'e'ast, 'w'est, 'n'orth, 's'outh or 'f'ly x y.\n"
    //                     "Quit with 'q'.  and 'h' print this help message.\n");
    //             break;
    //         default:
    //             fprintf(stderr, "%c: Invalid input.  Enter 'h' for help.\n", userChar);
    //         break;
    //     }
    // } while (userChar != 'q');
    
    
    return 0;
}