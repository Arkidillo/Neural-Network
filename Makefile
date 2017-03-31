CC = g++
CFLAGS = -g -Wall

TARGET = net

all: $(TARGET)

$(TARGET): net.cpp
	$(CC) $(CFLAGS) net.cpp -o $(TARGET)

clean:
	$(RM) *~ $(TARGET)
