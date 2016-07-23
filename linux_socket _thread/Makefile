ROOT  = $(shell pwd)
SRC   = $(ROOT)/src
HEAD  = $(ROOT)/head
BIN   = $(ROOT)/bin
LIB   = $(ROOT)/lib


all:
	@cd $(SRC) && g++ Socket.cpp ClientSocket.cpp ChatClient.cpp -o ChatClient  -I$(HEAD)   -lpthread
	@mv $(SRC)/ChatClient $(BIN)
	@cd $(SRC) && g++ Socket.cpp ServerSocket.cpp ChatServer.cpp ThreadReadWriteLock.cpp -o ChatServer -I$(HEAD)  -lpthread
	@mv $(SRC)/ChatServer $(BIN)
	@echo "compile compilelete......"

.PHONT:clean
clean:
	@rm -fr $(BIN)/ChatClient $(BIN)/ChatServer
	@echo "make clean sucess"
