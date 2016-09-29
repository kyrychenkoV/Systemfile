#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *getCurrentTimeFormate(char *format);
void outputFileToScrean(char * file);
void outputFileToScreanHELP(char * file);
void addHelpFile();
void outputFolder(struct dirent *pointer,DIR *dir);
void outputSpeciffolder(struct dirent *pointer,DIR *dir,char *directory);
int main(int argc, char *argv[]) {
    FILE *myfile;

    struct dirent *pointer;
    DIR *dir;
    int result;
    result=mkdir("c:/2");//new folder
    _chdir("c:\\2");//current folder

    char *pdir="--dir";
    char *phelp="--help";
    char *pexit="--exit";
    char *plogs="--logs";
    char cNewLine = '\n';

    char *dataTime=getCurrentTimeFormate("%Y-%m-%d %X:");
    myfile = fopen("logs.txt","a+");
    fprintf(myfile, "%s%s%c", dataTime,argv[1],cNewLine);
    fflush(myfile);
    fclose(myfile);
    if (strcmp(argv[1],plogs)==0){
        myfile = fopen("logs.txt","r+");
        fprintf(myfile, "%s%s%c", dataTime,argv[1],cNewLine);
        fflush(myfile);
        fclose(myfile);
        outputFileToScrean("logs.txt");
    }
    if (strcmp(argv[1],phelp)==0){
        addHelpFile();
        outputFileToScrean("help.txt");
    }
    if (strcmp(pdir,argv[1])==0){
        outputFolder(pointer,dir);
    }
    if(strcmp(argv[1],"--exit")==0){
        exit(1);
    }
    if (strcmp(pdir,argv[1])&&strcmp(phelp,argv[1])&&strcmp(pexit,argv[1])&&strcmp(plogs,argv[1])){
        outputSpeciffolder(pointer,dir,argv[1]);
    }
    return 0;
}
void outputFolder(struct dirent *pointer,DIR *dir){
    printf("The files in the current directory\n");
    dir = opendir("./");
    if (!dir) {
        perror("diropen");
        exit(1);
    }
    while ( (pointer = readdir(dir))) {
        puts (pointer->d_name);
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
    FILE *myf;
    myf = fopen(file,"r+");
    char array[20];
    while (fgets(array,20,myf)) {
        printf("%s",array);
    }
    fclose(myf);
}
void addHelpFile(){
    FILE* myfile; myfile = fopen("help.txt","w");
    char *words="Commands:\n1)--dir\n2)C:\\Program Files\\...\n3)--help\n4)--logs\n5)--exit\n";
    fprintf(myfile, "%s", words);
    fclose(myfile);
}