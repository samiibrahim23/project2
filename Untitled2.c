#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>
#define SIZE 100
typedef struct node {
    char word[50];
    char synonym[50];
    char antonym[50];
    int numChars[3];
    int numVowels[3];
    struct node* next;
} node;
 typedef node *TList ;
typedef struct stack{
    TList top;
}stack;
typedef stack* TStack;
TStack createstack(){
    TStack stack1=malloc(sizeof(stack));
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
	TList popednode;
    if(!isempty(stk)){
        popednode=copyNode(stk->top);
        stk->top=stk->top->next;
        return popednode;
    }
    return NULL;}
TList peek(TStack stk) {
    if (!isempty(stk)) {
        return stk->top;  
    }
    return NULL;
}
TList copyNode(TList src) {
    TList newNode = malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newNode->word, src->word);
    strcpy(newNode->synonym, src->synonym);
    strcpy(newNode->antonym, src->antonym);
    for (int i = 0; i < 3; i++) {
        newNode->numChars[i] = src->numChars[i];
        newNode->numVowels[i] = src->numVowels[i];
    }
    newNode->next = NULL;
    return newNode;
}
 typedef node *TList ;
typedef struct TTree{
	char word[50];
    char synonym[50];
    char antonym[50];
    int numChars[3];
    int numVowels[3];
 struct TTree* left;
struct TTree* right;
}TTree;
TList sortWord(TList syn){
	TList first,secound;
	char temp[100];
	bool isSorted=false;
	while(!isSorted){
		first=syn;
		secound=first->next;
		isSorted=true;
		while(secound!=NULL){
			if(strcasecmp(first->word,secound->word)>0){
				strcpy(temp,first->word);
				strcpy(first->word,secound->word);
				strcpy(secound->word,temp);
				isSorted=false;}
				else{
					first=secound;
					secound=secound->next;}}}
					return(syn);}	  
TTree *getInfWordTree(TTree *tr, char *word){
	TTree *found;
	if(tr==NULL)
	return(NULL);
	if(strcmp(tr->word,word)==0)
	return(tr);
	found=getInfWordTree(tr->left, word);
	 if (found != NULL)
        return found;

    return getInfWordTree(tr->right, word);

}
TTree* toTree(TStack *stk) {
    TTree *root = NULL;
    char *word;
    while (stk != NULL) {
        word = pop(stk); 
        root = insert(root, word);
        free(word);}
    return root;}

TTree *UpdateWordBST(TTree *tr, char *word, char *syne, char *anton){
	TTree *found;
	if(tr==NULL)
	return(NULL);
	if(strcmp(tr->word,word)==0){
		strcpy(tr->synonym,syne);
		strcpy(tr->antonym,anton);
	return(tr);}
	found=UpdateWordBST(tr->left,word,syne,anton);
	 if (found != NULL)
        return found;

    return UpdateWordBST(tr->right, word,syne,anton);
}
TTree* findMin(TTree* node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}
TTree* deleteWordBST(TTree* tr, char* word) {
    if (tr == NULL)
        return NULL;
    int cmp = strcasecmp(word, tr->word);
    if (cmp < 0) {
        tr->left = deleteWordBST(tr->left, word);
    } else if (cmp > 0) {
        tr->right = deleteWordBST(tr->right, word);
    } else {
        if (tr->left == NULL && tr->right == NULL) {
            free(tr);
            return NULL;
        }
        if (tr->left == NULL) {
            TTree* temp = tr->right;
            free(tr);
            return temp;
        } else if (tr->right == NULL) {
            TTree* temp = tr->left;
            free(tr);
            return temp;
        }
        TTree* minNode = findMin(tr->right);
        strcpy(tr->word, minNode->word);
        tr->right = deleteWordBST(tr->right, minNode->word); 
    }

    return tr;
}
TTree *AddWordBSTT(TTree *tr, char *word, char *syne, char *anton){
    if (tr == NULL) {
        TTree* node = (TTree*)malloc(sizeof(TTree));
        strcpy(node->word, word);
        strcpy(node->synonym,syne);
        strcpy(node->antonym,anton);
        node->left = node->right = NULL;
        return node;
    }
    if (strcasecmp(word, tr->word) < 0)
        tr->left =AddWordBSTT(tr->left, word,syne,anton);
    else
        tr->right =AddWordBSTT(tr->right, word,syne,anton);
    return tr;}
TTree* fillTree(FILE *f) {
 TTree *root = NULL;
    char word[50];
    while (fscanf(f, "%s", word) != EOF) {
        root = insert(root, word);}
    return root;}

TTree *TraversalBSTinOrder(TTree *tr){
	if(tr==NULL)
	return(NULL);
	TraversalBSTinOrder(tr->left);
	printf("%s",tr->word);
	TraversalBSTinOrder(tr->right);}
TTree *TraversalBSTpreOrder(TTree *tr){
	printf("%s",tr->word);
	TraversalBSTinOrder(tr->left);
	TraversalBSTinOrder(tr->right);
}
TTree *TraversalBSTpostOrder(TTree *tr){
	TraversalBSTpostOrder(tr->left);
	TraversalBSTpostOrder(tr->right);
	printf("%s",tr->word);}
int Height(TTree *tr) {
    if (tr == NULL) {
        return 0;
    } else {
        int leftHeight = Height(tr->left);
        int rightHeight = Height(tr->right);
        
        if (leftHeight > rightHeight) {
            return 1 + leftHeight;
        } else {
            return 1 + rightHeight;
        }}}
int size(TTree *tr){
	if (tr==NULL)
	return(0);
	return(1+size(tr->left)+size(tr->right));
}
void HighSizeBST(TTree *tr){
	printf("the size of this tree is: %d",size(tr));
	printf("the hight of this tree is: %d",Height(tr));
}
TTree* BSTMirror(TTree* tr) {
    if (tr == NULL) return NULL;
    // here i a Allocate a new node
    TTree* mirrored = (TTree*)malloc(sizeof(TTree));
    if (mirrored == NULL)
	return NULL; // 
    strcpy(mirrored->word,tr->word);
    mirrored->left = BSTMirror(tr->right);
    mirrored->right = BSTMirror(tr->left);

    return mirrored;
}
TTree* LowestCommonAncestor(TTree *tr, char *word1, char *word2) {
    if (tr == NULL) return NULL;
    if (strcmp(word1, tr->word) < 0 && strcmp(word2, tr->word) < 0)
        return LowestCommonAncestor(tr->left, word1, word2);

    if (strcmp(word1, tr->word) > 0 && strcmp(word2, tr->word) > 0)
        return LowestCommonAncestor(tr->right, word1, word2);
    return tr;
}// here i calculate the length of word and compare it with renge 
int CountNodesRanges(TTree *tr, int l, int h) {
	int count,val;
    if (tr == NULL)
	return 0;
    val = strlen(tr->word);
    count = 0;
    if (val >= l && val <= h)
        count = 1;
    return count + CountNodesRanges(tr->left, l, h) + CountNodesRanges(tr->right, l, h);
}
TTree* minValueNode(TTree* node) {
    TTree* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

TTree* inOrderSuccesor(TTree *root, char *word) {
    TTree* successor = NULL;
    while (root != NULL) {
        if (strcmp(word, root->word) < 0) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;}}
    return successor;
}

bool isBalencedBST(TTree *tr){
	if(tr==NULL)
	return(true);
	if(abs(Height(tr->left)-Height(tr->right))>1)
	return(false);
return(isBalencedBST(tr->left)&&isBalencedBST(tr->right));}

void inOrderToList(TTree* root, TList* listTail) {
    if (root == NULL) return;
    inOrderToList(root->left, listTail);
    TList newNode = (TList)malloc(sizeof(node));
    strcpy(newNode->word, root->word);
    newNode->next = NULL;
    (*listTail)->next = newNode;
    *listTail = newNode;
    inOrderToList(root->right, listTail);
}

TList treeToList(TTree* root) {
    TList list = (TList)malloc(sizeof(node));
    list->next = NULL;
    TList tail = list;
    inOrderToList(root, &tail);
    TList head = list->next;
    free(list);
    return head;
}
TList mergeLists(TList l1, TList l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    TList head = l1;
    while (l1->next != NULL)
        l1 = l1->next;
    l1->next = l2;
    return head;
}


TTree* BSTMerge(TTree* tr1, TTree* tr2) {
	TList list1,list2,merged,sorted;
	TTree *newTree;
    list1 = treeToList(tr1);
    list2 = treeToList(tr2);
    merged = mergeLists(list1, list2);
    sorted = sortWord(merged);
     newTree = NULL;
    while (sorted != NULL) {
        newTree = AddWordBSTT(newTree, sorted->word,NULL,NULL);
        sorted = sorted->next;
    }

    return newTree;
}


