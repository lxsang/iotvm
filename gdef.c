#include "gdef.h"

//boolean watching = 0;
object processStack;
int linkPointer;
object trueobj, falseobj;

#ifndef IMG_BUILD
#include "image.h"
#else
    object symbols;			/* table of all symbols created */
    struct objectStruct objectTable[ObjectTableMax];
    object memoryBlock[MemoryBlockSize* sizeof(object)];
    int currentMemoryPosition = 0;
#endif

object objectFreeList[FREELISTMAX];