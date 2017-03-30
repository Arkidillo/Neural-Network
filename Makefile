CC = g++
CFLAGS = -g -Wall

TARGET = net

#OBJS = node.o net.o

all: $(TARGET)

$(TARGET): net.cpp
	$(CC) $(CFLAGS) net.cpp -o $(TARGET)

#node.o:	node.cpp node.h
#	$(CC) $(CFLAGS) -c node.cpp

#net.o:	net.cpp net.h
#	$(CC) $(CFLAGS) -c net.cpp

clean:
	$(RM) *~ $(TARGET)
