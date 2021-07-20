#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

//edit for lab 1
int
sys_wait(void)
{
  int* s;
  argptr(0, (void*)&s, sizeof(s));
  return wait(s);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// for lab 1
// reads arugument in int  and calls exit system
int 
sys_modEx(void)
{
  int exitstatus;
if(arginint(0,&exitstatus)<0)
{
  return -1;
}
return modEx(exitstatus);

}

// adding waitpit for lab 1
// This system call must act like wait system call with the following additional properties: 
//The system call must wait for a process (not necessary a child process) with a pid that equals to one provided by the pid argument. 
//The return value must be the process id of the process that was terminated or -1 if this process does not exist or if an unexpected error occurred.

int 
sys_waitpid(void) 
{
  int pid;
  int options =0;
  int* s;
  
  if(argint(0,&pid) < 0)
  {
    return -1; // return value if procvess does not exist or an error occured.
  }
  else if(argptr(1, (void*)&s, sizeof(s)) < 0)
  {
    return 0;
  }
  else if(argint(2, &options) < 0)
  {
    return -1;
  }

  return waitpid(pid, s, options);
}
