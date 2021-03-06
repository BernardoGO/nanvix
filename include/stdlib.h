/*
 * Copyright(C) 2011-2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * <stdlib.h> - Standard library.
 */

#ifndef STDLIB_H_
#define STDLIB_H_

	#include <sys/types.h>

	/* Unsuccessful termination. */
	#define EXIT_FAILURE 1
	
	/* Successful termination. */
	#define EXIT_SUCCESS 0

	/* Null pointer. */
	#ifndef NULL
		#define NULL ((void *)0)
	#endif
	
	/*
	 * Registers a function to run at process termination.
	 */
	extern int atexit(void(*func)(void));
	
	/*
	 * Converts a string to an integer.
	 */
	extern int atoi(const char *str);
	
	/*
	 * Terminates the calling process.
	 */
	extern void exit(int status);
	
	/*
	 * Frees memory.
	 */
	extern void free(void *ptr);
	
	/*
	 * Gets value of an environment variable.
	 */
	extern char *getenv(const char *name);
	
	/*
	 * Allocates memory.
	 */
	extern void *malloc(size_t size);
		
	/*
	 * Converta a string to a long integer.
	 */
	extern long strtol(const char *nptr, char **endptr, int base);
	
	/*
	 * Converts a string to an unsigned long.
	 */
	extern unsigned long strtoul(const char *str, char **endptr, int base);

#endif /* STDLIB_H_ */
