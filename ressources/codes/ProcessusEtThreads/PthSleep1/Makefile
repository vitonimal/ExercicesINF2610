CC=cc
CFLAGS=`pth-config --cflags`
LDFLAGS=`pth-config --ldflags`
LIBS=`pth-config --libs`

all: a.out
a.out: thread_proc31.o
	$(CC) $(LDFLAGS) -o a.out thread_proc31.o $(LIBS)
thread_proc31.o: thread_proc31.c
	$(CC) $(CFLAGS) -c thread_proc31.c