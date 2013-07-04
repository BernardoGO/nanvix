/*
 * Copyright (C) 2011-2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * sched.c - Process scheduler.
 */

#include <asm/util.h>
#include <nanvix/const.h>
#include <nanvix/pm.h>
#include <nanvix/clock.h>
#include <signal.h>


/*
 * Handles a signal by stoping the process
 */
PUBLIC void stop(struct process *proc)
{
	proc->state = PROC_STOPPED;
	
	yield();
}

/*
 * Handles a signal by continuing the process.
 */
PUBLIC void resume(struct process *proc)
{	
	/* Resume only if process is stopped. */
	if (proc->state == PROC_STOPPED)
		sched(proc);
}


/*
 * Shedules the execution of a process.
 */
PUBLIC void sched(struct process *proc)
{
	proc->state = PROC_READY;
	proc->counter = 0;
}

/*
 * Yields the processor.
 */
PUBLIC void yield()
{
	int eprio;
	struct process *p;
	struct process *next;
	
	/* Re-schedule process for execution. */
	if (curr_proc->state == PROC_RUNNING)
		sched(curr_proc);

	/* Check alarm. */
	for (p = FIRST_PROC; p <= LAST_PROC; p++)
	{
		/* Valid process. */
		if (p->state != PROC_DEAD)
		{
			/* Alarm has expired. */
			if ((p->alarm) && (p->alarm < ticks))
				sndsig(p, SIGALRM);
		}
	}

	/* Choose a process to execute. */
	next = INIT;
	eprio = next->priority + p->nice + p->counter;
	for (p = FIRST_PROC; p <= LAST_PROC; p++)
	{
		/* Ready process. */
		if (p->state == PROC_READY)
		{
			/* Process with higher priority found. */
			if ((p->priority + p->nice + p->counter) < eprio)
			{
				next = p;
				eprio = next->priority + p->nice + p->counter;
			}
			/* Increment age of process. */
			else
				p->counter++;
		}
	}
	
	/* Switch to process. */
	p->state = PROC_RUNNING;
	p->counter = PROC_QUANTUM;
	switch_to(next);
}