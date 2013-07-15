/*
 * Copyright (C) 2011-2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * mm/mm.c - Memory system module.
 */

#include <nanvix/const.h>
#include <nanvix/pm.h>
#include <nanvix/region.h>
#include <nanvix/klib.h>
#include <nanvix/mm.h>

/*
 * Initializes the memory system module.
 */
PUBLIC void mm_init()
{
	/* Initialize memory regions. */
	initreg();
}
/*
 * Checks a memory area.
 */
PUBLIC int chkmem(void *ptr, size_t size, int writable)
{
	struct pregion *preg;
	
	preg = findreg(curr_proc, (addr_t)ptr);
	
	if (preg == NULL)
		goto out0;
	
	lockreg(preg->reg);
	
	if (((addr_t)ptr + size) < (preg->start + preg->reg->size))
		goto out1;
	
	if (writable > accessreg(curr_proc, preg->reg))
		goto out1;
	
	unlockreg(preg->reg);
		
	return (1);

out1:
	unlockreg(preg->reg);
out0:
	return (0);
}

/*
 * Fetches a byte from user addresss space.
 */
PUBLIC int fubyte(void *addr)
{	
	char byte;
	
	if ((addr_t)addr > UBASE_VIRT)
	{
		if ((addr_t)addr < KBASE_VIRT)
		{
			if (ksetjmp(&curr_proc->kenv) != 0)
				return (-1);
			
			byte = (*((char *)addr));
			
			return ((int)byte);
		}
	}
	
	return (-1);
}
