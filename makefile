GCC = gcc -g

project: final.c
	$(GCC) final.c -o project

run: project
	./project

clean:
	rm project
	rm *~
