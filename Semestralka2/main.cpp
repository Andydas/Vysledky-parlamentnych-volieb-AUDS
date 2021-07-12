#include "app.h"
#include "Typ_UJ.h"
#include <iostream>
#include "uzemna_jednotka.h"
#include "../structures/heap_monitor.h"

using namespace std;

int main()
{
	initHeapMonitor();

	App* aplikacia = new App();
	//aplikacia->nacitajK();

	//aplikacia->vypisUJ();
	//aplikacia->vypisPS();
	//aplikacia->vypisK();

	

	//aplikacia->testik();

	delete aplikacia;
	return 0;
}