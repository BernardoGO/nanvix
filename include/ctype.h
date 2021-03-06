/* 
 * Copyright(C) 2011-2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * This file is part of Nanvix.
 * 
 * Nanvix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Nanvix.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _CTYPE_H_
#define _CTYPE_H_

	/* Character types. */
	#define	_U	0x01 /* Upper-case character.         */
	#define	_L	0x02 /* Lower-case character.         */
	#define	_N	0x04 /* Decimal number character.     */
	#define	_S	0x08 /* White-space character.        */
	#define	_P	0x10 /* Punctuation character.        */
	#define	_C	0x20 /* Control character.            */
	#define	_X	0x40 /* Hexadecimal number character. */
	#define	_B	0x80 /* Blank space character.        */
	
	/*
	 * Character type table.
	 */
	extern unsigned char _ctype[];
	
	/*
	 * Lower character map.
	 */
	extern char _maplower[1 + 256];
	
	/*
	 * Upper character map.
	 */
	extern char _mapupper[1 + 256];

	/*
	 * Checks for an alphanumeric character.
	 */
	#define	isalnum(c)((_ctype + 1)[c] & (_U|_L|_N))
	
	/*
	 * Checks for an alphabetic character.
	 */
	#define	isalpha(c) ((_ctype + 1)[c] & (_U|_L))
	
	/*
	 * Checks for a blank character.
	 */
	#define	isblank(c) ((c) == '\t' || (c) == ' ')
	
	/*
	 * Checks for a control character.
	 */
	#define	iscntrl(c) ((_ctype + 1)[c] & _C)
	
	/*
	 * Checks for a decimal digit.
	 */
	#define	isdigit(c) ((_ctype + 1)[c] & _N)
	
	/*
	 * Checks for a visible character.
	 */
	#define	isgraph(c) ((_ctype + 1)[c] & (_P|_U|_L|_N))
	
	/*
	 * Checks for a lowercase character.
	 */
	#define	islower(c) ((_ctype + 1)[c] & _L)
	
	/*
	 * Checks for a printable character.
	 */
	#define	isprint(c) ((_ctype + 1)[c] & (_P|_U|_L|_N|_B))
	
	/*
	 * Checks for a punctuation character.
	 */
	#define	ispunct(c) ((_ctype + 1)[c] & _P)
	
	/*
	 * For a white-space character.
	 */
	#define	isspace(c) ((_ctype + 1)[c] & _S)
	
	/*
	 * Checks for an uppercase letter.
	 */
	#define	isupper(c) ((_ctype + 1)[c] & _U)
	
	/*
	 * Checks for a hexadecimal digit.
	 */
	#define	isxdigit(c) ((_ctype + 1)[c] & (_N|_X))
	
	/*
	 * Transliterates an uppercase character to a lowercase character.
	 */
	#define	tolower(c) ((_maplower + 1)[c])
	
	/*
	 * Transliterates a lowercase character to an uppercase character.
	 */
	#define	toupper(c) ((_mapupper + 1)[c])

#endif /* !_CTYPE_H_ */
