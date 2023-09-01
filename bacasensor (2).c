#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>        
#include <stdlib.h> 


void openfile(void);
void readfile(void);
int fd=0;
 
void  readfile(void)
{
  unsigned char ichar; 
  unsigned char dataread[1];
  int  i,ifd;
  
  FILE *datasensor = fopen("datasensor.txt","a");
  
  while (1) { 
	ifd = read(fd, &ichar, 1);
	printf("%d\n", ichar);
        if (ichar == 101) {
	    printf("data sensor : ");
	    ifd = read(fd, &dataread, 1);
	    printf("%.2x\n",dataread[0]);
	    fprintf(datasensor, "%.2x%.2x\n",dataread[0],dataread[1]);
	    
	}
	sleep(1);
  }
  fclose(datasensor);
  close(fd);
}

void openfile(void)
{
    if ((fd=open("/dev/ttyACM11", O_RDONLY)) < 0) {
        perror("Error Open File");
      	exit (1);
    } 
}

 
int  main()
{
	openfile();
	readfile();
        return 0;
}

