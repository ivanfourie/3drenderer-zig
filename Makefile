# Build settings
CC-BUILD=gcc
CC-RUN=tcc
CFLAGS=-Wall -std=c99
LDFLAGS=-lm
SDL_FLAGS=`pkg-config --cflags --libs sdl2`

# Directories
S_DIR=src

# Output
EXEC=renderer

# Shared flags
FLAGS=$(CFLAGS) $(S_DIR)/*.c $(SDL_FLAGS) $(LDFLAGS)

# Compile executable
build:
	@echo "Compile '$(EXEC)'"
	$(CC-BUILD) $(FLAGS) -o $(EXEC)

# Compile executable with optimisations
release:
	@echo "Compile '($EXEC)' with optimisations"
	$(CC-BUILD) -O3 -DNDEBUG $(FLAGS) -o $(EXEC)

# Execute the binary
run:
	@echo "Execute '$(EXEC)'"
	./$(EXEC)

# Compile and execute directly in memory
mem:
	@echo "Compile and execute directly in memory"
	$(CC-RUN) $(FLAGS) -run

clean:
	@echo "Remove '$(EXEC)'"
	rm -rf $(EXEC)