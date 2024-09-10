#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int wordNum = 1;
char *findWord(char *line, int wordNum) {
    char *word = NULL;
    int counter = 0;
    char *start = line;
    char *end = line;

    while (counter < wordNum) {
     
        while (*start == ' ') {
            start++;
        }
        
        end = start;
        while (*end != ' ' && *end != '\0') {
            end++;
        }

        if (*start == '\0') {
            return (counter == 0) ? NULL : word;
        }

        word = start;
        counter++;

        if (*end == '\0') {
            return word;
        }

        start = end;
    }

    return word;
}

int compare(const void *firstLine, const void *secondLine){
  char *lineOne = *(char**)firstLine;
  char *lineTwo = *(char**)secondLine;
  char *wordOne = findWord(lineOne, wordNum);
  char *wordTwo = findWord(lineTwo, wordNum);

  if(wordOne == NULL && wordTwo == NULL) {
    return 0;
  } else if (wordOne==NULL){
    return 1;
  } else if (wordTwo == NULL){
    return -1;
  }
 int result = strcmp(wordOne, wordTwo);

  if(result == 0) {
    return strcmp(lineOne, lineTwo);
  }

  return result;
}

int main(int argc, char** argv)
{
    char *fileName;
    if(argc > 3 || argc < 2){
        fprintf(stderr, "Error: Bad command line parameters\n");
        exit(1);
    }
    if(argc == 3){
        if(argv[1][0]=='-'&&isdigit(argv[1][1])){
            wordNum = argv[1][1] - '0';
            fileName = argv[2];
        } else {
            fprintf(stderr, "Error: Bad command line parameters\n");
            exit(1);
        }
    }
    if(argc == 2){
      if(argv[1][0]=='-'){
        fprintf(stderr, "Error: Bad command line parameters\n");
        exit(1);
      }
      fileName = argv[1];
      wordNum = 1;
    }

    FILE* file;
    file = fopen(fileName, "r");
    if(file==NULL){
      fprintf(stderr, "Error: cannot open file %s\n", fileName);
      exit(1);
    }
    
    
    int totalNumOfLines = 0;
    char buff[150];
    char testbuff[1000];
    
    while(fgets(testbuff, sizeof(testbuff), file)!=NULL){
      totalNumOfLines++;
    }
    
    rewind(file);

    char *lines[totalNumOfLines];
    int numOfLines = 0;
    while(fgets(buff, sizeof(buff), file)!=NULL){
      if(strlen(buff)>128){
        fprintf(stderr, "Line too long\n");
        exit(1);
      }
      lines[numOfLines] = strdup(buff);
      numOfLines++;
    }

    fclose(file);

    qsort(lines, numOfLines, sizeof(char*), compare);

    for(int x = 0; x < numOfLines; x++){
      printf("%s", lines[x]);
      free(lines[x]);
    }

    return 0;
}
