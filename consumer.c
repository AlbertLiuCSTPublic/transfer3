/*----------- rcvmsg.c --- Receive messages via a FIFO -----*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGSIZE 63

/*-- Globals ------------*/
char *fifo = "fifo";
char *lock = "lock";

int main (int argc, char *argv[])
{
  int fd, lk;
  char msgbuf[MSGSIZE+1];

  char *str;
  int i;
  double d;
  
  unlink(fifo);
  unlink(lock);
  if(mknod(fifo,010600,0) < 0)
    printf("mknod (fifo) call");
  if(mknod(lock,010600,0) < 0)
    printf("mknod (lock) call");

  /*----- Open fifo for reading and writing ------*/
  if ((fd = open (fifo, O_RDWR)) < 0)
    perror ("fifo open failed");

  if ((lk = open (lock, O_RDWR)) < 0)
    perror ("fifo open failed");

  /*----- receive the messages -------*/
  for (;;)
  {

    if (read (fd, msgbuf, MSGSIZE+1) < 0)
      perror ("Message read failed!");

    sscanf(msgbuf,"%s %d %lf",str,&i,&d);
    printf ("String:%s Int:%d Double:%lf\r\n", str,i,d);

    write (lk, msgbuf, MSGSIZE+1);
  }
}
