CC=cc
CFLAGS=`pth-config --cflags`
LDFLAGS=`pth-config --ldflags`
LIBS=`pth-config --libs`

all: a.out
a.out: thread_proc32.o
	$(CC) $(LDFLAGS) -o a.out thread_proc32.o $(LIBS)
thread_proc32.o: thread_proc32.c
	$(CC) $(CFLAGS) -c thread_proc32.c