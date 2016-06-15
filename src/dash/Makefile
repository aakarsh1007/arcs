OBJS = main.o screen.o io.o interface.o

all: common.h $(OBJS)
	gcc $(CFLAGS) $(OBJS) -lncurses -o ../../$(OUT)

main.o: main.c screen.h
screen.o: screen.c screen.h

.PHONY: clean
clean:
	$(RM) *.o