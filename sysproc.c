#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
enum trace Current_Trace = TRACE_OFF;
int call_count[23]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// System call added by me sys_toggle


int 
sys_toggle(void)
{
    if(Current_Trace == TRACE_OFF){
    	Current_Trace = TRACE_ON;
    	for(int i=0;i<23;i++){
    	call_count[i]=0;
    	}
    }
    else{
    	Current_Trace = TRACE_OFF;
    }
   // printf("current_trace = %d",Current_Trace);
return Current_Trace;
}



int
sys_print_count(void)
{
//atic int temp[22];
int c_fork    = call_count[0];
int c_exit    = call_count[1];
int c_wait    = call_count[2];
int c_pipe    = call_count[3];
int c_read    = call_count[4];
int c_kil     = call_count[5];
int c_exec    = call_count[6];
int c_fstat   = call_count[7];
int c_chdir   = call_count[8];
int c_dup     = call_count[9];
int c_getpid  = call_count[10];
int c_sbrk    = call_count[11];
int c_sleep   = call_count[12];
int c_uptime  = call_count[13];
int c_open    = call_count[14];
int c_write   = call_count[15];
int c_mknod   = call_count[16];
int c_unlink  = call_count[17];
int c_link    = call_count[18];
int c_mkdir   = call_count[19];
int c_close   = call_count[20];
int c_toggle  = call_count[21];
int c_pt_count  = call_count[22];
/////////////////////////////////////////

if(c_chdir >0){
  cprintf("%s %d\n","SYS_chdir",c_chdir);
}
if(c_close >0){
   cprintf("%s %d\n","SYS_close",c_close);
}
if(c_dup >0){
   cprintf("%s %d\n","SYS_dup",c_dup);
}
if(c_exec >0){
   cprintf("%s %d\n","SYS_exec",c_exec);
}
if(c_exit >0){
   cprintf("%s %d\n","SYS_exit",c_exit);
}
if(c_fork >0){
   cprintf("%s %d\n","SYS_fork",c_fork);
}
if( c_fstat>0){
   cprintf("%s %d\n","SYS_fstat",c_fstat);
}
if(c_getpid >0){
   cprintf("%s %d\n","SYS_getpid",c_getpid);
}
if(c_kil >0){
   cprintf("%s %d\n","SYS_kill",c_kil);
}
if(c_link >0){
   cprintf("%s %d\n","SYS_link",c_link);
}
if( c_mkdir>0){
   cprintf("%s %d\n","SYS_mkdir",c_mkdir);
}
if( c_mknod>0){
   cprintf("%s %d\n","SYS_mknod",c_mknod);
}
if(c_open >0){
   cprintf("%s %d\n","SYS_open",c_open);
}
if( c_pipe>0){
   cprintf("%s %d\n","SYS_pipe",c_pipe);
}
if( c_pt_count>0){
   cprintf("%s %d\n","SYS_print_count",c_pt_count);
}
if( c_read>0){
   cprintf("%s %d\n","SYS_read",c_read);
}
if( c_sbrk>0){
   cprintf("%s %d\n","SYS_sbrk",c_sbrk);
}
if( c_sleep>0){
   cprintf("%s %d\n","SYS_sleep",c_sleep);
}
if(c_toggle >0){
   cprintf("%s %d\n","SYS_toggle",c_toggle);
}
if( c_unlink>0){
   cprintf("%s %d\n","SYS_unlink",c_unlink);
}
if( c_uptime>0){
   cprintf("%s %d\n","SYS_uptime",c_uptime);
}
if(c_wait >0){
   cprintf("%s %d\n","SYS_wait",c_wait);
}
if( c_write>0){
   cprintf("%s %d\n","SYS_write",c_write);
}

return 23;
}





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

int
sys_wait(void)
{
  return wait();
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
