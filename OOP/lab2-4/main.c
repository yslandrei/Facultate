#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "offer.h"
#include "offersRepository.h"
#include "offersService.h"
#include "ui.h"
#pragma warning(disable:4996)

int main() {

	int oListLen = 0;
	offer oList[100];
	
	ui(oList, oListLen);
	
	return 0;
}