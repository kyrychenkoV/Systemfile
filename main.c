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
void logFile(struct dirent *pointer);
void addFile();
void outputHelpToscreen();

void outputLogstoScreen();

int main() {
    outData();
    return 0;
}

void outData(){
    addFile();
    struct dirent *pointer;
    logFile(pointer);
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

void logFile(struct dirent *pointer){
    FILE* myfile;
    myfile = fopen("logs.txt","a+");

    DIR *dir;
    struct tm *ptr;
    time_t It;
    It = time(NULL);
    ptr = localtime(&It);

    char *pdir="--dir";
    char *phelp="--help";
    char *pexit="--exit";
    char *plogs="--logs";
    char q[size];
    int i;
    while(1){
        printf("->");
        gets (q);
        i = 0;
        while ( q[i] != '\0' ){
            i ++;
        }
        if (!strcmp(plogs,q)){
            outputLogstoScreen();
            fprintf(myfile, "--logs: %s", asctime(ptr));
        }
        if (!strcmp(pdir,q)){
            outputFolder(pointer,dir);
            fprintf(myfile, "--myDir: %s", asctime(ptr));
        }
        if (!strcmp(phelp,q)){
            outputHelpToscreen();
            fprintf(myfile, "--help: %s", asctime(ptr));
        }
        if(!strcmp(pexit,q)){
            break;
        }
        if (strcmp(pdir,q)&&strcmp(phelp,q)&&strcmp(pexit,q)&&strcmp(plogs,q)){
            outputSpeciffolder(pointer,dir,q);
            fprintf(myfile, "--anyDir: %s", asctime(ptr));
        }
    }
}
void addFile(){
    FILE* myfile; myfile = fopen("help.txt","w");
    char *words="Commands:\n1)--dir\n2)C:\\Program Files\\...\n3)--help\n4)--logs\n5)--exit\n";
    fprintf(myfile, "%s", words);
    fclose(myfile);
}

void outputHelpToscreen(){
    FILE *myfile;
    myfile = fopen("help.txt","r");

    char array[size];
    while (fgets(array,size,myfile)) {
        printf("%s",array);
    }
    fclose(myfile);
}
void outputLogstoScreen(){
    FILE *myfile;
    myfile = fopen("logs.txt","r+");

    char array[size];
    while (fgets(array,size,myfile)) {
        printf("%s",array);
    }
    fclose(myfile);
}
