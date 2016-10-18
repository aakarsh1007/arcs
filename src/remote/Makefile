OBJS = main.o comms.o drivetrain.o teleop.o disabled.o command_manager.o tank.o timing.o
LIBS = -lncurses -lpthread -lslog

%.o : %.c
	@echo "[REMOTE] [CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS) $(OUT)

$(OUT):
	@echo "[REMOTE] [CC] $(OUT)"
	@$(CC) $(OBJS) $(LIBS) -o $(OUT) 

clean:
	@echo "[REMOTE] [RM] *.o"
	@rm -f *.o
	@echo "[REMOTE] [RM] $(OUT)"
	@rm -f $(OUT)
