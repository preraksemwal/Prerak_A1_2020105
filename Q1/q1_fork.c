#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h> // exec, fork
#include<sys/wait.h>
#include<sys/types.h>


int main(){
    printf("\n")  ;
 
    int pid_v, status;
    pid_v = fork();
                  

    if(pid_v<0){
        printf("forking failed");
        exit(0);
    }
    else if(pid_v==0){ // child
        printf("inside child...\n\n");

        FILE* fp = fopen("student_record.csv","r");    // file opening call

        if(fp==NULL){                              // error case handling
            perror("failed");
            exit(1);
        }

        int arr[6]={0};

        char buff[200];
        int consider=0, count=0;

        while(fgets(buff,sizeof(buff),fp)){
            char* token;
            token = strtok(buff,",");
            token = strtok(NULL,",");
            int stepIn = 0;
            if(*token=='A'){         // we only want to store A-section marks
                stepIn = 1;
                count++;
            }
            token = strtok(NULL,",");
            int index = 0;
            while(token!=NULL){
                if(stepIn==1){
                    char str[4];
                    strcpy(str,token);           // to copy
                    arr[index] += atoi(str);
                    index++;
                }
                token = strtok(NULL,",");
            }

            consider = 1;                       // from now on we will consider each horizontal row

        }

        printf("\t-----  Section - A  -----\n");

        for(int i=0;i<6;++i){
            printf("average score in Assignment - %d : %f\n",i+1,1.0*arr[i]/count);
        }
        fclose(fp);
        sleep(1);
        exit(0);
    }



    else{ // parent
        waitpid(pid_v,&status,0);                // waiting for child
        printf("\n\ninside parent...\n\n");

        FILE* fp = fopen("student_record.csv","r");

        if(fp==NULL){               // error handling
            perror("failed");
            exit(1);
        }

        int brr[6]={0};

        char buff[200];
        int consider=0, count=0;        // which line of excel to consider or not

        while(fgets(buff,sizeof(buff),fp)){   
            char* token;
            token = strtok(buff,",");
            token = strtok(NULL,",");
            int stepIn = 0;
            if(*token=='B'){         // we only want to store B-section marks
                stepIn = 1;
                count++;
            }
            token = strtok(NULL,",");        // reads in forms of token -
            int index = 0;
            while(token!=NULL){
                if(stepIn==1){
                    char str[4];
                    strcpy(str,token);
                    brr[index] += atoi(str);
                    index++;
                }
                token = strtok(NULL,",");
            }

            consider = 1;

        }

        printf("\t-----  Section - B  -----\n");

        for(int i=0;i<6;++i){
            printf("average score in Assignment - %d : %f\n",i+1,1.0*brr[i]/count);
        }
        fclose(fp);
        sleep(1);
        printf("\n\n=============================================================\n\n");
        exit(0);

    }
    return 0;
}
