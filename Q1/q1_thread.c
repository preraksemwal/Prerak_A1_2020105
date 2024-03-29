#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h> // exec, fork
#include<pthread.h>
#include<sys/wait.h>
#include<sys/types.h>



int arr[6]={0};                   //  section A
int brr[6]={0};                     // section B
int total = 0;                              // total students in sheet


void* thread2_caller(void* args){

    printf("inside child thread...\n\n");

    FILE* fp = fopen("student_record.csv","r");

    if(fp==NULL){
        perror("failed to open file (section A)");
        exit(1);
    }

    char buff[200];
    int consider=0, count=0;                     // when to consider horizontal row or not

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
                strcpy(str,token);
                arr[index] += atoi(str);
                index++;
            }
            token = strtok(NULL,",");
        }

        consider = 1;
    }

    printf("\t-----  Section - A  -----\n");

    for(int i=0;i<6;++i){
        printf("average score in Assignment - %d : %f\n",i+1,1.0*arr[i]/count);
    }

    total += count;
    fclose(fp);
    sleep(1);

}

void* thread1_caller(void* args){
    
    pthread_t t2_v;
    int ret2_v = pthread_create(&t2_v, NULL, thread2_caller, NULL);
    if(ret2_v!=0)
        perror("threading failed (section A)\n");

    pthread_join(t2_v,NULL);

    printf("\n\ninside parent Thread...\n\n");

    FILE* fp = fopen("student_record.csv","r");

    if(fp==NULL){
        perror("failed");                                   // error case
        exit(1);
    }

    char buff[200];                     // buffer for readinf the file
    int consider=0, count=0;

    while(fgets(buff,sizeof(buff),fp)){
        char* token;
        token = strtok(buff,",");
        token = strtok(NULL,",");
        int stepIn = 0;
        if(*token=='B'){         // we only want to store B-section marks
            stepIn = 1;
            count++;
        }
        token = strtok(NULL,",");
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
        printf("average score in Assignment : %d : %f\n",i+1,1.0*brr[i]/count);
    }
    total += count;
    fclose(fp);
    sleep(1);
    
}

int main(){  
    printf("\n\n");
 
    pthread_t t1_v;
    int ret1_v = pthread_create(&t1_v, NULL, thread1_caller, NULL);
                  

    if(ret1_v!=0)
        perror("threading failed (section B)\n");
        
    pthread_join(t1_v,NULL);


    printf("\n\nboth threads terminated!\n\n");

    
    for(int i=0;i<6;++i){
        printf("average score of both section in Assignment %d - %f\n",i+1,1.0*(arr[i]+brr[i])/total );
    }
    return 0;
}
