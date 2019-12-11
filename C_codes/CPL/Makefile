#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = C_Programming_Language

#--- Inputs ----#
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	src/mem\
	src/IO\
	src/util\

TEST_SRC_DIRS = \
	tests\
	tests/mem\
	tests/IO\
	tests/util\

MOCKS_SRC_DIRS = \
	mocks\

INCLUDE_DIRS =\
	$(CPPUTEST_HOME)/include\
	include/mem\
	include/util\
	include/IO\

CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default
# -Werror
# CPPUTEST_CFLAGS = -std=c89
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
