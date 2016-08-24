# Autonomous Robot Control System
arcs is a robot control system that focuses on LIDAR usage.


![](https://github.com/dominikWin/arcs/blob/master/img/e484ef039eaf7c2a64accad60c10f8f12efde668.jpg)

## Dependencies

arcs needs [slog](https://github.com/kala13x/slog) and [WiringPi](http://wiringpi.com/) on the controller.
ncurses and slog are needed on the dashboard system.
pthread is also required to compile both.

The makefile uses scp and gcc on the remote machine.

Linux is required on both the dashboard and the remote.

## Build

1.  Set remote IP in Makefile, setup root ssh cert
2.  Run `make all`
3.  Run with `./arcs-dash`

## Running

arcs dashboard should be run from a terminal that supports ncurses.
The only supported controllers are from the linux [xpad driver](https://github.com/torvalds/linux/blob/master/drivers/input/joystick/xpad.c).
Networking is enabled by pressing r, and quit with q or the guide button.
