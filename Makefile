SRCDIR = src
DASHDIR = dash
REMOTEDIR = remote
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
	@echo "Done all"

clean: local-clean remote-clean
	@echo "Done clean"

local-all:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) "CFLAGS=$(CFLAGS)" "RM=$(RM)" "OUT=$(OUT)" "CC=$(CC)" 
	@echo "Done local-all"

.PHONY: clean
local-clean:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) clean
	$(RM) $(OUT)
	@echo "Done local-clean"

.PHONY: remote-all
remote-all:
	$(MAKE) remote-clean
	scp -r $(SRCDIR)/$(REMOTEDIR)/* $(REMOTE_USER)@$(REMOTE_IP):$(REMOTE_DIR)/
	ssh $(REMOTE_USER)@$(REMOTE_IP) "$(MAKE) -C $(REMOTE_DIR) \"CFLAGS=$(REMOTE_CFLAGS)\" \"CC=$(REMOTE_CC)\"; exit"
	@echo "Done remote-all"

.PHONY: remote-clean
remote-clean:
	ssh $(REMOTE_USER)@$(REMOTE_IP) "rm -rf $(REMOTE_DIR)/*; exit"
	@echo "Done remote-clean"
