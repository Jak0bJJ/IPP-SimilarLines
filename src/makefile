CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = similar_lines
.PHONY: all clean
all: $(TARGET)

$(TARGET): basics.o check_type.o stand.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) basics.c check_type.c stand.c main.c

basics.o: basics.c basics.h
	$(CC) $(CFLAGS) -c basics.c

check_type.o: check_type.c check_type.h basics.h
	$(CC) $(CFLAGS) -c check_type.c

stand.o: stand.c stand.h check_type.h basics.h
	$(CC) $(CFLAGS) -c stand.c

similar_lines.o: main.c stand.h check_type.h basics.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(TARGET) *.o