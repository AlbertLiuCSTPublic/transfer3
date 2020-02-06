/*-------- Send messages using a FIFO -------------*/
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGSIZE   63

/*--------- globals ----------------*/
extern int  errno;
char *fifo = "fifo";
char *lock = "lock";

int main (int argc, char *argv[])
{
  int fd, lk;
  int j, nwrite;
  char msgbuf[MSGSIZE+1];
  char repbuf[MSGSIZE+1];

  char *arg[] = {"Hello","Bonjour","Bye"};
  /*-- Open fifo with O_NDELAY set ----*/
  if ((fd = open (fifo, O_WRONLY|O_NDELAY)) < 0)
    perror ("fifo open failed!");

  if ((lk = open (lock, O_WRONLY)) < 0)
    perror ("lock open failed!");
  
  /*---- Send the messages ---------------*/
  for (j = 0; j < 3; j++)
  {
    

    snprintf(msgbuf,MSGSIZE + 1,"%s %d %f\r\n",arg[j], (j + 1)  * (j + 1) , 2.4 * (j + 1));
    printf(msgbuf);


    if ((nwrite = write (fd, msgbuf, MSGSIZE+1)) <= 0)
    {
      if (nwrite == 0)     /* FIFO is full */
		errno = EAGAIN;   /* fake an error */
      perror ("Message write failed!");
    }
    read (lk, repbuf, MSGSIZE+1);
  }
  exit(0);
}
