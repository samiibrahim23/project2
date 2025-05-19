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


