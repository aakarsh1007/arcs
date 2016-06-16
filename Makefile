SRCDIR = src
DASHDIR = dash
CFLAGS =  -Wall --std=c11 -O3 -ftrapv
RM = rm -f
OUT = arcs-dash
CC = gcc

REMOTE_USER = pi
REMOTE_IP = 192.168.1.44
REMOTE_DIR = /var/arcs
REMOTE_CFLAGS = -Wall -std=c11 -O3 -ftrapv
REMOTE_CC = gcc

all: local-all remote-all
clean: local-clean remote-clean

local-all:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) "CFLAGS=$(CFLAGS)" "RM=$(RM)" "OUT=$(OUT)" "CC=$(CC)" 
	@echo "Done"

.PHONY: clean
local-clean:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) clean
	$(RM) $(OUT)
	@echo "Done"

.PHONY: remote-all
remote-all:
	$(MAKE) remote-clean
	scp -r src/remote/* $(REMOTE_USER)@$(REMOTE_IP):$(REMOTE_DIR)/
	ssh $(REMOTE_USER)@$(REMOTE_IP) "$(MAKE) -C $(REMOTE_DIR) \"CFLAGS=$(REMOTE_CFLAGS)\" \"CC=$(REMOTE_CC)\"; exit"

.PHONY: remote-clean
remote-clean:
	ssh $(REMOTE_USER)@$(REMOTE_IP) "rm -rf $(REMOTE_DIR)/*; exit"
