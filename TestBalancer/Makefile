COMPILER=g++
LINKER=g++

OS_TYPE=$(shell uname)

ifndef LINUX
  ifeq ($(OS_TYPE),Linux)
    LINUX=yes
  endif
endif

ifdef LINUX
LIBS=-lpthread -lz -lmysqlclient  -lxmlwrapp -lxml2
LIBDIRS=-L/usr/lib -L/usr/lib/mysql 
INCLUDEDIRS=-I/usr/include/mysql -I../libs -I./ -I../
CPPFLAGS=-DLINUX -D_XOPEN_SOURCE=600 -D_BSD_SOURCE=1 -D_GNU_SOURCE=1 -D_THREAD_SAFE=1 -std=c++0x
make=make
endif

PROG_NAME=testbalancer

VERSION=0.0.1
LD=../libs

OP=-g
CC=$(COMPILER) $(INCLUDEDIRS) -MD -fexceptions $(OP) -Wall -DUSE_NFS -D_PTHREADS -D_REENTRANT -D_DEBUG -m32

LINK=$(LINKER)
LOBJ=$(LD)/icharset.o $(LD)/chars.o $(LD)/socket.o $(LD)/log.o $(LD)/storage.o $(LD)/string.o $(LD)/mutexsync.o $(LD)/tools.o $(LD)/mysql.o $(LD)/thread.o  $(LD)/ips.o $(LD)/time.o $(LD)/dir.o $(LD)/limit.o $(LD)/eventpoller.o $(LD)/dfile.o

#OBJS=balancethread.o server.o node.o timethread.o ctrlthread.o eventthread.o appserver.o events.o socketbuffer.o $(LOBJ)
OBJS= threadman.o WebThreadManager.o WebThread.o BinProtocol.o WorkingSession.o WorkingServerApi.o WorkingThreadManager.o WorkingThread.o Server.o  $(LOBJ)



PROGRAMS=$(BIN_PROGRAMS) $(TEST_PROGRAMS)


all: $(OBJS) balancer calculationserver
	#$(LINKER) $(OP) -o $(PROG_NAME) balancer.o calculationserver.o $(OBJS) $(LIBDIRS) $(LIBS) -m32

balancer: $(OBJS) balancer.o
	$(LINKER) $(OP) -o $(PROG_NAME) balancer.o  $(OBJS) $(LIBDIRS) $(LIBS) -m32
calculationserver: $(OBJS) calculationserver.o
	$(LINKER) $(OP) -o calculationserver calculationserver.o $(OBJS) $(LIBDIRS) $(LIBS) -m32
%.o: %.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS) $(LOGFLAGS)
	
include $(wildcard *.d)

clean::
	rm -f *.o *.d
	rm -f ../libs/*.o ../libs/*.d
update::
	git pull origin master
	cd ../libs;git pull origin master


