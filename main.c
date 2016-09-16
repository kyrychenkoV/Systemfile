#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#define line "____________________________________"
void outData();
void outputFolder(struct dirent *pointer,DIR *dir);
void outputSpeciffolder(struct dirent *pointer,DIR *dir,char *directory);
void logFile(struct dirent *pointer,DIR *dir,char *directory);
void addFile();
void outputHelpToscreen(struct dirent *pointer,DIR *dir,char *directory);
void times();

int main() {
    outData();
    return 0;
}
void outData(){
    //1 task
    DIR *dir;
    struct dirent *pointer;
    printf("The files in the current directory\n");
    outputFolder(pointer,dir);
    printf(line"\n");
    //2 task
    char *directory="c:program files/Git";
    printf("The files in the c:Program files/Git\n");
    // 3 task
    addFile();
    logFile(pointer,dir,directory);
}

void outputFolder(struct dirent *pointer,DIR *dir){
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

void logFile(struct dirent *pointer,DIR *dir,char *directory){

    outputSpeciffolder(pointer,dir,directory);
    outputHelpToscreen(pointer,dir,directory);
    printf("\n");
    times();
}
void addFile(){         //add file help.txt end file write word "HELP!"
    FILE* myfile;
    if ((myfile = fopen("D:/Qt/Progect/Systemfile/help.txt","a"))==NULL) {
        printf("Eror .\n");
        exit(1);
    }
    fclose(myfile);
}

void outputHelpToscreen(struct dirent *pointer,DIR *dir,char *directory){
    FILE *myfile;
    if ((myfile = fopen("D:/Qt/Progect/Systemfile/help.txt","r"))==NULL) {
        printf("Eror .\n");
        exit(1);
    }
    printf("Do you want to open a help file Y/N\n");

    char array[20];
    char a;
    scanf("%c",&a);
    if (a=='Y'){
        while (fgets(array,20,myfile)) {
            printf("%s",array);
        }
    }
    fclose(myfile);
}
void times(){
    struct tm *ptr;
    time_t It;
    It = time(NULL);
    ptr = localtime(&It);
    printf(asctime(ptr));
    return 0;
}


