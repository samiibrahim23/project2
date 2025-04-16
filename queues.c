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
int peek(queue *head){
	if(head->front==NULL)
	return(-1);
	return(head->front->value);
}
void print(queue *head){
		node *p;
		p=head->front;
		while(p!=NULL){
		printf("%d",p->value);
		if(p->next!=NULL)
		printf("-->");
		p=p->next;}}
int main(int argc, char *argv[]) {
    queue *head = NULL;
    creat_queue(&head);
    enqueue(head,1);
    enqueue(head,4);
    enqueue(head,3);
    enqueue(head,2);
    print(head);

    return 0;}
