build:
	gcc -Wall -std=c99 ./src/*.c -o rendeder

run:
	./rendeder

clean:
	rm rendeder