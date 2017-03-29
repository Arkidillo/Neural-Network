CC = g++
CFLAGS = -g -Wall

TARGET = net

OBJS = node.o net.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

node.o:	node.cpp node.h
	$(CC) $(CFLAGS) -c node.cpp

net.o:	net.cpp net.h
	$(CC) $(CFLAGS) -c net.cpp

clean:
	$(RM) *.o *~ $(TARGET)
