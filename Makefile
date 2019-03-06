BUILD_DIR=./build

PRIV_S = primitives/primitive.c \
		primitives/ioprimitive.c

VM_SRC = gdef.c\
		interp.c\
		io.c\
		memory.c\
		imgtools/lex.c\
		imgtools/parser.c\
		names.c\
		news.c\
		$(PRIV_S)
		
UTILS = utils/tty.c \
		utils/kilo.c
		
SRC =	iotvm.c\
		$(UTILS) \
		$(VM_SRC) 
OBJS = $(SRC:%=%.o)
PRJ_NAME = iotvm
LIB = -lm
CFLAGS=-W -Wall -g -std=c99 -D DEBUG
system: vmimage all
vmimage:
	make clean
	cd imgtools/ && make clean && make

all : ${OBJS}
	gcc $(CFLAGS) $(OBJS)  -o $(BUILD_DIR)/${PRJ_NAME} $(LIB)

%.c.o:%.c
	gcc $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	rm -f $(BUILD_DIR)/${PRJ_NAME}
	rm -f $(BUILD_DIR)/*.img




