CC=gcc
STD=c23
CODEDIRS=src
INCDIRS=include
OP=-O0
FLAGS=-Wall -g $(foreach D, $(INCDIRS), -I$D)
LDLIBS = -lraylib -lGL -lX11 -lXrandr -lXinerama -lXi -lXcursor -lm -lpthread -ldl -lrt 
FILES=$(foreach D, $(CODEDIRS), $(wildcard $D/*.c))
BINARY=bin
OBJ=$(patsubst %.c,%.o,$(FILES))

all: $(BINARY)

run: all
	./bin
debug: all
	gdb ./bin

$(BINARY): $(OBJ)
	$(CC) $^ -o $@ $(LDLIBS)
%.o: %.c
	$(CC) -std=$(STD) -c $(FLAGS) $(OP) -o $@ $^
clean:
	rm -r $(OBJ) $(BINARY)
