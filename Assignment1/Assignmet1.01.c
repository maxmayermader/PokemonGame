#include <stdio.h>

#define MAX_SIZE 100  
#define HEIGHT 21
#define WIDTH 80


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

void createMap(map){

}

//Prints map out to the terminal
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

    createMap(map);

    printMap(map);
    return 0;
}