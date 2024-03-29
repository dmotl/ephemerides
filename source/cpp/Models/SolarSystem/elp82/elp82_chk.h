#ifndef _EPHEMERIS_ELP82_CHK_H_INCLUDED
#define _EPHEMERIS_ELP82_CHK_H_INCLUDED

#ifndef ELP82_TEST_DEFS_DEFINED
	#define ELP82_TESTS_DEFS_DEFINED
	typedef struct tELP82TestXYZ { double jd; double X, Y, Z; } tELP82TestXYZ;
#endif

	static const tELP82TestXYZ elp82_MOON_A[] =
	{
		{ 2469000.5, -361602.98536,  44996.99510, -30696.65316 },
		{ 2449000.5, -363132.34248,  35863.65378, -33196.00409 },
		{ 2429000.5, -371577.58161,  75271.14315, -32227.94618 },
		{ 2409000.5, -373869.15893, 127406.79129, -30037.79225 },
		{ 2389000.5, -346331.77361, 206365.40364, -28502.11732 }
	};

#endif
