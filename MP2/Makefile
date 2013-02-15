ICCDIR = /home/icc/opt/intel/bin#location of icc on my localmachine

CC = icc#$(ICCDIR)/icc
CCOPTS = -c -g -O3
LINKOPTS = -g 

all: vecstencil

vecstencil: vecstencil.o 
	$(CC) $(LINKOPTS) -o $@ $^

vecstencil.o: vecstencil.c
	$(CC) $(CCOPTS) -o $@ vecstencil.c
	
clean:
	rm -rf *.o vecstencil a.out a.out~ ginsbur3_arrays ginsbur3_times
