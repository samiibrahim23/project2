#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <unistd.h>
#include"listfile.h"


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
 
 void getInfWord(TList syn, TList ant, char *word) {
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
			  printf("the antonym does no exist \n");
              }

void getInfWord2(TList syn, TList ant, char *inf){
char *word=NULL;
bool find =false,synonym=false,antonym=false;
   
    while(syn!=NULL&&ant!=NULL)
    {
        if(strcasecmp(syn->synonym,inf)==0){
            printf(" %s is  synonym of the word : %s \n",syn->synonym,syn->word);
            find=true;
            synonym=true;
            break;
        }
        if(strcasecmp(ant->antonym,inf)==0){
            printf(" %s is antonym of the word : %s \n",ant->antonym,ant->word);
            find=true;
            antonym=true;
            break;
        }
        syn=syn->next;
        ant=ant->next;

    }
    if(find!=true &&syn==NULL){
        while(ant!=NULL){
        if(strcasecmp(ant->antonym,inf)==0){
            printf("  %s is antonym of  the word : %s \n",ant->antonym,ant->word);
            find=true;
            antonym=true;
            break;
        }
         ant=ant->next;         
        }
    }
   if(find!=true&&ant==NULL){
    while(syn!=NULL){
        if(strcasecmp(syn->synonym,inf)==0){
            printf(" %s is synonym of  the word : %s \n",syn->synonym,syn->word);
            find=true;
         synonym=true;
            break;
        }
        syn=syn->next;        
    }
   }
   if(find==false){
    printf("no synonym or antonym were found \n");

   }
   else{
    if(synonym==true){
        printf("Characters: %d\n",countChars(syn->word));
        printf("Vowels: %d \n",countVowels(syn->word));

    }
    else{
        printf("Characters: %d\n",countChars(ant->word));
        printf("Vowels: %d \n",countVowels(ant->word));
    }
   }
}

bool issortedbynumCHRAS(TList head  )  
{
    int temp;
    if(NULL==head)
    return true;
    temp=head->numChars[0];
    while(NULL!=head->next){
        head=head->next;
        if(temp>head->numChars[0])
        return false;
        temp=head->numChars[0];
    }
    return true;
}


TList merge2bychar(TList head1,TList head2){
    if(!issortedbynumCHRAS(head1) || !issortedbynumCHRAS(head2)){
        printf("there is mistake");
        exit(EXIT_FAILURE);
    }
    if(head1==NULL){
        return head2;
    }
    if(head2==NULL){
        return head1;
    }
    TList head3,temp;
    if(head1->numChars[0]<head2->numChars[0]){
        head3=head1;
        head1=head1->next;
    }else{
        head3=head2;
       head2= head2->next;
    }
    temp=head3;
    TList save=NULL;
    while(NULL!=head1 && NULL!=head2){
        if(head1->numChars[0]<head2->numChars[0]){
            save=head1;
            head1=head1->next;
            temp->next=save;
        }else{
            save=head2;
            head2=head2->next;
            temp->next=save;
        }
        temp=temp->next;

    }
    if(NULL==head1){
        temp->next=head2;
        return head3;
    }
    if(NULL==head2){
        temp->next=head1;
        return head3;
    }
    return head3;
}


int count(TList head){
    int c=0;
    while(NULL!=head){
    c++;
    head=head->next;
    }
    return c;
}
void split2(TList head,TList *head1){
    *head1=NULL;
    int index=count( head);
    if(0==index){
        return;
    }
    TList temp=head;
    for(int i=1;i<index/2;i++)
    temp=temp->next;
    *head1=temp->next;
    temp->next=NULL;


}
void sortWord2(TList *syn){
    if(issortedbynumCHRAS(*syn))
    return;
    TList half=NULL;
    
    split2(*syn,&half);
    
    
        
        sortWord2(syn);
        sortWord2(&half);
        
    
    *syn=merge2bychar(*syn,half);
        
}

// sort3

bool issortedbynumvowls(TList head  )  
{
    int temp;
    if(NULL==head)
    return true;
    temp=head->numVowels[0];
    while(NULL!=head->next){
        head=head->next;
        if(temp<head->numVowels[0])
        return false;
        temp=head->numVowels[0];
    }
    return true;
}


TList merge2byvowls(TList head1,TList head2){
    if(!issortedbynumvowls(head1) || !issortedbynumvowls(head2)){
        printf("there is mistake");
        exit(EXIT_FAILURE);
    }
    if(head1==NULL){
        return head2;
    }
    if(head2==NULL){
        return head1;
    }
    TList head3,temp;
    if(head1->numVowels[0]>head2->numVowels[0]){
        head3=head1;
        head1=head1->next;
    }else{
        head3=head2;
        head2=head2->next;
    }
    temp=head3;
    TList save=NULL;
    while(NULL!=head1 && NULL!=head2){
        if(head1->numVowels[0]>head2->numVowels[0]){
            save=head1;
            head1=head1->next;
            temp->next=save;
        }else{
            save=head2;
            head2=head2->next;
            temp->next=save;
        }
        temp=temp->next;

    }
    if(NULL==head1){
        temp->next=head2;
        return head3;
    }
    if(NULL==head2){
        temp->next=head1;
        return head3;
    }
    return head3;
}


void sortWord3(TList *syn){

    if(issortedbynumvowls(*syn))
    return;
    TList half=NULL;
    
    split2(*syn,&half);
    
    
        
        sortWord3(syn);
        sortWord3(&half);
        
    
    *syn=merge2byvowls(*syn,half);

}


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
 
 TList searchword(char *word,TList list){
while(list!=NULL){
    if(strcasecmp(word,list->word)==0)
    return list;
    list=list->next;
}
return NULL;
}
 
void addtolist(TList *head,char *word,char *synonym,char*antonym){
    if(*head==NULL){
        *head=createNode(word,synonym,antonym);
        return;
    }
    TList temp=*head;
    while(temp->next!=NULL)
    temp=temp->next;
    temp->next=createNode(word,synonym,antonym);

}

 
 void deleteWord(FILE *file,char *file_name,TList *syn,TList *ant ,char *word){
	char buffer[200];
	FILE *temp=fopen("temp.txt","w");
	  while(fgets(buffer,200,file)!=NULL){
	  	if(strstr(buffer,word)==NULL)
	  	fputs(buffer,temp);}
	  	fclose(file);
	  	fclose(temp);
		remove(file_name);
	  	rename("temp.txt",file_name);
	bool check_s=false,check_A=false;
	TList temp1=*ant,temp0=*syn,prv1=*ant,prv=*syn;
	while(check_s!=true ){
	  		if(strcmp(temp0->word,word)==0){
	  		check_s=true;
			  prv->next=temp0->next;
			  free(temp0);}
	  		else{
	  		prv=temp0;
	  		temp0=temp0->next;}}
	  		while(check_A!=true){
			  if(0==strcmp(word,temp0->word)){
	  		check_A=true;
			  prv1->next=temp1->next;
			  free(temp1);}
	  		else{
	  		prv1=temp1;
	  		temp1=temp1->next;}}}

void updateWord(FILE *f , TList *syn, TList *ant, char *word, char *syne, char *anton)
{
    FILE *temp=fopen("__tempfile","w+");
    rewind(f);
    if(syne!=NULL && anton!=NULL){
        bool inanto=false,insyne=false;
        TList tempanto,tempsyn;
        tempanto=searchword(word,*ant);
        tempsyn=searchword(word,*syn);
        if(tempanto!=NULL)
        inanto=true;
        if(tempsyn!=NULL)
        insyne=true;
        char buffer[256];
        while(fgets(buffer,256,f)!=NULL){
            if(strncasecmp(buffer,word,strlen(word))==0){
                if(strstr(buffer,"=")!=NULL){
                fprintf(temp, "%s=%s\n", word, syne);
                if (tempsyn != NULL)
                strcpy(tempsyn->synonym,syne);
                tempsyn->numChars[1]=countChars(syne);
                tempsyn->numVowels[1]=countVowels(syne);
                }
                else{
                fprintf(temp, "%s#%s\n", word, anton);
                if (tempanto != NULL)
                strcpy(tempanto->antonym,anton);
                tempanto->numChars[2]=countChars(anton);
                tempanto->numVowels[2]=countVowels(anton);
                }
            }
            else{
                fputs(buffer,temp);
            }

        }
       
        if(inanto==false){
            fprintf(temp, "%s#%s\n", word, anton);
            addtolist(ant,word,NULL,anton);
        }
        if(insyne==false){
            fprintf(temp, "%s=%s\n", word, syne);
            addtolist(syn,word,syne,NULL);
        }
    }
    if(syne!=NULL&&anton==NULL){
                bool insyne=false;
        TList tempsyn;
       
        tempsyn=searchword(word,*syn);
       
        if(tempsyn!=NULL)
        insyne=true;
        char buffer[256];
        while(fgets(buffer,256,f)!=NULL){
            if(strncasecmp(buffer,word,strlen(word))==0){
                if(strstr(buffer,"=")!=NULL){
                fprintf(temp, "%s=%s\n", word, syne);
                if (tempsyn != NULL)
                strcpy(tempsyn->synonym,syne);
                tempsyn->numChars[1]=countChars(syne);
                tempsyn->numVowels[1]=countVowels(syne);
                }
            }
            else{
                fputs(buffer,temp);
            }
        }
        
        if(insyne==false){
            fprintf(temp, "%s=%s\n", word, syne);
            addtolist(syn,word,syne,NULL);
        }

    }
    if(syne==NULL&&anton!=NULL)
    {
        bool inanto=false;
        TList tempanto;
        tempanto=searchword(word,*ant);
        if(tempanto!=NULL)
        inanto=true;
        char buffer[256];
        while(fgets(buffer,256,f)!=NULL){
            if(strncasecmp(buffer,word,strlen(word))==0){
                if(strstr(buffer,"#")!=NULL){
                fprintf(temp, "%s#%s\n", word, anton);
                if (tempanto != NULL)
                strcpy(tempanto->antonym,anton);
                tempanto->numChars[2]=countChars(anton);
                tempanto->numVowels[2]=countVowels(anton);
                }
            }
            else{
                fputs(buffer,temp);
            }

        }
        
        if(inanto==false){
            fprintf(temp, "%s#%s\n", word, anton);
            addtolist(ant,word,NULL,anton);
        }
    }
    fclose(temp);
    temp=fopen("__tempfile","r");
    rewind(f);
    rewind(temp);
    
    #ifdef _WIN32
    _chsize(_fileno(f), 0);       // Windows: clear file
    #else
    ftruncate(fileno(f), 0);      // Linux/Unix: clear file
    #endif
    char buffer[256];
    while(fgets(buffer,256,temp)!=NULL){
        fputs(buffer,f);
    }
    fflush(f);
    fclose(temp);
    remove("__tempfile");
    

}

TList countWord(TList syn, char *prt){
   TList temp,head=NULL,temp1;	
	while(syn!=NULL){
		if(strstr(syn->word,prt)!=NULL){
			if(head==NULL){
			head=createNode(syn->word,temp->synonym,NULL);
		    temp1=head;}
			else{
			temp=createNode(syn->word,syn->synonym,NULL);
			temp1->next=temp;
			temp1=temp;}}
		    syn=syn->next;}
			return(head);}
void reverseString(char* str){
 int i,save;
for(i=0;i<(strlen(str)/2);i++){
 save=str[i];
 str[i]=str[strlen(str)-1-i];
 str[strlen(str)-1-i]=save;}}
TList palindromWord(TList syn){
	char *temp;
	TList head=NULL,p,list=NULL;
	while(syn!=NULL){
	strcpy(temp,syn->word);
	reverseString(temp);
	if(strcmp(temp,syn->word)==0){
	    if(list==NULL){
	    list=createNode(syn->word,syn->synonym,syn->antonym);
	    head=list;
		p=list;}
	    else{
	    	list=createNode(syn->word,syn->synonym,syn->antonym);
	    	p->next=list;
	    	p=list;}}
		    syn=syn->next;}
		    sortWord(head);
	return(head);
}
void addWord(FILE *f,TList *syn, TList *ant, char *word, char *syne, char *anton){
	TList temp,temp1;
	temp=createNode(word,syne,NULL);
	temp->next=*syn;
	temp1=createNode(temp->word,NULL,anton);
	temp1->next=*ant;
	*syn=temp;
	*ant=temp1;
	fputs(word,f);
 
}


float matchRate(char *word1, char *word2) {  // to calculate rate 
    int match = 0;
    int lenword1 = strlen(word1), lenword2 = strlen(word2);
    int minLen ,maxLen;
    if(lenword1>lenword2){
        minLen=lenword2;maxLen=lenword1;
    }
    else{
        minLen=lenword1;maxLen=lenword2;
    }

    for (int i = 0; i < minLen; i++) {
        if (word1[i] == word2[i]) match++;  
    }

    return (float)match / maxLen;  
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

TListBD copyNodetobd(TList src) {
    TListBD newNode = malloc(sizeof(nodebd));
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
    newNode->prev=NULL;
    return newNode;
}

TList copybdtoNode(TListBD src) {
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


TList similarWord(TList syn, char* word,  float rate){
    TList result,temp,newnode;
    bool notempty=false;
    while(syn!=NULL){
        if(matchRate(syn->word,word)>=rate){
            newnode=copyNode(syn);
            if(notempty==false){
                result=newnode;
                temp=result;
                notempty=true;
            }
            else{
                temp->next=newnode;
                temp=temp->next;
            }
        }
        syn=syn->next;

    }
    return result;

}

TListBD copyToBDList(TList head) {
    if (head == NULL) return NULL;
    TListBD dhead;
    dhead=copyNodetobd(head);

    TListBD dcurrent = dhead;
    TList scurrent = head->next;

    while (scurrent != NULL) {
        TListBD newNode;
        newNode=copyNode(scurrent);
        newNode->prev = dcurrent;
        dcurrent->next = newNode;

        dcurrent = newNode;
        scurrent = scurrent->next;
    }
    dcurrent->next = NULL;
    return dhead;
}


TListBD merge(TList syn, TList ant){
    TListBD returnd;
    
     if(syn==NULL&&ant==NULL)
     return NULL;
     if(syn!=NULL&&ant==NULL){
     returnd=copyToBDList(syn);
     return returnd;}
     if(syn==NULL&&ant!=NULL){
    returnd=copyToBDList(ant);
     return returnd;
     }
     if(syn!=NULL&&ant!=NULL){
        returnd=copyToBDList(syn);
        TListBD temp=returnd;
        
        while(temp->next!=NULL)
        temp=temp->next;

        TListBD antbd=copyToBDList(ant);
        temp->next=antbd;
        antbd->prev=temp;
     }
    return returnd;
}

 TList merge2(TList syn, TList ant){
    TList returnd,temp;
    if(syn==NULL&&ant==NULL)
     return NULL;
    if(syn!=NULL&&ant==NULL){
     returnd=copyNode(syn);
     syn=syn->next;
     temp=returnd;
     while(syn!=NULL){
        temp->next=copyNode(syn);
        syn=syn->next;
        temp=temp->next;
     }
     temp->next=returnd;
     return returnd;}
     if(syn==NULL&&ant!=NULL){
     returnd=copyNode(ant);
     ant=ant->next;
     temp=returnd;
     while(ant!=NULL){
        temp->next=copyNode(ant);
        ant=ant->next;
        temp=temp->next;
     }
     temp->next=returnd;
     return returnd;
     }
     if(syn!=NULL&&ant!=NULL){
     returnd=copyNode(syn);
     syn=syn->next;
     temp=returnd;
     while(syn!=NULL){
        temp->next=copyNode(syn);
        syn=syn->next;
        temp=temp->next;
     }
        while(ant!=NULL){
        temp->next=copyNode(ant);
        ant=ant->next;
        temp=temp->next;
     }  
     temp->next=returnd;
     }
     return returnd;


}


void enqueuenode(TQueue  q,TList syn){
    TList newnode=copyNode(syn);
    if (q->front==NULL){
      q->front=newnode;
      q->rear=newnode;
      return;
    }
    q->rear->next=newnode;
    q->rear=q->rear->next;
}
int isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || 
            c == 'o' || c == 'u'  || c=='A'|| c == 'E' || c == 'I' || 
            c == 'O' || c == 'U' );
}

int countSyllables(const char *word) { 
    int count = 1;
    if (word == NULL || *word == '\0') return 0;                  
    for ( char *p = word; *p != '\0'; p++) {
        if (*p == ' ')
            count++;
    }
    return count;
}

TQueue syllable(TList syn){
    if(syn==NULL)
    return NULL;
    TQueue results=malloc(sizeof(queue));
    results->front=NULL;
    results->rear=NULL;
    struct syllable {
        TList list;
        int numofsyll;
    };
    int size=count(syn);
    struct syllable *arrofsyll=malloc(sizeof(struct syllable)*size);
    int i=0;
    while(syn!=NULL){
        arrofsyll[i].list=copyNode(syn);
        arrofsyll[i].numofsyll=countSyllables(syn->word);
        i++;
        syn=syn->next;

    }
    int swap=1;
    while(swap!=0){
        swap=0;
        for(i=0;i<size-1;i++){
            if((arrofsyll+i)->numofsyll>(arrofsyll+i+1)->numofsyll){
                swap=1;
                struct syllable temp = arrofsyll[i];
                arrofsyll[i] = arrofsyll[i + 1];
                arrofsyll[i + 1] = temp;

            }

        }

    }
    
  
    for(i=0;i<size;i++){
        enqueuenode(results,arrofsyll[i].list);

    }
    free(arrofsyll);
    return results;

}

int containsDiphthong(const char *word) {
    const char *diphthongs[] = {"oi", "ou", "ow", "au", "ea", "ai", "oy", "ie", "ei"};
    for (int i = 0; i < sizeof(diphthongs)/sizeof(diphthongs[0]); i++) {
        if (strstr(word, diphthongs[i]) != NULL)
            return 1;
    }
    return 0;
}

int isLongVowel(const char *word) {
    int len = strlen(word);
    if (len > 2 && word[len - 1] == 'e' && isVowel(word[len - 2]))
        return 1;
    
    for (int i = 0; i < len - 1; i++) {
        if (isVowel(word[i]) && isVowel(word[i + 1]))
            return 1;
    }
    return 0;
}

TQueue *prounounciation(TList syn) // return array of 3queues /first short/2long/3dipthong
{
  TQueue *resule=malloc(sizeof(TQueue)*3);
   for (int i = 0; i < 3; i++) {
        resule[i]=malloc(sizeof(queue));
        resule[i]->front=NULL;
        resule[i]->rear =NULL;
    }
   while (syn != NULL) {
        TList node = copyNode(syn);

        if (containsDiphthong(syn->word)==1) {
            enqueuenode(resule[2], node);
        } else if (isLongVowel(syn->word)==1) {
            enqueuenode(resule[1], node);
        } else {
            enqueuenode(resule[0], node);
        }

        syn = syn->next;
    }
    return resule;

}

 TQueue toQueue(TListBD merged){
    TQueue result =malloc(sizeof(queue));
    result->front=NULL;
    result->rear=NULL;
    while(merged){
        TList newnode=copybdtoNode(merged);
        enqueuenode(result,newnode);
        merged=merged->next;
    }
    return result;

 }