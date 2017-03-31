CC = g++
CFLAGS = -g -Wall -O

TARGET = net

all: $(TARGET)

$(TARGET): net.cpp
	$(CC) $(CFLAGS) net.cpp -o $(TARGET)
	./net

clean:
	$(RM) *~ $(TARGET)
