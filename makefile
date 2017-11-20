all:
	gcc -o exec *.c

run: all
	./exec

clean:
	rm exec
	clear
	rm *~
	clear

cleanall:
	rm exec
	rm a.out
	rm *~
	clear
