OBJS = main.o screen.o io.o interface.o js.o args.o keyboard.o remote.o comms.o
LIBS = -lncurses -lpthread -lslog

%.o : %.c
	@echo "[DASH] [CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS) $(OUT)

$(OUT):
	@echo "[DASH] [CC] $(OUT)"
	@$(CC) $(OBJS) $(LIBS) -o $(OUT) 

clean:
	@echo "[DASH] [RM] *.o"
	@rm -f *.o
	@echo "[DASH] [RM] $(OUT)"
	@rm -f $(OUT)
