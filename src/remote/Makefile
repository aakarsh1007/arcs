OBJS=main.o comms.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lslog -lpthread -o arcs

.PHONY: clean
clean:
	rm -f *.o
	rm -f arcs
