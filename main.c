#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
void outData();
void outputFolder(struct dirent *pointer,DIR *dir);
void outputSpeciffolder(struct dirent *pointer,DIR *dir,char *directory);
void logFile(struct dirent *pointer,char *directory);
void addFile();
void outputHelpToscreen();
void times();

int main() {
    outData();
    return 0;
}
void outData(){
    struct dirent *pointer;
    char *directory="c:/Program Files";
    logFile(pointer,directory);


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
    printf("The files in the c:Program files/Git\n");
    dir = opendir(directory);
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

void logFile(struct dirent *pointer,char *directory){
    FILE* myfile;
    myfile = fopen("help.txt","a");

    DIR *dir;
    struct tm *ptr;
    time_t It;
    It = time(NULL);
    ptr = localtime(&It);

    printf("Do you want to open a current directory Y/N\n");
    char a,b,c;
    scanf("%c",&a);
    getchar();
    if (a=='Y'){
        outputFolder(pointer,dir);
        fprintf(myfile, "--myDir: %s", asctime(ptr));
    }
    printf("Do you want to open a any directory Y/N\n");
    scanf("%c",&b);
    getchar();
    if (b=='Y'){
        outputSpeciffolder(pointer,dir,directory);
        fprintf(myfile, "--anyDir: %s", asctime(ptr));
    }
    printf("Do you want to open a help file Y/N\n");
    scanf("%c",&c);
    getchar();
    if (c=='Y'){
        outputHelpToscreen();
        fprintf(myfile, "--help: %s", asctime(ptr));
    }
    printf("\n");
    times();

}
void addFile(){         //add file help.txt end file write word "HELP!"
    FILE* myfile; myfile = fopen("help.txt","a");

    fprintf(myfile, "%s", times);
    fclose(myfile);
}

void outputHelpToscreen(){
    FILE *myfile;
    myfile = fopen("help.txt","r");

    char array[20];
    while (fgets(array,20,myfile)) {
        printf("%s",array);
    }

    fclose(myfile);
}
void  times(){
    FILE* myfile;
    myfile = fopen("help.txt","a");


    struct tm *ptr;
    time_t It;
    It = time(NULL);
    ptr = localtime(&It);
}

