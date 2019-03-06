#include <stdio.h>
#include "gdef.h"
#include "names.h"
int main()
{
    FILE *fp;
    object firstProcess;
    char *p, buffer[1024], cmd[1024];
    char* code;

    initMemoryManager();

    strcpy(buffer, "image.im");
    p = buffer;
    fp = fopen(p, "r");

	if (fp == NULL) {
		sysError("cannot open image", p);
		exit(1);
    }
    imageRead(fp);
    initCommonSymbols();
	while(vm_execute(globalSymbol("systemProcess"),15000));
    return 0;
}