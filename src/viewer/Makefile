OBJS = main.o comms.o
LIBS = -l glfw -l GLEW -l GL -lpthread
CC = g++

%.o : %.cpp
	@echo "[VIEWER] [CPP] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS) $(OUT)

$(OUT):
	@echo "[VIEWER] [CPP] $(OUT)"
	@$(CC) $(OBJS) $(LIBS) -o $(OUT) 

clean:
	@echo "[VIEWER] [RM] *.o"
	@rm -f *.o
	@echo "[VIEWER] [RM] $(OUT)"
	@rm -f $(OUT)
