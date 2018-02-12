
// Implementation
// https://sourceforge.net/p/mingw/msys-runtime/ci/14ef9f7b676ea6031d76c09f1e4cd256327cada4/tree/libiberty/ffs.c?diff=5e5798c0a39572f38a121bd761b925916ae77158
//


/* ffs -- Find the first bit set in the parameter

NAME
	ffs -- Find the first bit set in the parameter

SYNOPSIS
	int ffs (int valu)

DESCRIPTION
	Find the first bit set in the parameter. Bits are numbered from
	right to left, starting with bit 1.

*/

int ffs(valu) 
register int valu;
{
	register int bit;

	if (valu == 0)
		return 0;
	
	for (bit = 1; !(valu & 1); bit++)
		valu >>= 1;
	
	return bit;
}
