#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countWordOccurence(FILE *f, char *word) {
    char temp[50];// ????? ??????: ??? ????? ?????? ?????
    if (fscanf(f, "%s", temp) == EOF)
        return 0;
    if (strcmp(temp, word) == 0)
        return 1 + countWordOccurence(f, word); 
		 else
        return countWordOccurence(f, word);}
FILE* removeWH(FILE *f, FILE *temp, char *word) {
    char tempWord[50];
    if (fscanf(f, "%s", tempWord) == EOF)
        return temp;
    if (strcmp(tempWord, word) != 0) 
        fprintf(temp, "%s ", tempWord); 
    return removeWH(f, temp, word);}
FILE* removeWordOccurence(FILE *f, char *word) {
    FILE *temp = tmpfile();
    return removeWH(f, temp, word);
}
FILE* replaceWordOccurenceHelper(FILE *f, FILE *temp, char *word, char *rep) {
    char tempWord[50];

    if (fscanf(f, "%s", tempWord) == EOF)
        return temp;

    if (strcmp(tempWord, word) == 0)
        fprintf(temp, "%s ", rep);
    else
        fprintf(temp, "%s ", tempWord);
    return replaceWordOccurenceHelper(f, temp, word, rep);}
FILE* replaceWordOccurence(FILE *f, char *word, char *rep) {
    FILE *temp = tmpfile();
    return replaceWordOccurenceHelper(f, temp, word, rep);
}
void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *word, int l, int r) {
	int i;
    if (l == r)
        printf("%s\n", word); 
    else {
        for (i = l; i <= r; i++) {
            swap(&word[l], &word[i]); 
	        permute(word, l + 1, r);   
            swap(&word[l], &word[i]);
        }
    }
}

void wordPermutation(char *word) {
    int len = strlen(word);
    permute(word, 0, len - 1);
}

void findsubseq(char *word, char *subseq, int i, int j){
    if (word[i] == '\0') {
        subseq[j] = '\0';
        printf("%s\n", subseq);
        return;
    }
    subseq[j] = word[i];
    findSubseq(word, subseq, i + 1, j + 1);
    findSubseq(word, subseq, i + 1, j);
}

void subseqWord(char *word){
    int leng=strlen(word);
    char subseq=malloc(sizeof(char)*(leng+1));
    findsubseq(word, subseq, 0, 0);
}
int longestSubseq(char *word1,char *word2,int leng1,int leng2){
    if (leng1 == 0 || leng2 == 0)
        return 0;
    if (word1[leng1 - 1] == word2[leng2 - 1])
        return 1 + longestSubseq(word1, word2, leng1 - 1, leng1 - 1);
    else
        return(longestSubseq(word1, word2, leng1 - 1, leng2)>   //return largest between them
                longestSubseq(word1, word2, leng1, leng2 - 1))
                ? longestSubseq(word1, word2, leng1 - 1, leng2)
                : longestSubseq(word1, word2, leng1, leng2 - 1);
}

bool isPalind(char *word,int start,int end){
    if (start >= end)  
        return true;
    if (word[start] != word[end])  
        return false;
    return isPalind(word,start+1,end-1);
}

bool isPalindromWord(char *word){
    int lengt = strlen(word);
    return isPalindromeHelper(word,0,lengt-1);
}


