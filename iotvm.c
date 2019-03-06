#include <stdio.h>
#include "gdef.h"
#include "names.h"
int main()
{
    object firstProcess;
    initMemoryManager();
    initCommonSymbols();
    firstProcess = globalSymbol("systemProcess");
	while(vm_execute(firstProcess,15000));
    return 0;
}