/*
 *			s t r e q . c
 */
 
/*)LIBRARY
*/

#ifdef	DOCUMENTATION

title	streq	String Equality Test
index		String equality test

synopsis
	.s.nf
	streq(a, b);
	char		*a;
	char		*b;
	.s.f
Description

	Return TRUE if the strings are equal.

Bugs

#endif

#define	EOS	0
#define	FALSE	0
#define	TRUE	1

int
streq(s1, s2)
register char	*s1;
register char	*s2;
/*
 * TRUE if strings are identical
 */
{
	while (*s1++ == *s2) {
	    if (*s2++ == EOS)
		return (TRUE);
	}
	return (FALSE);
}
