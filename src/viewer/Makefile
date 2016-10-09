OBJS = main.o
CC=g++

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -l glfw -l GLEW -l GL -o ../../$(OUT)

.PHONY: clean
clean:
	$(RM) *.o
