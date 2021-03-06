/****************************************************************
Copyright (C) AT&T 1992
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

#include "nlp.h"

 static int
#ifdef KR_headers
slen(s, len) register char *s; fint len;
#else
slen(register char *s, fint len)
#endif
{
	register char *s1 = s + len;
	while(s1 > s)
		if (*--s1 > ' ') {
			s1++;
			break;
			}
	return s1 - s;
	}

 void
#ifdef KR_headers
wrtsol_(msg, nmsg, x, y, msg_len) char *msg; fint *nmsg;
				  real *x, *y; fint msg_len;
#else
wrtsol_(char *msg, fint *nmsg, real *x, real *y, fint msg_len)
#endif
{
	char *b, *buf, *me;
	int i, len, nm;

	nm = (int)*nmsg;
	len = nm + 1;
	me = msg + nm*msg_len;
	for(b = msg; b < me; b += msg_len)
		len += slen(b,msg_len);
	b = buf = (char *)Malloc(len);
	if (nm)
		for(;;) {
		if (i = slen(msg, msg_len)) {
			strncpy(b, msg, i);
			b += i;
			}
		msg += msg_len;
		if (msg >= me)
			break;
		*b++ = '\n';
		}
	*b = 0;
	write_soln(buf, x, y);
	free(buf);
	}
