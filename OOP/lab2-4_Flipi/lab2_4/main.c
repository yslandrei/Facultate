#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include "teste.h"
#include "ui.h"

int main()
{
	run_tests();
	ui();
	_CrtDumpMemoryLeaks();
	return 0;
}
//pb 6 urmatoarea

/*
1
VL42ZRE
skoda
sedan
1
BT60BOT
bmw
sedan
1
CT08TST
vw
mini
1
VL50KMY
vw
suv
1
BT10ZEC
audi
sedan
8

*/