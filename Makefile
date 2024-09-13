TARGET=main
LD=gcc
SRC=main.c speciesRoutines.c funcoesFornecidas.c funcionalities.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(LD) -o $(TARGET) $(SRC) -g -Wall -Wextra

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
