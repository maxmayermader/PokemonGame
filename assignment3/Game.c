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

/*Begin heap implemantation*/
typedef struct MinHeap MinHeap;
struct MinHeap {
    int* arr;
    // Current Size of the Heap
    int size;
    // Maximum capacity of the heap
    int capacity;
};

int parent(int i) {
    // Get the index of the parent
    return (i - 1) / 2;
}

int left_child(int i) {
    return (2*i + 1);
}

int right_child(int i) {
    return (2*i + 2);
}

int get_min(MinHeap* heap) {
    // Return the root node element,
    // since that's the minimum
    return heap->arr[0];
}

MinHeap* init_minheap(int capacity) {
    MinHeap* minheap = (MinHeap*) calloc (1, sizeof(MinHeap));
    minheap->arr = (int*) calloc (capacity, sizeof(int));
    minheap->capacity = capacity;
    minheap->size = 0;
    return minheap;
}

MinHeap* insert_minheap(MinHeap* heap, int element) {
    // Inserts an element to the min heap
    // We first add it to the bottom (last level)
    // of the tree, and keep swapping with it's parent
    // if it is lesser than it. We keep doing that until
    // we reach the root node. So, we will have inserted the
    // element in it's proper position to preserve the min heap property
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Cannot insert %d. Heap is already full!\n", element);
        return heap;
    }
    // We can add it. Increase the size and add it to the end
    heap->size++;
    heap->arr[heap->size - 1] = element;

    // Keep swapping until we reach the root
    int curr = heap->size - 1;
    // As long as you aren't in the root node, and while the 
    // parent of the last element is greater than it
    while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr]) {
        // Swap
        int temp = heap->arr[parent(curr)];
        heap->arr[parent(curr)] = heap->arr[curr];
        heap->arr[curr] = temp;
        // Update the current index of element
        curr = parent(curr);
    }
    return heap; 
}

MinHeap* heapify(MinHeap* heap, int index) {
    // Rearranges the heap as to maintain
    // the min-heap property
    if (heap->size <= 1)
        return heap;
    
    int left = left_child(index); 
    int right = right_child(index); 

    // Variable to get the smallest element of the subtree
    // of an element an index
    int smallest = index; 
    
    // If the left child is smaller than this element, it is
    // the smallest
    if (left < heap->size && heap->arr[left] < heap->arr[index]) 
        smallest = left; 
    
    // Similarly for the right, but we are updating the smallest element
    // so that it will definitely give the least element of the subtree
    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) 
        smallest = right; 

    // Now if the current element is not the smallest,
    // swap with the current element. The min heap property
    // is now satisfied for this subtree. We now need to
    // recursively keep doing this until we reach the root node,
    // the point at which there will be no change!
    if (smallest != index) 
    { 
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[smallest];
        heap->arr[smallest] = temp;
        heap = heapify(heap, smallest); 
    }

    return heap;
}

MinHeap* delete_minimum(MinHeap* heap) {
    // Deletes the minimum element, at the root
    if (!heap || heap->size == 0)
        return heap;

    int size = heap->size;
    int last_element = heap->arr[size-1];
    
    // Update root value with the last element
    heap->arr[0] = last_element;

    // Now remove the last element, by decreasing the size
    heap->size--;
    size--;

    // We need to call heapify(), to maintain the min-heap
    // property
    heap = heapify(heap, 0);
    return heap;
}

MinHeap* delete_element(MinHeap* heap, int index) {
    // Deletes an element, indexed by index
    // Ensure that it's lesser than the current root
    heap->arr[index] = get_min(heap) - 1;
    
    // Now keep swapping, until we update the tree
    int curr = index;
    while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr]) {
        int temp = heap->arr[parent(curr)];
        heap->arr[parent(curr)] = heap->arr[curr];
        heap->arr[curr] = temp;
        curr = parent(curr);
    }

    // Now simply delete the minimum element
    heap = delete_minimum(heap);
    return heap;
}

void print_heap(MinHeap* heap) {
    // Simply print the array. This is an
    // inorder traversal of the tree
    printf("Min Heap:\n");
    for (int i=0; i<heap->size; i++) {
        printf("%d -> ", heap->arr[i]);
    }
    printf("\n");
}

void free_minheap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
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
    if (y != 0){
        for (a=entranceX1[0]; a <= connectionX1[0]; a++){
            map->terrain[a][entranceX1[1]] = '#';
            //printf("1  %d     %d\n", a, entranceX1[1]);
        }
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
    if(y != worldYSize-1){
        for (a=connectionX2[0]; a <= entranceX2[0]; a++){
            map->terrain[a][entranceX2[1]] = '#';
        }
    }


    //Build rooads for rows
    //Go right
    if(x != 0){
        for (a=entranceY1[1]; a <= connectionY1[1]; a++){
            map->terrain[entranceY1[0]][a] = '#';
        }
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
    if (x != worldXSize-1){
        for (a=connectionY2[1]; a <= entranceY2[1]; a++){
            map->terrain[entranceY2[0]][a] = '#';
        }
    }

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

int main(int argc, char *argv[]){

    srand(time(NULL));//random seed

   
    worldMap wm;
    int currX = 200;
    int currY = 200;
    
    createWorldMap(&wm);
    createMap(currX, currY, &wm);
    printf("(%d, %d)\n", currX-200, currY-200);

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