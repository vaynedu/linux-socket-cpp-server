ROOTPATH  = $(shell pwd)
SRC       = $(ROOTPATH)/src
HEAD      = $(ROOTPATH)/head
LIB       = $(ROOTPATH)/lib
BIN       = $(ROOTPATH)/bin

all:
	@cd $(ROOTPATH) && g++ Socket.cpp FileOperator.cpp ClientSocket.cpp ChatClient.cpp -o ChatClient -lpthread -g
#	@mv $(SRC)/ChatClient $(BIN)
	@cd $(ROOTPATH) && g++ Socket.cpp FileOperator.cpp ChatServer.cpp ServerSocket.cpp  -o ChatServer -g
#	@mv $(SRC)/ChatServer $(BIN)
	@echo "compile complet.........."

.PHONY:clean
clean:
	@rm -fr $(BIN)/ChatClient ChatServer
