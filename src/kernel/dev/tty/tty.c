/*
 * Copyright (C) 2011-2013 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * tty.c - tty device driver
 */

#include <nanvix/const.h>
#include <nanvix/dev.h>
#include <nanvix/klib.h>
#include <nanvix/pm.h>
#include "tty.h"

/*
 * tty device.
 */
PUBLIC struct tty tty;

/*
 * Puts process to sleep if tty output buffer is full.
 */
PRIVATE void sleep_full()
{
	/* Sleep while output buffer is full. */
	while (KBUFFER_FULL(tty.output))
		sleep(&tty.output.chain, PRIO_TTY);
}

/*
 * Writes to the tty device.
 */
PRIVATE ssize_t tty_write(unsigned minor, const char *buf, size_t n)
{	
	const char *p;
	
	UNUSED(minor);
	
	p = buf;
	
	/* Write n characters. */
	while (n > 0)
	{
		sleep_full();
		
		/* Copy data to output tty buffer. */
		while ((n > 0) && (!KBUFFER_FULL(tty.output)))
		{
			KBUFFER_PUT(tty.output, *p);
			
			p++, n--;
		}
		
		/* Flushes tty output buffer. */
		console_write(&tty.output);
	}
		
	return ((ssize_t)(p - buf));
}

/*
 * tty device driver interface.
 */
PRIVATE struct cdev tty_driver = {
	NULL,       /* Read.  */
	&tty_write  /* Write. */
};

/*
 * Initializes the tty device driver.
 */
PUBLIC void tty_init()
{		
	/* Initialize buffers. */
	KBUFFER_INIT(tty.output);
	KBUFFER_INIT(tty.input);
	
	/* Initialize device drivers. */
	console_init();
	
	/* Register charecter device. */
	cdev_register(TTY_MAJOR, &tty_driver);
	
	/* Change kernel's output device. */
	chkout(DEVID(TTY_MAJOR, 0, CHRDEV));
	
	kprintf("INIT: tty initialized");
}