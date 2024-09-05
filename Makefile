ROOT_DIR=$(shell pwd)
BUILD=$(ROOT_DIR)/build
INCLUDE_DIR=$(ROOT_DIR)/include
SRC_DIR=$(ROOT_DIR)/src
CC = gcc
CFLAGS = -Wall -O3 
CFLAGS += -I $(INCLUDE_DIR)
all: init build

.PHONY:all

init:
    @$(shell if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi)

build:
    @(MAKE) -C $(SRC_DIR) all

clean:
    @echo "RM	OBJS"
    @-rm -f $(BUILD)
    @-rm -f $(shell find $(BUILD) -name *.o)
