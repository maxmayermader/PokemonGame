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
int heapSize = 0;
void swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

// Function to heapify the tree
void heapify(int array[], int size, int i) {
  if (size == 1) {
    printf("Single element in the heap");
  } else {
    // Find the largest among root, left child and right child
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < heapSize && array[l] < array[smallest])
      smallest = l;
    if (r < heapSize && array[r] < array[smallest])
      smallest = r;

    // Swap and continue heapifying if root is not smallest
    if (smallest != i) {
      swap(&array[i], &array[smallest]);
      heapify(array, size, smallest);
    }
  }
}

// Function to insert an element into the tree
void insert(int array[], int newNum) {
  if (heapSize == 0) {
    array[0] = newNum;
    heapSize += 1;
  } else {
    array[heapSize] = newNum;
    heapSize += 1;
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
      heapify(array, heapSize, i);
    }
  }
}

// Function to delete an element from the tree
void deleteRoot(int array[], int num) {
  int i;
  for (i = 0; i < heapSize; i++) {
    if (num == array[i])
      break;
  }

  swap(&array[i], &array[heapSize - 1]);
  heapSize -= 1;
  for (int i = heapSize / 2 - 1; i >= 0; i--) {
    heapify(array, heapSize, i);
  }
}

//function to pop min

// Print the array
void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i)
    printf("%d ", array[i]);
  printf("\n");
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

    int array[10];

  insert(array, 3);
  printArray(array, heapSize);
  insert(array, 4);
  printArray(array, heapSize);
  insert(array, 9);
  printArray(array, heapSize);
  insert(array, 5);
  printArray(array, heapSize);
  insert(array, 0);
  printArray(array, heapSize);
  insert(array, 2);
  printArray(array, heapSize);
  insert(array, 1);
  printArray(array, heapSize);

  printf("Min-Heap array: ");
  printArray(array, heapSize);

  deleteRoot(array, 4);

  printf("After deleting an element: ");

  printArray(array, heapSize);
   
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