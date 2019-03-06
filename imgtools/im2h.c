#include <stdio.h>
#include <stdint.h>
#include "../gdef.h"
#include "../names.h"

void im2h()
{
    //printf("#include(\"gdef.h\");\n");
    // printout object table
    printf("// object table dump\n");
    printf("object symbols = %d;\n", symbols);
    printf("int currentMemoryPosition = %d;\n", currentMemoryPosition);
    printf("struct objectStruct objectTable[] = {\n");
    for(int i = 0; i < ObjectTableMax; i++)
    {
        printf("{%d,(short)%d,%d,(object*)%d}",
            objectTable[i].class,
            objectTable[i].referenceCount,
            objectTable[i].size,
            objectTable[i].size == 0?0:objectTable[i].memory - memoryBlock
            );
        if( i != ObjectTableMax -1)
            printf(", ");
        else
            printf("\n");
        if(i!= 0 && i % 30 == 0)
            printf("\n");
    }
    printf("};\n\n");
    printf("// objects memory dump\n");
    printf("object memoryBlock[] = {");
    for(int i = 0; i < MemoryBlockSize; i++)
    {
        printf("%d", memoryBlock[i]);
        if( i != MemoryBlockSize -1)
            printf(", ");
        else
            printf("\n");
        if(i != 0 && i % 80 == 0)
            printf("\n");
    }
     printf("};\n");
}

int main(int argc, char** argv)
{
    FILE *fp;
    object firstProcess;
    char *p, buffer[1024], cmd[1024];
    char* code;

    initMemoryManager();

    strcpy(buffer, argv[1]);
    p = buffer;
    fp = fopen(p, "r");

	if (fp == NULL) {
		sysError("cannot open image", p);
		exit(1);
    }
    imageRead(fp);
    initCommonSymbols();
	im2h();
    return 0;
}