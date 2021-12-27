build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o rendeder

run:
	./rendeder

clean:
	rm rendeder