PLATFORM_TARGET=x64
CONFIGURATION=Debug
PROJECT_BASE_PATH=C:/hhw/project/private/kaphein-core

PROJECT_CONFIGURATION_NAME=kaphein-core

CC=gcc
CFLAGS=-g -Wall -DKAPHEIN_COMPOPT_DLL_API_MODE=1 -I$(INCLUDE_PATH)

INCLUDE_PATH=$(PROJECT_BASE_PATH)/include
SRC_PATH=$(PROJECT_BASE_PATH)/src
OBJ_PATH=$(PROJECT_BASE_PATH)/obj/$(CC)/$(PROJECT_CONFIGURATION_NAME)/$(PLATFORM_TARGET)/$(CONFIGURATION)/src
BIN_PATH=$(PROJECT_BASE_PATH)/bin/$(CC)/$(PROJECT_CONFIGURATION_NAME)/$(PLATFORM_TARGET)/$(CONFIGURATION)

OBJ_SUB_DIRECTORY_PATHS= \
	$(OBJ_PATH)/kaphein \
	$(OBJ_PATH)/kaphein/coll \
	$(OBJ_PATH)/kaphein/geom3d \
	$(OBJ_PATH)/kaphein/io \
	$(OBJ_PATH)/kaphein/math \
	$(OBJ_PATH)/kaphein/mem \
	$(OBJ_PATH)/kaphein/ppgen \
	$(OBJ_PATH)/kaphein/text \
	$(OBJ_PATH)/kaphein/thrd

default: build

byteOrder.o: byteOrder.c $(INCLUDE_PATH)
	echo $<
	echo $@

build:
	mkdir -p $(BIN_PATH)
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_SUB_DIRECTORY_PATHS)
	$(CC) $(CFLAGS) -o foo byteOrder.o

clean:
	rm -rf $(BIN_PATH)/*.*
	rm -rf $(OBJ_PATH)/*.*
	rm -rf $(OBJ_PATH)/*.*
  
