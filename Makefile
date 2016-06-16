SRCDIR = src
DASHDIR = dash
CFLAGS =  -Wall --std=c11 -O3 -ftrapv
RM = rm -f
OUT = arcs-dash
CC = gcc

all:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) "CFLAGS=$(CFLAGS)" "RM=$(RM)" "OUT=$(OUT)" "CC=$(CC)" 
	@echo "Done"

.PHONY: clean
clean:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) clean
	$(RM) $(OUT)
	@echo "Done"