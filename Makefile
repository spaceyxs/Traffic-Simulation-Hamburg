CC=g++
CFLAGS=-g -std=gnu++2b -DSIM_TIME

CADMIUM_INCLUDE := $(firstword $(wildcard ../cadmium_v2/include ../cadmium/include))

ifeq ($(CADMIUM_INCLUDE),)
$(error Could not find Cadmium include folder. Expected ../cadmium_v2/include or ../cadmium/include)
endif

INCLUDECADMIUM=-I $(CADMIUM_INCLUDE)
INCLUDES=-I ./include -I ./atomics -I ./data_structures -I ./top_model

bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)

main_top.o: top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDES) top_model/main.cpp -o build/main_top.o

simulator: main_top.o
	$(CC) -g -o bin/traffic_sim build/main_top.o

all: simulator

clean:
	rm -f bin/* build/*
