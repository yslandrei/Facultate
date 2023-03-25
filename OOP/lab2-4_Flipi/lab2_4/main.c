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