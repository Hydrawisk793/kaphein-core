OS_NAME=win
OS_ARCH=x64
CONFIGURATION=Debug
PROJECT_BASE_PATH=C:/hhw/project/private/kaphein-core
PROJECT_NAME=kaphein-core
CC=gcc
AR=ar

BUILD_TARGETS= \
	kaphein/byteOrder \
	kaphein/ErrorCode \
	kaphein/internal \
	kaphein/mem/utils \
	kaphein/mem/defAlloc \
	kaphein/mem/SegmentPool \
	kaphein/coll/List \
	kaphein/coll/TreeSet \
	kaphein/coll/RingBuffer \
	kaphein/coll/Vector \
	kaphein/coll/sort 

OBJ_FILE_PATHS= \
	$(OBJ_PATH)/kaphein/byteOrder.o \
	$(OBJ_PATH)/kaphein/ErrorCode.o \
	$(OBJ_PATH)/kaphein/internal.o \
	$(OBJ_PATH)/kaphein/mem/utils.o \
	$(OBJ_PATH)/kaphein/mem/defAlloc.o \
	$(OBJ_PATH)/kaphein/mem/SegmentPool.o \
	$(OBJ_PATH)/kaphein/coll/List.o \
	$(OBJ_PATH)/kaphein/coll/TreeSet.o \
	$(OBJ_PATH)/kaphein/coll/RingBuffer.o \
	$(OBJ_PATH)/kaphein/coll/Vector.o \
	$(OBJ_PATH)/kaphein/coll/sort.o

PLATFORM_TARGET=$(OS_ARCH)
INCLUDE_PATH=$(PROJECT_BASE_PATH)/include
SRC_PATH=$(PROJECT_BASE_PATH)/src
OBJ_PATH=$(PROJECT_BASE_PATH)/obj/$(CC)/$(PROJECT_NAME)/$(PLATFORM_TARGET)/$(CONFIGURATION)/src
BIN_PATH=$(PROJECT_BASE_PATH)/bin/$(CC)/$(PROJECT_NAME)/$(PLATFORM_TARGET)/$(CONFIGURATION)
OUTPUT_FILE_NAME=$(BIN_PATH)/$(PROJECT_NAME)

CFLAGS=-Wall -Wextra -I$(INCLUDE_PATH) \
	-g \
	-DKAPHEIN_COMPOPT_DLL_API_MODE=1

default: all

all: build

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

build: $(OBJ_FILE_PATHS)
	mkdir -p $(BIN_PATH)
	$(CC) $(CFLAGS) -fPIC -shared -o $(OUTPUT_FILE_NAME).dll -Wl,--out-implib,$(OUTPUT_FILE_NAME).a $(OBJ_FILE_PATHS)

clean:
	rm -rf $(BIN_PATH)
	rm -rf $(OBJ_PATH)

