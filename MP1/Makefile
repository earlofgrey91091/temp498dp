CC = gcc
CCOPTS = -c -g -O3
LINKOPTS = -g 

all: ccradix gen

ccradix: ccradix.o 
	$(CC) $(LINKOPTS) -o $@ $^

ccradix.o: ccradix.c
	$(CC) $(CCOPTS) -o $@ ccradix.c
	
gen: gen.o 
	$(CC) $(LINKOPTS) -o $@ $^

gen.o: gen.c
	$(CC) $(CCOPTS) -o $@ gen.c
	
clean:
	rm -rf *.o ccradix gen a.out b.out a.out~ b.out~ sorted.txt 
	
cleangen:
	rm -rf *.o ccradix gen a.out b.out numbers.txt a.out~ b.out~ numbers.txt~
