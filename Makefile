
all: base64.o smtp.o demo.o
	gcc -g base64.o smtp.o demo.o -o smtp

base64.o:base64.c base64.h
	gcc -c -g base64.c	
smtp.o:smtp.c smtp.h
	gcc -c -g smtp.c
demo.o:demo.c
	gcc -c -g demo.c

clean:
	rm *.o -rf
	rm smtp -rf

test:clean all
	./smtp smtp.163.com 