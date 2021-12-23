build:
	mkdir bin
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o ./bin/rendeder

run:
	./bin/rendeder

clean:
	rm -rf bin