#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include<unistd.h> // exec, fork
#include<pthread.h>
#include<sched.h>  // clone
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void A(){
   printf("Inside function A\n");
   
}

int main(){  // fd - 0:read  1:write  2:stderr  

   


   int fd = open("avenger.txt",O_CREAT|O_WRONLY|O_APPEND); 
   char c[20];
   read(0,c,20);
   write(fd,c,strlen(c));




}
