CC = g++
CFLAGS = -g -Wall -O2

TARGET = net

all: $(TARGET)

OBJS = net.o synapseIO.o caesarTrainer.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	./net

synapseIO: synapseIO.cpp synapseIO.h
	$(CC) $(CFLAGS) -c synapseIO.cpp

caesarTrainer: caesarTrainer.cpp caesarTrainer.h
	$(CC) $(CFLAGS) -c caesarTrainer.cpp


clean:
	$(RM) *~ $(TARGET)
