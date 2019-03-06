#include <stdio.h>
#include "gdef.h"
#include "names.h"
int main()
{
    object firstProcess;
    initMemoryManager();
    initCommonSymbols();
	while(vm_execute(globalSymbol("systemProcess"),15000));
    return 0;
}