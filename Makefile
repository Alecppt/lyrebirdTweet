##(1) student's name:     Alec Chen
##(2) student ID:         301187669
##(3) SFU user name:      cca169
##(4) lecture section:    CMPT 300 D1 (Fall 2015)
##(5) instructor's name:  Brian Booth
##(6) TA's name:          Scott Kristjanson

#stack.o decrypt.o lyrebird.client -Wall -Werror

.SUFFIXES: .h .o .c

CCFLAGS= -g -DMEMWATCH -DMW_STDIO
CC = gcc
LIBS = -lm
# CCEXEC = lyrebird.server lyrebird.client
SERVEROBJCS = serverMain.o helper.o network.o
CLIENTOBJCS = clientMain.o helper.o

all: lyrebird.server lyrebird.client

lyrebird.server: $(SERVEROBJCS)
	@echo Linking $@ . . .
	$(CC) $(CCFLAGS) $(SERVEROBJCS) -o $@ $(LIBS)

lyrebird.client: $(CLIENTOBJCS)
	@echo Linking $@ . . .
	$(CC) $(CCFLAGS) $(CLIENTOBJCS) -o $@ $(LIBS)

%.o: %.c
	@echo Compiling $< . . .
	$(CC) -c $(CCFLAGS) $<

clean:
	rm -f core $(SERVEROBJCS) $(CLIENTOBJCS) lyrebird.server lyrebird.client emwatch.log decrypt.o stack.o
