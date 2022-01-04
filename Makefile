build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -lm -o rendeder

run:
	./rendeder

clean:
	rm rendeder