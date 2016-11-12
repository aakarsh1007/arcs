SRC_DIR = src

DASH_DIR = dash
DASH_OUT = arcs-dash
DASH_CFLAGS = -Wall --std=c11 -O3

REMOTE_DIR = remote
REMOTE_OUT = arcs
REMOTE_CFLAGS = -Wall --std=c11 -O3
REMOTE_USER = pi
REMOTE_IP = 192.168.1.44
REMOTE_ARCS_DIR = /var/arcs

VIEWER_DIR = viewer
VIEWER_OUT = arcs-view
VIEWER_CFLAGS = -O3 -std=gnu++0x

all: dash viewer remote

clean: dash-clean viewer-clean remote-clean

dash:
	@echo "[MAKE] dash"
	@$(MAKE) --no-print-directory -C $(SRC_DIR)/$(DASH_DIR) "CFLAGS=$(DASH_CFLAGS)" "OUT=$(DASH_OUT)"
	@echo "[DASH] [LN] $(DASH_OUT)"
	@ln -s $(SRC_DIR)/$(DASH_DIR)/$(DASH_OUT) $(DASH_OUT)

viewer:
	@echo "[MAKE] viewer"
	@$(MAKE) --no-print-directory -C $(SRC_DIR)/$(VIEWER_DIR) "CFLAGS=$(VIEWER_CFLAGS)" "OUT=$(VIEWER_OUT)"
	@echo "[DASH] [LN] $(VIEWER_OUT)"
	@ln -s $(SRC_DIR)/$(VIEWER_DIR)/$(VIEWER_OUT) $(VIEWER_OUT)

remote:
	@echo "[MAKE] remote"
	@echo "[REMOTE] [SCP] $(SRC_DIR)/$(REMOTE_DIR)/*"
	@scp -r $(SRC_DIR)/$(REMOTE_DIR)/* $(REMOTE_USER)@$(REMOTE_IP):$(REMOTE_ARCS_DIR)/
	@echo "[REMOTE] [MAKE] remote"
	@ssh $(REMOTE_USER)@$(REMOTE_IP) "$(MAKE) --no-print-directory -C $(REMOTE_ARCS_DIR) \"CFLAGS=$(REMOTE_CFLAGS)\" \"OUT=$(REMOTE_OUT)\""
	@echo "[REMOTE] Restart Daemon"
	@ssh root@$(REMOTE_IP) "systemctl restart arcs"

dash-clean:
	@echo "[MAKE] dash-clean"
	@$(MAKE) --no-print-directory -C $(SRC_DIR)/$(DASH_DIR) clean "OUT=$(DASH_OUT)"
	@echo "[DASH] [RM] $(DASH_OUT)"
	@rm -f $(DASH_OUT)

viewer-clean:
	@echo "[MAKE] viewer-clean"
	@$(MAKE) --no-print-directory -C $(SRC_DIR)/$(VIEWER_DIR) clean "OUT=$(VIEWER_OUT)"
	@echo "[VIEWER] [RM] $(VIEWER_OUT)"
	@rm -f $(VIEWER_OUT)

remote-clean:
	@echo "[SSH] $(REMOTE_USER)@$(REMOTE_IP)"
	@ssh $(REMOTE_USER)@$(REMOTE_IP) "rm -rf $(REMOTE_ARCS_DIR)/*; exit"

format:
	@echo "[FORMAT] *.h"
	@find . -type f -name '*.h' -exec clang-format -i {} \;
	@echo "[FORMAT] *.c"
	@find . -type f -name '*.c' -exec clang-format -i {} \;
	@echo "[FORMAT] *.cpp"
	@find . -type f -name '*.cpp' -exec clang-format -i {} \;
	@echo "[FORMAT] *.hpp"
	@find . -type f -name '*.hpp' -exec clang-format -i {} \;
