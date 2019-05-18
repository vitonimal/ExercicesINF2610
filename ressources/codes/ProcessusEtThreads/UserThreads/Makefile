CC=cc
CFLAGS=`pth-config --cflags`
LDFLAGS=`pth-config --ldflags`
LIBS=`pth-config --libs`

all: a.out
a.out: uthreads.o
	$(CC) $(LDFLAGS) -o a.out uthreads.o $(LIBS)
uthreads.o: uthreads.c
	$(CC) $(CFLAGS) -c uthreads.c