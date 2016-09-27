#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define size 40
void outData();
void outputFolder(struct dirent *pointer,DIR *dir);
void outputSpeciffolder(struct dirent *pointer,DIR *dir,char *directory);
void logFile(struct dirent *pointer,char *dataTime);
void addHelpFile();
char *getCurrentTimeFormate(char *format);
void outputFileToScrean(char * file);
int main(int argc, char **argv) {
    printf("%s", argv[0]);

    outData();
    return 0;
}


void outData(){
    addHelpFile();
    char *dataTime=getCurrentTimeFormate("%Y-%m-%d %X:");
    struct dirent *pointer;
    logFile(pointer,dataTime);
}

void outputFolder(struct dirent *pointer,DIR *dir){
    printf("The files in the current directory\n");
    dir = opendir("./");
    if (!dir) {
        perror("diropen");
        exit(1);
    }
    while ( (pointer = readdir(dir))) {
        printf(" %s \n",
               pointer->d_name);
    }
    closedir(dir);
}

void outputSpeciffolder(struct dirent *pointer,DIR *dir,char *directory){
    printf(directory,"\n");
    dir = opendir(directory);
    if (!dir) {
        perror("diropen");
        //exit(1);
    }
    while ( (pointer = readdir(dir))) {
        printf(" %s \n",
               pointer->d_name);
    }
    closedir(dir);
}

void logFile(struct dirent *pointer,char *dataTime){
    FILE* myfile;
    myfile = fopen("logs.txt","w");
    fclose(myfile);
    myfile = fopen("logs.txt","r+");
    DIR *dir;

    char *pdir="--dir";
    char *phelp="--help";
    char *pexit="--exit";
    char *plogs="--logs";
    char userinput[size];
    int i;
    char cNewLine = '\n';
    while(1){
        printf("->");
        gets (userinput);

        i = 0;
        while ( userinput[i] != '\0' ){
            i ++;
        }
        if (!strcmp(plogs,userinput)){
            fprintf(myfile, "%s%s%c", dataTime,userinput,cNewLine);
            fflush(myfile);
            outputFileToScrean("logs.txt");
        }
        if (!strcmp(pdir,userinput)){
            outputFolder(pointer,dir);
        }
        if (!strcmp(phelp,userinput)){
            outputFileToScrean("help.txt");
        }
        if(!strcmp(pexit,userinput)){
            break;
        }
        if (strcmp(pdir,userinput)&&strcmp(phelp,userinput)&&strcmp(pexit,userinput)&&strcmp(plogs,userinput)){
            outputSpeciffolder(pointer,dir,userinput);
        }
        fprintf(myfile, "%s%s%c", dataTime,userinput,cNewLine);
        fflush(myfile);
    }
    fclose(myfile);
}
void addHelpFile(){
    FILE* myfile; myfile = fopen("help.txt","w");
    char *words="Commands:\n1)--dir\n2)C:\\Program Files\\...\n3)--help\n4)--logs\n5)--exit\n";
    fprintf(myfile, "%s", words);
    fclose(myfile);
}
char *getCurrentTimeFormate(char *format){
    time_t rawtime;
    struct tm * timeinfo;
    static char buffer[128]="";

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    strftime (buffer,128,format,timeinfo);

    return buffer;
}
void outputFileToScrean(char * file){
    FILE *myfile;
    myfile = fopen(file,"r");

    char array[size];
    while (fgets(array,size,myfile)) {
        printf("%s",array);
    }
    fclose(myfile);
}
