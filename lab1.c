#include "types.h" 
#include "user.h" 


int test_exitwithwait(void);
int test_waitpid(void);

int main(int argc, char *argv[]){

  printf(1, "\n Lab1 code check \n");
  
  if (atoi(argv[1]) == 1){
    test_exitwithwait();
  }
  else if (atoi(argv[1]) == 2){
    test_waitpid();
  }
  else{ 
    printf(1, "\n wrong argument \n");
  }
  exitwithstatus(0);

  return 0;
 }
  
  int test_exitwithwait(void) {
  int pid; 
  int return_pid;
  int exit_status;
  int i;
 
  printf(1, "\n  exit with wait test \n");

  for(i = 0; i < 2; i++) 
  {
    pid = fork();
    if(pid == 0){
    if(i == 0){
        printf(1, "\n child pid = %d && exit status = %d \n", getpid(), 0);
        exitwithstatus(0);
    }
    else{
	    printf(1, "\n child pid = %d && exit status = %d \n" ,getpid(), -1);
        exitwithstatus(-1);
      } 
    }  
    else if (pid > 0){
        return_pid = wait(&exit_status);
        printf(1, "\nparent process (child pid = %d, && exit status = %d)\n", return_pid, exit_status);
    } 
    else{ // fork error
        printf(2, "\n Fork() error \n");
        exitwithstatus(-1);
    }
  }// end of for loop
  return 0;
}

int test_waitpid(void){
  int return_pid;
  int exit_status;
  int i;
  int pid_a[5]={0, 0, 0, 0, 0};
  // wait test

  printf(1, "\n testing waitpid():\n");

  for(i = 0; i <5; i++) {
    pid_a[i] = fork();
    if (pid_a[i] == 0) { // child runs this code
      printf(1, "\n child pid = %d && exit status = %d \n", getpid(), getpid() + 4);
      exitwithstatus(getpid() + 4);
    }
  }
       
  sleep(5);
  printf(1, "\n parent process, wait for child PID# %d \n",pid_a[3]);
  return_pid = waitpid(pid_a[3], &exit_status, 0);
  printf(1, "\n parent process, child# %d, exit status %d \n",return_pid, exit_status);
  sleep(5);
  printf(1, "\n parent process, wait for child PID# %d \n",pid_a[1]);
  return_pid = waitpid(pid_a[1], &exit_status, 0);
  printf(1, "\n parent process, child# %d, exit status %d \n",return_pid, exit_status);
  sleep(5);
  printf(1, "\n parent process, wait for child PID# %d \n",pid_a[2]);
  return_pid = waitpid(pid_a[2], &exit_status, 0);
  printf(1, "\n parent process, child# %d, exit status %d \n",return_pid, exit_status);
  sleep(5);
  printf(1, "\n parent process, wait for child PID# %d \n",pid_a[0]);
  return_pid = waitpid(pid_a[0], &exit_status, 0);
  printf(1, "\n parent process, child# %d, exit status %d \n",return_pid, exit_status);
  sleep(5);
  printf(1, "\n parent process, wait for child PID# %d \n",pid_a[4]);
  return_pid = waitpid(pid_a[4], &exit_status, 0);
  printf(1, "\n parent process, child# %d, exit status %d \n",return_pid, exit_status);
      
  return 0;
}