/****************************************************************
Copyright (C) AT&T 1992, 1993, 1994
All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the name of AT&T or any of its entities
not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

AT&T DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
IN NO EVENT SHALL AT&T OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
****************************************************************/

#ifdef __cplusplus
extern "C" {
#include "memory.h"
#endif
#ifndef No_dtoa
#include "arith.h"
#undef Use_dtoa_
#define Use_dtoa_
#endif

#ifdef Use_dtoa_
#include "math.h"
#undef  __MATH_H__
#define __MATH_H__

#ifdef __cplusplus
extern "C" char *dtoa(double, int, int, int*, int*, char **);
extern "C" double strtod(const char*, char**);
#else
#ifdef __STDC__
extern char *dtoa(double, int, int, int*, int*, char **);
extern double strtod(const char*, char**);
#else
extern char *dtoa();
extern double strtod();
#endif
#endif
#define No_leftright
#ifndef MALLOC
#define MALLOC dtoamalloc
#include "dtoa.c"

#include "stdio.h"

#ifdef KR_headers
#define Void char
 char *
dtoamalloc(x) unsigned x;
#else
#define Void void
#include "stdlib.h"

 void *
dtoamalloc(size_t x)
#endif
{
	Void *rv = malloc(x);
	if (!rv) {
		fputs("\nmalloc failure in dtoa!\n", stderr);
		exit(63);
		}
	return rv;
	}
#else
#include "dtoa.c"
#endif
#else
#ifdef KR_headers
 extern char *ecvt(), *fcvt();

 char *
dtoa(d, mode, ndigits, decpt, sign, rve)
	double d; int mode, ndigits, *decpt, *sign; char **rve;
#else
extern char *ecvt(double value, int ndigit, int *decpt, int *sign);
extern char *fcvt(double value, int ndigit, int *decpt, int *sign);

 char *
dtoa(double d, int mode, int ndigits, int *decpt, int *sign, char **rve)
#endif
{
	char *s, *s1;

	if (!d) {
		*decpt = 1;
		s = "0";
		if (rve)
			*rve = s + 1;
		return s;
		}
	if (mode > 3)
		mode = 2 + (mode & 1);
	if (mode == 3)
		s = fcvt(d, ndigits, decpt, sign);
	else {
		if (mode <= 1)
			ndigits = 15;
		s = ecvt(d, ndigits, decpt, sign);
		}
	if (*(s1 = s)) {
		while(*++s1);
		while(--s1 > s && *s1 == '0');
		*++s1 = 0;
		}
	if (rve)
		*rve = s1;
	return s;
	}
#endif
#ifdef __cplusplus
}
#endif
