all: joystick.out lidar.out

.PHONY: clean
clean:
	rm -f *.out

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $<
