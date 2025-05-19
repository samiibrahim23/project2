#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include <unistd.h>
#include"stackfile.h"


TStack createstack(){
    TStack stack1=(sizeof(stack));
    stack1->top=NULL;
    return stack1;
}
bool isempty(TStack stk){
    if(stk->top==NULL)
    return true ;
    return false;
}
void push(TStack stk,TList node){
    if(isempty(stk)){
        stk->top=copyNode(node);
        return;
    }
    TList temp=copyNode(node);
    temp->next=stk->top;
    stk->top=temp;
    return ;

}
TList pop(TStack stk){
    if(!isempty(stk)){
        TList popednode=copyNode(stk->top);
        TList temp=stk->top;
        temp->next=NULL;
        stk->top=stk->top->next;
        free(temp);
        return popednode;
    }
    return NULL;

}
TList peek(TStack stk) {
    if (!isempty(stk)) {
        return stk->top;  
    }
    return NULL;
}
TStack toStack(TListBD merged){
    TStack result=createstack();
    while(merged!=NULL){
        push(result,copybdtoNode(merged));
        merged=merged->next;
    }
    return result;
}

void getInfWordStack(TStack stk, char *word) {
    if (isempty(stk)) {
        printf("Stack is empty.\n");
        return;
    }

    TStack tempStack = createstack(); 
    TList current = NULL;
    bool found = false;

    
    while (!isempty(stk)) {
        current = pop(stk);
        if (strcmp(current->word, word) == 0) {
            printf("Word: %s\n", current->word);
            printf("Synonym: %s\n", current->synonym);
            printf("Antonym: %s\n", current->antonym);
            printf("Number of Characters: %d %d %d\n",
                   current->numChars[0], current->numChars[1], current->numChars[2]);
            printf("Number of Vowels: %d %d %d\n",
                   current->numVowels[0], current->numVowels[1], current->numVowels[2]);
            found = true;
        }
        push(tempStack, current); 
    }

    
    while (!isempty(tempStack)) {
        push(stk, pop(tempStack));
    }

    if (found==false) {
        printf("Word '%s' not found in the stack.\n", word);
    }
}
TStack sortWordStack(TStack syn) {
    TStack sorte=createstack();     
    TStack temp=createstack();       
    while (!isempty(syn)) {
        TList curr = pop(syn);
        while (!isempty(sorte)&&strcasecmp(peek(sorte)->word, curr->word)>0) { //to find the right place
            push(temp, pop(sorte));
        }
        push(sorte, curr);
        while (!isempty(temp)) {
            push(sorte, pop(temp));
        }
    }

    return sorte;
}

TQueue stackToQueue(TStack stk) {
    TStack sorte = sortWordStack(stk);  

    TQueue queue1=malloc(sizeof(queue));
    queue1->front=NULL;
    queue1->rear=NULL;
    while (!isempty(sorte)) {
        TList node= pop(sorte);
        enqueuenode(queue1, node);
    }

    return queue1;
}

TListBD StacktoList(TStack stk) {
    TStack sorte=sortWordStack(stk);  
    TListBD head=NULL, temp;

    while (!isempty(sorte)) {
        TList current=pop(sorte);
        TListBD newNode =copyNodetobd(current);

        if (head==NULL) {
            head=newNode;
            temp=head;
        } else {
            temp->next=newNode;
            newNode->prev=temp;
            temp=newNode;
        }
    }

    return head;  
}

TStack addWordStack(TStack stk, char *word, char *syne, char *anton) {
    TList newNode=createNode(word,syne,anton);
    if (newNode==NULL) return stk;
    TStack tempStack = createstack();

    while (!isempty(stk)&&strcasecmp(peek(stk)->word,word)<0){
        push(tempStack, pop(stk));
    }

    push(stk, newNode);

    while (!isempty(tempStack)){
        push(stk, pop(tempStack));
    }

    return stk;
}

char *getSmallest(TStack stk) {
    if (stk==NULL||isempty(stk)) {
        return NULL;
    }

    TStack temp=createstack();
    char *minStr=NULL;

   
    while (!isempty(stk)){
        TList node=pop(stk);

        if (minStr==NULL ||strcmp(node->word,minStr)<0){
            free(minStr);
            minStr = malloc(strlen(node->word) + 1);
            if (!minStr) {
                fprintf(stderr, "Memory allocation faile \n");
                minStr= NULL;
            } else {
                strcpy(minStr,node->word);
            }
        }

        push(temp, node);
    }
    while (!isempty(temp)){
        push(stk, pop(temp));
    }
    free(temp);

    return minStr;
}

TStack syllableStack(TStack stk){
    if (stk==NULL|| isempty(stk)) 
    return stk;
    TStack sorte=createstack();
    TStack temp=createstack();
    while (!isempty(stk)) {
        TList curr =pop(stk);
        int   currCount =countSyllables(curr->word);
        while (!isempty(sorte) &&
               countSyllables(peek(sorte)->word)>currCount)
        {
            push(temp, pop(sorte));
        }
        push(sorte, curr);

        while (!isempty(temp)) {
            push(sorte, pop(temp));
        }
    }

    free(temp);
    return sorte;
}

TStack *pronunciationStack(TStack stk){
    if (isempty(stk)) return NULL;
    TStack temp = createstack();

    TStack *rsulte = malloc(3 * sizeof(TStack));
    rsulte[0]=createstack();
    rsulte[1]=createstack();
    rsulte[2]=createstack();

    while (!isempty(stk)) {
        TList node= pop(stk);
        if (containsDiphthong(node->word)){
            push(rsulte[2], node);
        }
        else if (isLongVowel(node->word)){
            push(rsulte[1], node);
        }
        else {
            push(rsulte[0], node);
        }
        push(temp,node);
    }

    while (!isempty(temp)) {
        push(stk, pop(temp));
    }
    free(temp);

    return rsulte;
}

typedef struct charNode{
    char data;
    struct charNode *next;
} charNode;


typedef struct{
    charNode *top;
} CharStack;
// Initialize stack
void initStack(CharStack *stack){
    stack->top = NULL;
}

// Push a character onto the stack
void pushc(CharStack *stack, char c){
    charNode *newNode = (charNode *)malloc(sizeof(charNode));
    newNode->data = c;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop a character from the stack
char popc(CharStack *stack){
    if (stack->top == NULL) return '\0';
    charNode *temp = stack->top;
    char c=temp->data;
    stack->top = temp->next;
    free(temp);
    return c;
}

// Check if stack is empty
bool isEmpty(CharStack *stack){
    return stack->top == NULL;
}
bool isPalindromeStack(char *word){
    if (word == NULL || *word == '\0') return true;
    CharStack stk;
    initStack(&stk);
    int length=strlen(word);
    for (int i=0;i<length;i++) {
        push(&stk, word[i]);
    }
    for (int i=0;i<length;i++) {
        char topChar=popc(&stk);
        if (word[i]!=topChar) {
            return false;
        }
    }

    return true;
}
void insertAtBottom(TStack stk,TList node){
    if (isempty(stk)) {
        push(stk,node);
        return;
    }
    TList temp=pop(stk);
    insertAtBottom(stk,node);
    push(stk,temp);
    
}
TStack StackRev(TStack stk){
    if (isempty(stk)) return stk;
    TList temp=pop(stk);
    StackRev(stk); 
    insertAtBottom(stk,temp);
    return stk;
}
bool deleteWordStack(TStack stk,char *word){
    if (isempty(stk)) return stk;

    TStack tempStack=createstack();
    bool found=false;
    while (!isempty(stk)){
        TList topNode=peek(stk);
        if (strcasecmp(topNode->word, word)==0){
            pop(stk); // Skip 
            found=true;
            break;
        }
        push(tempStack,pop(stk));
    }

    while (!isempty(stk)) {
        push(tempStack,pop(stk));
    }
    while (!isempty(tempStack)) {
        push(stk,pop(tempStack));
    }
    return found;
}
bool updateWordStack(TStack stk,char *word,char *syne,char *anton){
    if (isempty(stk)) return stk;

    TStack tempStack=createstack();
    bool updated=false;

    while (!isempty(stk)){
        TList node = pop(stk);

        if (strcasecmp(node->word,word)==0){
            if(syne != NULL){
                strcpy(node->synonym,syne);
                node->numChars[1]=countChars(syne);
                node->numVowels[1]=countVowels(syne);
            }
            if(anton != NULL){
                strcpy(node->antonym,anton);
                node->numChars[2]=countChars(anton);
                node->numVowels[2]=countVowels(anton);
            }
            updated = true;
        }

        push(tempStack, node);
    }

   
    while (!isempty(tempStack)){
        push(stk,pop(tempStack));
    }
    return updated;
}