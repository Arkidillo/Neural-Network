CC = g++
CFLAGS = -g -Wall -O

TARGET = net

all: $(TARGET)

$(TARGET): $(TARGET).cpp $(TARGET).h
	$(CC) $(CFLAGS) net.cpp -o $(TARGET)
	./net

clean:
	$(RM) *~ $(TARGET)
