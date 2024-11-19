start:
	make build run

run:
	./main

build:
	bear -- gcc -std=c11 -omain -Iinclude src/*.c 
