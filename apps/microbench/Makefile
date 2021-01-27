NAME = microbench
SRCS = $(shell find src/ -name "*.c" -o -name "*.cc")

INPUT ?= REF
CFLAGS += -DSETTING_$(INPUT)
CXXFLAGS += -DSETTING_$(INPUT)

include $(AM_HOME)/Makefile.app
