#include <stdio.h>
#include <stdlib.h>
#include <math.h>



typedef struct node{
	int value;
	struct node *next;
}node;
typedef struct queue{
	node *front;
	node *reare;
}queue;
queue* creat_queue(queue **head ){
 (*head)=malloc(sizeof(queue));
 (*head)->front=NULL;
 (*head)->reare=NULL;
 return(*head);
}
void enqueue(queue *head,int value){
	node *p;
	p=malloc(sizeof(node));
		p->value=value;
			p->next=NULL;
	if(head->front==NULL){
		head->front=p;
		head->reare=p;}
		else{
			head->reare->next=p;
			head->reare=p;}}
void dequeue(queue *head){
	node *p;
	if(head->front==NULL)
	printf("the queue is empty");
	else{
	printf("%d",head->front->value);
	p=head->front;
	head->front=head->front->next;
	free(p);}}
void printQueue(queue *head){
	queue *p;
	node *q;
	int val;
	q=head->front;
	p->front=head->front;
	val=q->value;
	printf("\t %d",q->value);
	dequeue(p);
	enqueue(p,val);
	q=q->next;
	while(p->front!=head->front){
		val=q->value;
		dequeue(p);
	    enqueue(p,val);
	     q=q->next;
		
	}
	
	
}
