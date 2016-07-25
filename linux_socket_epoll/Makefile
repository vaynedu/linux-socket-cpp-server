ROOTPATH  = $(shell pwd)
SRC       = $(ROOTPATH)/src
HEAD      = $(ROOTPATH)/head
LIB       = $(ROOTPATH)/lib
BIN       = $(ROOTPATH)/bin

all:
	@cd $(SRC) && g++ Socket.cpp ClientSocket.cpp ChatClient.cpp -o ChatClient -I$(HEAD)
	@mv $(SRC)/ChatClient $(BIN)
	@cd $(SRC) && g++ Socket.cpp EpollServerSocket.cpp ChatServer.cpp Epoll.cpp -o ChatServer -I$(HEAD)
	@mv $(SRC)/ChatServer $(BIN)
	@echo "compile complet.........."

.PHONY:clean
clean:
	@rm -fr $(BIN)/ChatClient ChatServer
