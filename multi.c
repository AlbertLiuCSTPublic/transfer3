/*--------- Multi-threaded "Hello World"-------*/

#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// look up the sched_yield() system call

#define _REENTRANT
#define DCE_COMPAT

#define MSG_BUF_SIZE 63

/*----------- Function Prototypes ------------------*/
void* producer(void*);
void* consumer();

int main (void)
{

  
  int frk;

  if((frk = fork()) < 0)
    printf("Error Creating Processes");

  if(frk != 0)
    consumer();
  else
    producer((ThreadInfo*)&info_ptr);
  unlink("fifo");
  return 0;
}


void* producer(void* arg){

  printf("Producer\r\n");
  char prdBuf[MSG_BUF_SIZE + 1];clear


	int fd, nwrite, i = 0;

  
  if((fd = open("fifo", O_RDONLY | O_NDELAY)) < 0)
    printf("open on fifo");

	for (;i < 3;i++)       
	{

      info->i = i * 20;
      info->d++;

      snprintf(prdBuf,MSG_BUF_SIZE + 1,"%s %d %f","Bonjour", i * 20, info->d++);

      if ((nwrite = write(fd, prdBuf, MSG_BUF_SIZE + 1)) <= 0)
        printf("Write Failed");

      printf("Write done/r/n");

	}
	return NULL;

}
void* consumer(){
  



	int fd, i = 0;
  char conBuf[MSG_BUF_SIZE + 1];

  if ((fd = open ("fifo", O_WRONLY|O_NDELAY)) < 0)
     printf("fifo open error\r\n");

	for (;;)
	{
      
      if(read (fd, conBuf, MSG_BUF_SIZE+1) < 0)
        printf("Read error");

      printf("String:%s Int:%d Double:%f\r\n", 1,2,3);

	}
	return NULL;
}



