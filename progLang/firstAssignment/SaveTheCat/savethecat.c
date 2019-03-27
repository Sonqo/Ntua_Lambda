#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Constructing Queue */
struct Queue{
	int line;
	int column;
	char symbol;
	int time;
	char* position;
	struct Queue *next;
};

struct Queue *front = NULL;
struct Queue *rear = NULL;

/* Functions For Queue */
void enqueue(int x, int y, char ch, int time, char* pos){
	struct Queue *nptr = malloc(sizeof(struct Queue));
	nptr->line = x;
	nptr->column = y;
	nptr->symbol = ch;
	nptr->time = time;
	nptr->position = pos;
	nptr->next = NULL;
	if (rear == NULL){
    	front = nptr;
    	rear = nptr;
	}
	else{
    	rear->next = nptr;
    	rear = rear->next;
	}
}

void dequeue(){
	if (front == NULL){
    	printf("\n\n Queue is empty \n");
	}
	else{
    	struct Queue *temp;
    	temp = front;
    	front = front->next;
    	free(temp);
	}
}

void display(){
	struct Queue *temp;
	temp = front;
	while (temp != NULL){
    	printf("%c ", temp->symbol);
    	printf("%s ", temp->position);
    	printf("\n");
    	temp = temp->next;
	}
}

/* Constructing Stack */


int main(int argc, char *argv[]) {
	
	/* Variables Declaration */
	int i, j, N, M, flag;
	char ch;
	
	FILE *fp = fopen(argv[1], "r");
	
	/* Lines and columns calculation */
	flag = 0;
	N = 0;
	M = 0;
	while (!feof(fp)){
		ch = fgetc(fp);
		if(ch == '\n'){
			N++;
			flag = 1;
		}
		if (flag == 0){
			M++;
		}
	}
	fclose (fp);
	char array[N+2][M+2];	
	
	/* File reading and map filling */
	flag = 0;
	fp = fopen(argv[1], "r");
	for (i = 1; i <= N+1; i++){
		for (j = 1; j <= M+1; j++){
			ch = fgetc(fp);	
			array[i][j] = ch;
			if (ch == 'W'){
				int time = 0;
				flag = 1;
				enqueue(i, j, ch, time, "");
			}
			if (ch == 'A'){
				int time = 0;
				enqueue(i, j, ch, time, "");
			}
		}
	}
		
	/* Border creation of X's */
	for (i = 0; i < M+2; i++){
		array[0][i] = 'X';
		array[N+1][i] = 'X';
	}
	
	for (i = 0; i < N+2; i++){
		array[i][0] = 'X';
		array[i][M+1] = 'X';
	}	
	
    /* Printing for testing */
	for (i = 0; i < N+2; i++){
		for (j = 0; j < M+2; j++){
			printf("%c ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	int global_time = 0;
	int time = front->time;
	int arjumand = 0;
	
	char* right = "R";
	char* left = "L";
	char* up = "U";
	char* down = "D";
		
	/* Floodfill Algorithm */
	while ((front != NULL) && (flag != 0)){
		while (global_time == time){
			int line = front->line;
			int column = front->column;
			char item = front->symbol;
			char* pos = front->position;
			/* Cross Elements for the tested item */
			char item_east = array[line][column+1];
			char item_west = array[line][column-1];
			char item_north = array[line-1][column];
			char item_south = array[line+1][column];
			if (item == 'W'){
				if ((item_east != 'W') && (item_east != 'X')){
					array[line][column+1] = item;
					enqueue(line, column+1, item, time+1, "");	
				}			
				if ((item_west != 'W') && (item_west != 'X')){
					array[line][column-1] = item;
					enqueue(line, column-1, item, time+1, "");	
				}				
				if ((item_north != 'W') && (item_north != 'X')){
					array[line-1][column] = item;
					enqueue(line-1, column, item, time+1, "");	
				}
				if ((item_south != 'W') && (item_south != 'X')){
					array[line+1][column] = item;
					enqueue(line+1, column, item, time+1, "");	
				}
			}
			dequeue();
			
			/* If queue is not empty, go to the next element */
			if (front != NULL){
				time = front->time;
			}
			else{
				global_time = -1;
			}
		}

		
		/* Printing for testing */
		for (i = 0; i < N+2; i++){
			for (j = 0; j < M+2; j++){
				printf("%c ", array[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		
		display();
		
		global_time++;
		if (arjumand == 1){
			while (front != NULL){
				dequeue();
			}
		}
	}
	
	/* Print latest possible time for Arjumand */
	if (flag == 0){
		printf("infinity\n");
		printf("stay\n");
	} 
	
	if (global_time != 0){
		printf("%d", global_time);
	}
	printf("\n");
	
	printf("\n");
	
	for (i = 0; i < N+2; i++){
		for (j = 0; j < M+2; j++){
			printf("%c ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	return 0;
}
