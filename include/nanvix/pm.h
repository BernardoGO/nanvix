/*
 * Copyright (C) 2011-2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * pm.h - Process management
 */

#ifndef PM_H_
#define PM_H_

	#include <i386/i386.h>
	#include <nanvix/config.h>
	#include <nanvix/const.h>
	#include <nanvix/region.h>
	#include <sys/types.h>
	#include <signal.h>
	
	/* Process quantum. */
	#define PROC_QUANTUM 100

	/* Process priorities. */
	#define PRIO_INODE  -60 /* Waiting for inode.         */
	#define PRIO_TTY    -40 /* Waiting for terminal I/O.  */
	#define PRIO_REGION -20 /* Waiting for memory region. */
	#define PRIO_USER    0 /* User priority.             */
	#define PRIO_DAEMON 20 /* Daemon priority.           */
	#define PRIO_INIT   40 /* init priority.             */
	
	/* Process flags. */
	#define PROC_FREE 1 /* Process is free. */

	/* Process states. */
	#define PROC_DEAD     0 /* Dead.                      */
	#define PROC_NEW      1 /* New.                       */
	#define PROC_ZOMBIE   2 /* Zombie.                    */
	#define PROC_RUNNING  3 /* Running.       	          */
	#define PROC_READY    4 /* Ready to execute.          */
	#define PROC_WAITING  5 /* Waiting (interruptible).   */
	#define PROC_SLEEPING 6 /* Waiting (uninterruptible). */
	#define PROC_STOPPED  7 /* Stopped.                   */

	/* Offsets to the process structure. */
	#define PROC_KESP      0 /* Kernel stack pointer.   */
	#define PROC_CR3       4 /* Page directory pointer. */
	#define PROC_INTLVL    8 /* Interrupt level.        */
	#define PROC_FLAGS    12 /* Process flags.          */
	#define PROC_RECEIVED 16 /* Received signasl.       */
	#define PROC_KSTACK   20 /* Kernel stack base.      */
	#define PROC_HANDLERS 24 /* Signals handlers.       */
	
	/* Clock frequency (in hertz). */
	#define CLOCK_FREQ 100
	
	/* Superuser ID. */
	#define SUPERUSER 0
	
	/* Superuser group ID. */
	#define SUPERGROUP 0

	/* Number of process memory regions. */
	#define NR_PREGIONS 6

#ifndef _ASM_FILE_

	/*
	 * Process.
	 */
	struct process
	{
		/* Hardcoded fields. */
    	dword_t kesp;              /* Kernel stack poiner.      */
    	dword_t cr3;               /* Page directory pointer.   */
		dword_t intlvl;            /* Interrupt level.          */
		int flags;                 /* Processflags (see above). */
    	int received;              /* Received signals.         */
    	void *kstack;              /* Kernel stack.             */
		sighandler_t handlers[32]; /* Signal handlers.          */
		
    	/* Memory information. */
		struct pte *pgdir;                 /* Page directory.         */
		struct pregion pregs[NR_PREGIONS]; /* Process memory regions. */
		size_t size;                       /* Process size.           */
		
		/* General information. */
		uid_t uid;    /* User ID.             */
		uid_t euid;   /* Efective user ID.    */
		uid_t suid;   /* Saved set-user-ID.   */
		gid_t gid;    /* Group ID.            */
		gid_t egid;   /* Efective user ID.    */
		gid_t sgid;   /* Saved set-group-ID.  */
    	pid_t pid;    /* Process ID.          */
    	pid_t father; /* Father's process ID. */
    	pid_t pgrp;   /* Process group ID.    */
    	id_t session; /* Session ID.          */
    	pid_t leader; /* Session leader.      */
    	int tty;      /* Attached tty.        */
    	
    	/* Timing information. */
    	int utime; /* User time.   */
    	int ktime; /* Kernel time. */
    	
    	/* Scheduling information. */
    	int state;              /* Current state.          */
    	int counter;            /* Remaining quantum.      */
    	int priority;           /* Priority.               */
    	int nice;               /* Nice for scheduling.    */
    	unsigned alarm;         /* Alarm.                  */
		struct process *next;   /* Next process in a list. */
		struct process **chain; /* Sleeping chain.         */
	};
	
	EXTERN void pm_init();
	
	EXTERN void sleep(struct process **chain, int priority);
	
	EXTERN void wakeup(struct process **chain);

	EXTERN void terminate(struct process *proc, int err);

	EXTERN void stop(struct process *proc);	
	
	EXTERN void resume(struct process *proc);
	
	EXTERN void abort(struct process *proc);	
	
	EXTERN void sndsig(struct process *proc, int sig);
	
	EXTERN void yield();
	
	EXTERN void sched(struct process *proc);
	
	#define KERNEL_RUNNING(p) ((p)->intlvl > 1)
	
	#define IS_SUPERUSER(p) \
		((p->uid == SUPERUSER) || (p->euid == SUPERUSER))
		
	
	
	EXTERN sighandler_t sig_default[NR_SIGNALS];

	/* Process table. */
	EXTERN struct process proctab[PROC_MAX];
	
	/*  Current running process. */
	EXTERN struct process *curr_proc;
	
	/*  init process. */
	#define INIT (&proctab[0])
	
	/* First process. */
	#define FIRST_PROC ((&proctab[1]))
	
	/* Last process. */
	#define LAST_PROC ((&proctab[PROC_MAX - 1]))

#endif /* _ASM_FILE */

#endif /* PM_H_ */