ICCDIR = /home/icc/opt/intel/bin

CC = $(ICCDIR)/icc
CCOPTS = -c -g -O3
LINKOPTS = -g 

all: vecstencil gen

vecstencil: vecstencil.o 
	$(CC) $(LINKOPTS) -o $@ $^

vecstencil.o: vecstencil.c
	$(CC) $(CCOPTS) -o $@ vecstencil.c
	
clean:
	rm -rf *.o vecstencil a.out a.out~ ginsbur3_arrays ginsbur3_times
