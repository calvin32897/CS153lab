#include "types.h"
#include "user.h"


int main(int argc, char *argv[])
{
  int exitWait(void);
  int waitPid(void);
  int PScheduler(void);

  printf(1, "\n This program tests the correctness of your lab#1\n");
  
  if (atoi(argv[1]) == 1)
    exitWait();
  else if (atoi(argv[1]) == 2)
    waitPid();
  else if (atoi(argv[1]) == 3)
    PScheduler();
  else if (atoi(argv[1]) == 4)
    age();
  else 
    printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to test waitpid and \"lab1 3\" to test the priority scheduler \n");

  exit(0);
 }
 
int exitWait(void) {
  int pid, ret_pid, exit_status;
  int i;
  
  printf(1, "\n  Step 1: testing exit(int status) and wait(int* status):\n");

  for (i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0) { 
      if (i == 0)
      {
        printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), 0);
        exit(0);
      }
      else
      {
        printf(1, "\nThis is child with PID# %d and I will exit with status %d\n" ,getpid(), -1);
        exit(-1);
      } 
    } 
    else if (pid > 0) { 
      ret_pid = wait(&exit_status);
      printf(1, "\n This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
    } else  
    {  
      printf(2, "\nError using fork\n");
      exit(-1);
    }
  }
  return 0;
}

int waitPid(void){	
  int ret_pid, exit_status;
  int i;
  int pid_a[5]={0, 0, 0, 0, 0};

  printf(1, "\n  Step 2: testing waitpid(int pid, int* status, int options):\n");

  for (i = 0; i <5; i++) {
    pid_a[i] = fork();
	
    if (pid_a[i] == 0) { 
      
      printf(1, "\n The is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);}}
       
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[3]);
      ret_pid = waitpid(pid_a[3], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[1]);
      ret_pid = waitpid(pid_a[1], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[2]);
      ret_pid = waitpid(pid_a[2], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[0]);
      ret_pid = waitpid(pid_a[0], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[4]);
      ret_pid = waitpid(pid_a[4], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      
      return 0;
  }
      
      
int PScheduler(void){
		 
  int pid, ret_pid, exit_status;
  int i,j,k;
  
  printf(1, "\n  Step 2: testing the priority scheduler and setpriority(int priority)) systema call:\n");
  printf(1, "\n  Step 2: Assuming that the priorities range between range between 0 to 31\n");
  printf(1, "\n  Step 2: 0 is the highest priority. All processes have a default priority of 20\n");
  printf(1, "\n  Step 2: The parent processes will switch to priority 0\n");
  setpriority(0);
  for (i = 0; i <  3; i++) {
    pid = fork();
    if (pid > 0 ) {
      continue;}
    else if ( pid == 0) {
      setpriority(30-10*i);
      printf(1, "\n child# %d with priority %d has started! \n",getpid(),30-10*i);
      //printf("PID: %d has exited.\n", curproc->pid); //cs153_lab2: print pid
      //printf("Ending priority: %d\n", curproc->priority); //cs153_lab2: print ending priority
      //printf("Turn time: %d\n", curproc->turnTime); //cs153_lab2: print turn time
      //printf("Wait time: %d\n", curproc->waitTime); //cs153_lab2: print wait time
      //printf("Burst time: %d\n", curproc->burstTime); //cs153_lab2: print burst time
      for (j=0;j<50000;j++) {
        for(k=0;k<10000;k++) {
	  asm("nop"); 
        }
      }
      printf(1, "\n child# %d with priority %d has finished! \n",getpid(),30-10*i);
      //printf("PID: %d has exited.\n", curproc->pid); //cs153_lab2: print pid
      //printf("Ending priority: %d\n", curproc->priority); //cs153_lab2: print ending priority
      //printf("Turn time: %d\n", curproc->turnTime); //cs153_lab2: print turn time
      //printf("Wait time: %d\n", curproc->waitTime); //cs153_lab2: print wait time
      //printf("Burst time: %d\n", curproc->burstTime); //cs153_lab2: print burst time
      exit(0);
    }
    else {
      printf(2," \n Error \n");
      exit(-1);
    }
  }

  if(pid > 0) {
    for (i = 0; i <  3; i++) {
      ret_pid = wait(&exit_status);
    }
    printf(1,"\n if processes with highest priority finished first then its correct \n");
  }
			
return 0;
}

int age(void){
  int pid;
  int i,j;
  pid=fork();
  if(pid>0){ //parent
    setpriority(0);
    for(i=0;i<1000;i++){
      printf(1,"P");
    }
    wait(0);
  }
  else{
   setpriority(5);
   for(j=0;j<1000;j++){
     printf(1,"C");
   }
  }
printf(1, "DONE!");
return 0;
}
