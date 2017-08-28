CC=gcc
PROJECT_NAME=drcom-kai
BUILD_DIR=build
INCLUDE_DIR=include
SRC_DIR=src
SRC_NAME=$(SRC_DIR)/main.c
FLOW_SRC=$(SRC_DIR)/flow.c
SOCKET_SRC=$(SRC_DIR)/socket.c
PACKAGE_SRC=$(SRC_DIR)/package.c
UTILS_SRC=$(SRC_DIR)/utils.c
MD5_SRC=$(SRC_DIR)/md5.c
CFLAGS=-g
all: flow.o
	$(CC) $(CFLAGS) $(SRC_NAME) $(BUILD_DIR)/flow.o $(BUILD_DIR)/socket.o $(BUILD_DIR)/package.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/md5.o -o $(BUILD_DIR)/$(PROJECT_NAME) -I$(INCLUDE_DIR)
flow.o: socket.o package.o
	$(CC) $(CFLAGS) -c $(FLOW_SRC) -o $(BUILD_DIR)/flow.o -I$(INCLUDE_DIR)
socket.o:
	$(CC) $(CFLAGS) -c $(SOCKET_SRC) -o $(BUILD_DIR)/socket.o -I$(INCLUDE_DIR)
package.o: utils.o md5.o
	$(CC) $(CFLAGS) -c $(PACKAGE_SRC) -o $(BUILD_DIR)/package.o -I$(INCLUDE_DIR)
utils.o:
	$(CC) $(CFLAGS) -c $(UTILS_SRC) -o $(BUILD_DIR)/utils.o -I$(INCLUDE_DIR)
md5.o:
	$(CC) $(CFLAGS) -c $(MD5_SRC) -o $(BUILD_DIR)/md5.o -I$(INCLUDE_DIR)