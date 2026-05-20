CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99
TARGET  = mydf
SRC     = mydf.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

re: clean all

.PHONY: all clean re
