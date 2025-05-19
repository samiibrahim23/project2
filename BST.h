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

typedef struct node {
    char word[50];
    char synonym[50];
    char antonym[50];
    int numChars[3];
    int numVowels[3];
    struct node* next;
} node;
 typedef node *TList ;



int countChars(const char *word) {
    return strlen(word);
}

int countVowels(const char *word) {
    int count = 0,i;
    for ( i = 0; word[i]; i++) {
        char c = word[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'|| c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            count++;
        }
    }
    return count;
}




TList createNode(char *word,char *synonym,char*antonym){
    TList newnode=malloc(sizeof(node));
    strcpy(newnode->word,word);
    newnode->numChars[0]=countChars(word);
    newnode->numVowels[0]=countVowels(word);
    newnode->synonym[0]='\0';
    newnode->antonym[0]='\0';
    if(synonym!=NULL){
    strcpy(newnode->synonym,synonym);
    newnode->numChars[1]=countChars(synonym);
    newnode->numVowels[1]=countVowels(synonym);   
    } 
     if(antonym!=NULL){
    strcpy(newnode->antonym,antonym);
    newnode->numChars[2]=countChars(antonym);
    newnode->numVowels[2]=countVowels(antonym);
    
    }

     
    



newnode->next=NULL;

return newnode;

}






TList getSynWords(FILE *f)
{
TList temp=NULL,head=NULL;
char buffer[200];

while(fgets(buffer,200,f)!=NULL){

 buffer[strcspn(buffer, "\n")] = '\0' ;   //change \n to \0    

   if(strchr(buffer,'#') !=NULL) 
   continue;

   char *equal=strchr(buffer,'=');
   if(equal==NULL)
   continue;
   *equal='\0';
   char *word=buffer;
   char* synonym=equal+1;
   if(head==NULL){
   head=createNode(word,synonym,NULL);
   temp=head;}
   else{
    TList temp2=createNode(word,synonym,NULL);
    temp->next=temp2;
    temp=temp->next;

   }

}
return head;


}


 TList getAntoWords(FILE  *f){
TList temp=NULL,head=NULL;
char buffer[200];

while(fgets(buffer,200,f)!=NULL){

 buffer[strcspn(buffer, "\n")] = '\0' ;   //change \n to \0    

   if(strchr(buffer,'=') !=NULL) 
   continue;

   char *equal=strchr(buffer,'#');
   if(equal==NULL)
   continue;
   *equal='\0';
   char *word=buffer;
   char* synonym=equal+1;
   if(head==NULL){
   head=createNode(word,NULL,synonym);
   temp=head;}
   else{
    TList temp2=createNode(word,NULL,synonym);
    temp->next=temp2;
    temp=temp->next;

   }

}
return head;
 }
 
void getInfWord(TList syn, TList ant, char *word){
	  bool find_syn=false,find_anto= false;
	  printf(" the nember of char in this word is : %d\n",countChars(word));
	  printf(" the nember of Vowels in this word is : %d\n",countVowels(word));
	  while(find_syn!=true && syn!=NULL){
	  	if(strcmp(word,syn->word)==0){
	  		printf(" the synonyme of this word is : %s\n",syn->synonym);
	  		find_syn=true;}
			  syn=syn->next;}
			  if(syn==NULL)
			  printf("the synonyme does no exist \n");
	  	while(find_anto!= true && ant!=NULL){
	  		 if(0!= strcmp(word,ant->word)){
	  		printf(" the antonym of this word is : %s\n",ant->word);
	  		find_anto=true;}
			  ant=ant->next;}
			  if(!find_anto)
			  printf("the antonym does no exist \n");}
