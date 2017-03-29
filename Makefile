CC = g++
CFLAGS = -g -Wall

TARGET = net

all: $(TARGET)

$(TARGET): $(TARGET).cpp $(TARGET).h
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
