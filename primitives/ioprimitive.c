#include "ioprimitive.h"

/* i/o primitives 
basically, files are all kept in a large array.
File operations then just give an index into this array 
IO primitives are 120-139
 we assume this is initialized to NULL */
static FILE *fp[MAXFILES]= {0};
#ifndef IMG_BUILD
object edit(char* buff, int size)
{
	object returnedObject;
	initEditor();
	editorInput(buff, size);
	int len;
	editorSetStatusMessage(
		"HELP: Ctrl-C = commit | Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");
	while(edStatus() == ED_ON) {
		editorRefreshScreen();
		editorProcessKeypress(STDIN_FILENO);
	}
	//print content
	buff = editorRowsToString(&len);
	edFreeBuffer();
	returnedObject = newStString(buff);
	free(buff);
	return returnedObject;
}
#endif
/*120 - 129*/
object filePrimitive(int number, object* arguments)
{
    int i, j;
    char *p, buffer[1024];
    object returnedObject;
    returnedObject = nilobj;
	i = intValue(arguments[0])-1;
	if(i == 0 && !fp[i]) fp[i] = stdin;
	if(i == 1 && !fp[i]) fp[i] = stdout;
    switch (number) {
	    case 0:			/* file open */
		if(i < 2) return newInteger(i);
		p = charPtr(arguments[1]);
		fp[i] = fopen(p, charPtr(arguments[2]));
		if (fp[i] == NULL)
		    returnedObject = nilobj;
		else
		    returnedObject = newInteger(i);
		break;

	    case 1:			/* file close - recover slot */
		if (i >= 2 && fp[i])
		{
			ignore fclose(fp[i]);
			fp[i] = NULL;
		}
		break;

	    case 2:			/* stdout no return */
#ifndef IMG_BUILD
		printf("\n");
		fflush(stdout);
		returnedObject = edit(charPtr(arguments[0]), intValue(arguments[1]));
	
#endif
		break;
	
   	 	case 3:			/* read byte array */
		j =  intValue(arguments[1]);
		p = (char*) malloc(j);
		if(p)
		{
			j = fread(p,1, j,fp[i]);
			if(j>0)
			{
				returnedObject = newByteArray(j);
				memcpy(charPtr(returnedObject),p,j);
			}
			free(p);
			p = NULL;
		}
		break;

    	case 4:			/* write byte array */
		j = sizeField(arguments[1]);
		if (j < 0)
			j = (-j);
		returnedObject = newInteger(
			fwrite(charPtr(arguments[1]), 1, j, fp[i]));
		break;

	    case 5:			/* get line */
		if (!fp[i])
		    break;
		j = 0;
		buffer[j] = '\0';
		if(fp[i] == stdin)
		{
#ifndef IMG_BUILD
			tty_readline(buffer,sizeof(buffer),1);
			returnedObject = newStString(buffer);
#endif
		} else if (!fgets(buffer, 1024, fp[i]))
			returnedObject = nilobj;
		else
		{
		    j = strlen(buffer) - 1;
		    buffer[j] = '\0';
			    /* else we loop again */
			returnedObject = newStString(buffer);
		}
		break;
		
		case 6: // file path primitive
#ifndef IMG_BUILD
		//j = intValue(arguments[0]);
		//returnedObject = fp_primitive(j,&arguments[1]);
#endif;
		break;
			
   	 	case 7:			/* write an object image */
		break;

    	case 8:			/* print no return */
    	case 9:			/* print string */
		if (!fp[i])
	   	 	break;
#ifndef IMG_BUILD		
		if(fp[i] == stdout)
			//setvbuf(stdout, NULL, _IONBF, 0);
			printf(charPtr(arguments[1]));
		else
#endif
			ignore fputs(charPtr(arguments[1]), fp[i]);
			//setvbuf(stdout, NULL, _IOLBF, 0);
		//serial_write(charPtr(arguments[1]),strlen(charPtr(arguments[1])));
		if (number == 9) {
			ignore fputs("\n", fp[i]);
		}
		fflush(fp[i]);
		break;
	
		default:break;
	}
	return returnedObject;
}

object ioPrimitive(int number, object * arguments)
{
    object returnedObject;
    returnedObject = nilobj;
	if(number <= 9)
		return filePrimitive(number, arguments);
}

