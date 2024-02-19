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
#define MAX_HEAP_SIZE 1482
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
    int symb;
    int row;
    int col;
}NPC;

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
    NPC npcArray[5];
}mapStruct;


//Global map. Array of map pointers
typedef struct worldMap{
    mapStruct* arr[worldYSize][worldXSize];
    PC player;
}worldMap;

//char startMap[ROW][COL];
int queSize = 0;
int getQueSize(){
    return queSize;
}

//forward declerations
    void createMap(int x, int y, worldMap *wm);
    void dijkstras(int row, int col, mapStruct* terrainMap, int weightArr[NPCROW][NPCCOL], int type);
    

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


typedef struct heapNode {
    int row;
    int col;
    int weight;
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
    //h->capacity = capacity;
 
    // Allocating memory to array
    //h->arr = (heapNode*)malloc(capacity * sizeof(heapNode));
 
    // Checking if memory is allocated to h or not
    // if (h->arr == NULL) {
    //     printf("Memory error");
    //     return NULL;
    // }
    //int i=0;
    // for (i = 0; i < capacity; i++) {
    //     h->arr[i] = nodes[i];
    // }
 
    //h->size = i;
    // int i = (h->size - 2) / 2;
    // while (i >= 0) {
    //     heapify(h, i);
    //     i--;
    // }
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
void makeRoads(mapStruct *map, int distanceFromCenter, int x, int y){
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
}


/*Create a terrain map and add it to world map at position x y*/
void createMap(int x, int y, worldMap *wm){
    
    mapStruct *newMap = malloc(sizeof(mapStruct));
    setMap(newMap, x, y, wm);;
    createTerrain(newMap);
    int distanceFromCenter = abs(x - 200) + abs(y - 200);
    makeRoads(newMap, distanceFromCenter, x, y);

    wm->arr[x][y] = newMap;

    printMap(newMap);
}

/*Go to terrain map at x y*/
void fly(int x, int y, worldMap *wm){
    if (wm->arr[x][y] != NULL){
        printMap(wm->arr[x][y]);
    } else {
        createMap(x, y, wm);
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
                         {10, 50, 50, 20, 10, INFINTY, INFINTY, INFINTY}};    //Rival

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
                    printf("%d ", weightArr[i-1][j-1]);
                } else {
                    printf("_ ");
                }
            } else {
                printf("B ");
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
            HNArr[i][j] = HN;
        }
    }
}

/*
function Dijkstra(Graph, source):
   // Initialize distances to all nodes as infinity, except for the source node.
   distances = map infinity to all nodes
   distances = 0

   // Initialize an empty set of visited nodes and a priority queue to keep track of the nodes to visit.
   visited = empty set
   queue = new PriorityQueue()
   queue.enqueue(source, 0)

   // Loop until all nodes have been visited.
   while queue is not empty:
       // Dequeue the node with the smallest distance from the priority queue.
       current = queue.dequeue()

       // If the node has already been visited, skip it.
       if current in visited:
           continue

       // Mark the node as visited.
       visited.add(current)

       // Check all neighboring nodes to see if their distances need to be updated.
       for neighbor in Graph.neighbors(current):
           // Calculate the tentative distance to the neighbor through the current node.
           tentative_distance = distances[current] + Graph.distance(current, neighbor)

           // If the tentative distance is smaller than the current distance to the neighbor, update the distance.
           if tentative_distance < distances[neighbor]:
               distances[neighbor] = tentative_distance

               // Enqueue the neighbor with its new distance to be considered for visitation in the future.
               queue.enqueue(neighbor, distances[neighbor])

   // Return the calculated distances from the source to all other nodes in the graph.
   return distances
*/
void dijkstras(int row, int col, mapStruct* terrainMap, int weightArr[NPCROW][NPCCOL], int type){
    //Initilaize var
    int i,j;
    heap* h = createHeap();
    heapNode* HNArr[NPCROW][NPCCOL];

    setWeights(weightArr); //Set all weights to infinty
    initHeapNodeDatat(HNArr);
    
    


    for(i=0; i<NPCROW; i++){
        for(j=0; j<NPCCOL; j++){
            //heapNode data;
            // data.row = i;
            // data.col = j;
            // data.weight = calcCost(type, terrainMap->terrain[i+1][j+1]); //get weight
            // HNArr[i][j]->row = i;
            // HNArr[i][j]->col = j;
            // HNArr[i][j]->weight = calcCost(type, terrainMap->terrain[i+1][j+1]);
            makeHeapNodeData(HNArr[i][j], i, j, type, terrainMap);
            if(HNArr[i][j]->row == 4251078 || (i == 18 && j == 76)){
                printf("its broken\n");
            }
            
            insert(h, HNArr[i][j]); //insert data into heap
        }
    }

    printWeightMap(weightArr);
    //Set player pos weight to 0
    weightArr[row-1][col-1] = 0;

    int heapRunCount=0;
    heapNode* lastNode = h->arr[h->size-1];

    while(h->size > 0){
        heapNode* HN = extractMin(h);

        if (HN->row-1 >= 0){ //Up
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row-1][HN->col];
            if(alt < weightArr[HN->row-1][HN->col]){
                weightArr[HN->row-1][HN->col] = alt;
            }
        }

        if (HN->row-1 >= 0 && HN->col+1 < NPCCOL){ //Diagonal up-right
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row-1][HN->col+1];
            if(alt < weightArr[HN->row-1][HN->col+1]){
                weightArr[HN->row-1][HN->col+1] = alt;
            }
        }

        if (HN->col + 1 < NPCCOL){ //Right
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row][HN->col+1];
            if(alt < weightArr[HN->row][HN->col+1]){
                weightArr[HN->row][HN->col+1] = alt;
            }
        }

        if (HN->row+1 < NPCROW && HN->col+1 < NPCCOL){ //Down right
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row+1][HN->col+1];
            if(alt < weightArr[HN->row+1][HN->col+1]){
                weightArr[HN->row+1][HN->col+1] = alt;
            }
        }

        if (HN->row+1 < NPCROW){ //Down
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row+1][HN->col];
            if(alt < weightArr[HN->row+1][HN->col]){
                weightArr[HN->row+1][HN->col] = alt;
            }
        }

        if (HN->row+1 < NPCROW && HN->col-1 >= 0){  //Down Left
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row+1][HN->col-1];
            if(alt < weightArr[HN->row+1][HN->col-1]){
                weightArr[HN->row+1][HN->col-1] = alt;
            }
        }

        if (HN->col-1 >= 0){ //Left
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row][HN->col-1];
            if(alt < weightArr[HN->row][HN->col-1]){
                weightArr[HN->row][HN->col-1] = alt;
            }
        }

        if (HN->row-1 >= 0 && HN->col-1 >= 0){ //Up left
            int alt = weightArr[HN->row][HN->col] + weightArr[HN->row-1][HN->col-1];
            if(alt < weightArr[HN->row-1][HN->col-1]){
                weightArr[HN->row-1][HN->col-1] = alt;
            }
        }

        heapRunCount++;
        lastNode = h->arr[h->size-1];
        //printWeightMap(weightArr);
    }


    killHeap(h);
}

int main(int argc, char *argv[]){

    //srand(time(NULL));//random seed

   
    worldMap wm;
    int currX = 200;
    int currY = 200;


    
    
    createWorldMap(&wm);
    createMap(currX, currY, &wm);
    printf("(%d, %d)\n", currX-200, currY-200);

    int wArr[NPCROW][NPCCOL];
    
    

    dijkstras(10, 25, wm.arr[200][200], wArr, 0);
    printWeightMap(wArr);

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
                    printf("(%d, %d)\n", currX-200, currY-200);
                } else {
                    printf("Can't go that way\n");
                }
                break;
            case 's':
                if(currY + 1 <  worldYSize){
                    currY++;
                    fly(currX, currY, &wm);
                    printf("(%d, %d)\n", currX-200, currY-200);
                } else {
                    printf("Can't go that way\n");
                }
                break;
            case 'e':
                if(currX + 1 < worldXSize){
                    currX++;
                    fly(currX, currY, &wm);
                    printf("(%d, %d)\n", currX-200, currY-200);
                } else {
                    printf("Can't go that way\n");
                }
                break;
            case 'w':
                if(currX - 1 > -1){
                    currX--;
                    fly(currX, currY, &wm);
                    printf("(%d, %d)\n", currX-200, currY-200);
                } else {
                    printf("Can't go that way\n");
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
                    userX+=200;
                    userY+=200;
                    if(userX >= worldXSize || userX < 0 || userY >= worldYSize || userY < 0){
                        printf("invalid coordinates\n");
                    } else {
                        currX = userX;
                        currY = userY;
                        fly(currX, currY, &wm);
                    }
                    printf("(%d, %d)\n", currX-200, currY-200);
                    break;
                }
                break;
            case 'h':
                printf("Move with 'e'ast, 'w'est, 'n'orth, 's'outh or 'f'ly x y.\n"
                        "Quit with 'q'.  and 'h' print this help message.\n");
                break;
            default:
                fprintf(stderr, "%c: Invalid input.  Enter 'h' for help.\n", userChar);
            break;
        }
    } while (userChar != 'q');
    
    
    return 0;
}