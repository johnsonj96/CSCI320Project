#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

// Runs three processes with a 3:2:1 ratio of tickets.
// Stores the uptime of each process in the input array.
void
lottery(int retval[3], int time)
{
  int child = 0;
  int a = -1;
  int rc = 0;
  int childid[3] = {0,0,0};
  if (child == 0) {
	while (child < 3) {
	  child++;
	  rc = fork();
	  if (rc < 0) {
		exit(1);
	  }
	  else if (rc == 0) {
		settickets((4-child)*5);
		// Sleep so we can call the
		// process in scheduler.
		for (int i=0; i<time; i++) {
		  sleep(1);
		}
		exit(0);
	  }
	  else {
		childid[child-1] = rc;
	  }
	}
	int status = 0;
	while (status != -1) {
	  status = wait(&a);
	}
	while (child>0) {
	  retval[child-1] = puptime(childid[child-1]);
	  child--;
	}
  }
}

int
main(int argc, char *argv[])
{
  int a = 0;
  int b = 0;
  int c = 0;
  int time = 0;
  int retval[3] = {0,0,0};
  for (int i=0; i<5; i++) {
	time = i*10+10;
	printf("Test %d (%d ticks): ",i+1,time);
	lottery(retval, time);
	a += retval[0]/time;
	b += retval[1]/time;
	c += retval[2]/time;
	printf("%d, %d, %d\n",retval[0],retval[1],retval[2]);
	retval[0] = 0;
	retval[1] = 0;
	retval[2] = 0;
  }
  a /= 5;
  b /= 5;
  c /= 5;
  printf("The average time slices per tick for each process were: %d, %d, %d\n",a,b,c);
  return 0;
}