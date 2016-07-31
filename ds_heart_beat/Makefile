ROOTPATH  = $(shell pwd)
SRC       = $(ROOTPATH)/src
HEAD      = $(ROOTPATH)/head
LIB       = $(ROOTPATH)/lib
BIN       = $(ROOTPATH)/bin

all:
	@cd $(ROOTPATH) && gcc ds_socket.c client.c -o client -lpthread -g
#	@mv $(SRC)/ChatClient $(BIN)
	@cd $(ROOTPATH) && gcc ds_socket.c server.c -o server -lpthread -g
#	@mv $(SRC)/ChatServer $(BIN)
	@echo "compile complet.........."

.PHONY:clean
clean:
	@rm -fr $(BIN)/ChatClient ChatServer
