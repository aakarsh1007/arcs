all: joystick.out

.PHONY: clean
clean:
	rm -f *.out

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $<
