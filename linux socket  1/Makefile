ROOT = $(shell pwd)
SRC  = $(ROOT)/src
HEAD = $(ROOT)/head
LIB  = $(ROOT)/lib
BIN  = $(ROOT)/bin

all:
	@cd $(SRC) && g++ Socket.cpp ClientSocket.cpp ChatClient.cpp -o ChatClient -I$(HEAD)
	@mv $(SRC)/ChatClient $(BIN)
	@echo "compile complete ChatClient"
	@cd $(SRC) && g++ Socket.cpp ServerSocket.cpp ChatServer.cpp -o ChatServer -I$(HEAD)
	@mv $(SRC)/ChatServer $(BIN)
	@echo "compile complete ChatServer"

.PHONY:clean
clean:
	@rm -fr $(BIN)/Chat*
	@echo "delete sucess"
