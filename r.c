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
void logFile(struct dirent *pointer,char *dataTime,char **argv);
void addHelpFile();
char *getCurrentTimeFormate(char *format);
void outputFileToScrean(char * file);
int main(int argc, char **argv) {
    printf("%s", argv[1]);


    addHelpFile();
    char *dataTime=getCurrentTimeFormate("%Y-%m-%d %X:");
    struct dirent *pointer;
    //logFile(pointer,dataTime,argv[0]);
    FILE* myfile;
    myfile = fopen("logs.txt","w");
    fclose(myfile);
    myfile = fopen("logs.txt","r+");
    DIR *dir;

    char *pdir="--dir";
    char *phelp="--help";
    char *pexit="--exit";
    char *plogs="-logs";
    char userinput[size];
    int i;
    char cNewLine = '\n';
    //while(1){
        printf("->");
       // gets (userinput);

        //i = 0;
        //while ( userinput[i] != '\0' ){
          // i ++;
        //}
        if (strcmp(argv[1],"-logs")==0){
            fprintf(myfile, "%s%s%c", dataTime,userinput,cNewLine);
            fflush(myfile);
            outputFileToScrean("logs.txt");
            exit(1);
        }
        if (strcmp(pdir,argv[1])==0){
		
            outputFolder(pointer,dir);
            exit(1);
        }
        if (strcmp(argv[1],phelp)==0){
	
            outputFileToScrean("help.txt");
            exit(1);
        }
        if(strcmp(argv[1],"--exit")==0){
        	exit(1);
        
            
        }
        if (strcmp(pdir,userinput)&&strcmp(phelp,userinput)&&strcmp(pexit,userinput)&&strcmp(plogs,userinput)){
            outputSpeciffolder(pointer,dir,userinput);
            exit(1);
        }
        fprintf(myfile, "%s%s%c", dataTime,userinput,cNewLine);
        fflush(myfile);
    //}
    fclose(myfile);
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

void logFile(struct dirent *pointer,char *dataTime,char **argv){
    
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
