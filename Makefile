SRCDIR = src
DASHDIR = dash
REMOTEDIR = remote
VIEWERDIR = viewer
CFLAGS =  -Wall --std=c11 -O3 -ftrapv
CPP_FLAGS = -O3
RM = rm -f
OUT = arcs-dash
VIEW_OUT = arcs-view
CC = gcc
TESTDIR = tests

REMOTE_USER = pi
REMOTE_IP = 192.168.1.44
REMOTE_DIR = /var/arcs
REMOTE_CFLAGS = -Wall -std=c11 -O3 -ftrapv
REMOTE_CC = gcc

.PHONY: all
all: dash-all viewer-all remote-all
	@echo "Done all"

.PHONY: clean
clean: dash-clean remote-clean
	@echo "Done clean"

.PHONY: dash-all
dash-all:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) "CFLAGS=$(CFLAGS)" "RM=$(RM)" "OUT=$(OUT)" "CC=$(CC)" 
	@echo "Done dash-all"

.PHONY: clean
dash-clean:
	$(MAKE) -C $(SRCDIR)/$(DASHDIR) clean
	$(RM) $(OUT)
	@echo "Done dash-clean"

.PHONY: viewer-all
viewer-all:
	$(MAKE) -C $(SRCDIR)/$(VIEWERDIR) "CFLAGS=$(CPP_FLAGS)" "OUT=$(VIEW_OUT)"
	@echo "Done viwer-all"

.PHONY: viewer-clean
viewer-clean:
	$(MAKE) -C $(SRCDIR)/$(VIEWERDIR) clean
	@echo "Done viewer-clean"

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


.PHONY: tests
tests:
	$(MAKE) -C $(TESTDIR)

.PHONY: tests-clean
tests-clean:
	$(MAKE) -C $(TESTDIR) clean

.PHONY: format
format:
	find . -type f -name '*.h' -exec clang-format -i {} \;
	find . -type f -name '*.cpp' -exec clang-format -i {} \;
	find . -type f -name '*.c' -exec clang-format -i {} \;
