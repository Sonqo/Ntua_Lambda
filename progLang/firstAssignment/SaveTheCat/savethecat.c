#include <stdio.h>
#include <stdlib.h>

/* Struct Queue */
struct node{
	int line;
	int column;
	char symbol;
	int time;
	int visit;
	struct node *next;
};

struct node *front = NULL;
struct node *rear = NULL;

/* Functions of Queue */
void enqueue(int x, int y, char ch, int time){
	struct node *nptr = malloc(sizeof(struct node));
	nptr->line = x;
	nptr->column = y;
	nptr->symbol = ch;
	nptr->time = time;
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
    	struct node *temp;
    	temp = front;
    	front = front->next;
    	free(temp);
	}
}

void display(){
	struct node *temp;
	temp = front;
	while (temp != NULL){
    	printf("%c ", temp->symbol);
    	temp = temp->next;
	}
}

int main(int argc, char *argv[]) {
	
	/* Variables Declaration */
	int i, j, N, M, flag;
	char ch;
	
	FILE *fp = fopen(argv[1], "r");
	
	/* Lines and Columns Calculation */
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
	
	/* File Reading and Array Filling */
	fp = fopen(argv[1], "r");
	for (i = 1; i <= N+1; i++){
		for (j = 1; j <= M+1; j++){
			ch = fgetc(fp);	
			array[i][j] = ch;
			if ((ch == 'W')){
				int time = 0;
				enqueue(i, j, ch, time);
			}
		}
	}
		
	/* Border Creation of X's */
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
	
	/* Floodfill Algorithm */
	while (front != NULL){
		while (global_time == time){
			int line = front->line;
			int column = front->column;
			char item = front->symbol;
			/* Border Elements of Tested Item */
			char item_east = array[line][column+1];
			char item_west = array[line][column-1];
			char item_north = array[line-1][column];
			char item_south = array[line+1][column];
			if (item == 'W'){
				if ((item_east != 'W') && (item_east != 'X') && (item_east != 'A')){
					array[line][column+1] = item;
					enqueue(line, column+1, item, time+1);	
				}
				else if (item_east == 'A'){
					array[line][column+1] = 'A';
					arjumand = 1;
				}
				if ((item_west != 'W') && (item_west != 'X') && (item_west != 'A')){
					array[line][column-1] = item;
					enqueue(line, column-1, item, time+1);	
				}
				else if (item_west == 'A'){
					array[line][column-1] = 'A';
					arjumand = 1;
				}
				if ((item_north != 'W') && (item_north != 'X') && (item_north != 'A')){
					array[line-1][column] = item;
					enqueue(line-1, column, item, time+1);	
				}
				else if (item_north == 'A'){
					array[line-1][column] = 'A';
					arjumand = 1;
				}
				if ((item_south != 'W') && (item_south != 'X') && (item_south != 'A')){
					array[line+1][column] = item;
					enqueue(line+1, column, item, time+1);	
				}
				else if (item_south == 'A'){
					array[line+1][column] = 'A';
					arjumand = 1;
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
		global_time++;
		if (arjumand == 1){
			while (front != NULL){
				dequeue();
			}
		}
	}
	
	/* Print latest possible time for Arjumand */
	if (global_time != 0){
		printf("%d", global_time);
	}
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
