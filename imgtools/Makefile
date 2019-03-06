CC=gcc
UNAME_S := $(shell uname -s)
ADV_INPUT := True
PF_FLAG=-D_GNU_SOURCE -DIMG_BUILD
BUILDIRD= ../build
VMLIBS = -lm

SYS_PRIV =
VMDEP = ../memory.o \
		../names.o \
		../news.o \
		../interp.o \
		../primitives/primitive.o \
		../primitives/ioprimitive.o \
		../io.o \
		../gdef.o \
		#$(SYS_PRIV) 
IMG_BUILD_DEP = fileio.o \
				lex.o \
				parser.o
			
ST_BOOTSTRAP =  basic.st \
				Block.st \
				Context.st \
				Process.st \
				Smalltalk.st \
				UndefinedObject.st \
				mag.st \
				Boolean.st \
				Method.st \
				collect.st \
				Class.st \
				Object.st \
				Symbol.st \
				Scheduler.st \
				../optional/GPIO.st\
				../optional/File.st\
				../optional/nativeparser.st

#../optional/parser.st\
../optional/Serial.st\				
CFLAGS=-W -Wall -g -std=c99 -D DEBUG  $(PF_FLAG)
main:  $(VMDEP) $(IMG_BUILD_DEP) buildimage im2h
	./im2h $(BUILDIRD)/image.im > ../image.h

%.o: %.c
		$(CC) $(CFLAGS) -I$(PLUGINS_BASE) -I$(STROS_BASE) -c $< -o $@
clean:
		-rm -f *.o ../*.o *.o  $(BUILDIRD)/image.im

im2h: $(VMDEP) $(IMG_BUILD_DEP) im2h.o
	$(CC) $(CFLAGS) $(VMDEP) $(IMG_BUILD_DEP) im2h.o -o im2h $(VMLIBS)

.PRECIOUS: %.o

buildimage: initial.o
	-mkdir $(BUILDIRD)
	$(CC) $(CFLAGS) $(VMDEP) $(IMG_BUILD_DEP) initial.o -o build_image $(VMLIBS)
	@cd bootstrap && ../build_image $(ST_BOOTSTRAP)
	@mv bootstrap/systemImage $(BUILDIRD)/image.im
	