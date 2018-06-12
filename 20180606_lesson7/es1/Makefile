CC=gcc
LDFLAGS=-pthread
OBJECTS=exCreazioneThread.o
TARGET=exCreazioneThread

all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean: ; rm -rf $(OBJECTS) $(TARGET)
