.PHONY: clean

CFLAGS := -Wall -Wextra -std=c99 -pedantic -Iinclude

CFILES := $(shell find src -type f -name '*.c')
OFILES := $(CFILES:.c=.o)
BIN := 4th

$(BIN): $(OFILES)
	gcc $(OFILES) $(LDFLAGS) -o $(BIN)

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OFILES) $(BIN)