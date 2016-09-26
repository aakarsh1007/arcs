OBJS=main.o comms.o drivetrain.o teleop.o disabled.o command_manager.o tank.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lslog -lpthread -lwiringPi -o arcs

.PHONY: clean
clean:
	rm -f *.o
	rm -f arcs
