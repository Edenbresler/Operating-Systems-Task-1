#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
    int n;
    uint64 exit_msg_addr; 
    char exit_msg[32];  //the maximum length of the exit message is 32

    // Get the integer status code from the first argument (position 0)
    argint(0, &n);
    argaddr(1, &exit_msg_addr);
    if(exit_msg_addr==0){
      exit(n, 0);
    }
    
    // Get the exit message string from the second argument (position 1)
    // if (fetchstr(exit_msg_addr, exit_msg, sizeof(exit_msg)) < 0) {
      
    // } 
    else {
      fetchstr(exit_msg_addr, exit_msg, sizeof(exit_msg));   //copyy 1
      exit(n, exit_msg);
    }

    return 0;  // not reached
}


uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  uint64 exit_msg;
  argaddr(0, &p);
  argaddr(1, &exit_msg);
  return wait(p, exit_msg);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_memsize(void)
{
    struct proc *p = myproc();
    return p->sz;
}

uint64
sys_set_affinity_mask(void)
{
  struct proc *p = myproc();
  int affinityMask;
  argint(0, &affinityMask);
  p->affinity_mask = affinityMask;
  p->effective_affinity_mask = affinityMask;
  return 0;
}