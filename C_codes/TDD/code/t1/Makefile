#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = t1
TARGET_LIB = \
	lib/lib$(COMPONENT_NAME).a

TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

CPPUTEST_USE_EXTENSIONS = Y
CPPUTEST_WARNINGFLAGS += -Wall
# CPPUTEST_WARNINGFLAGS += -Werror
# CPPUTEST_WARNINGFLAGS += -Wswitch-default
# CPPUTEST_WARNINGFLAGS += -Wswitch-enum
# CPPUTEST_WARNINGFLAGS += -Wno-self-assign
CPPUTEST_CFLAGS += -std=c89
CPPUTEST_CFLAGS += -Wextra
CPPUTEST_CFLAGS += -pedantic
CPPUTEST_CFLAGS += -Wstrict-prototypes

SRC_DIRS = \
	src/*\
	# src/MyOS/Acme\

TEST_SRC_DIRS = \
	tests \
	tests/util \
	tests/devices \
	tests/HomeAutomation\
	tests/IO \
	mocks/IO \
	mocks\
	# tests/MyOS \

INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include/\
  include/*\
  mocks/IO \
  mocks


ifeq ($(CPPUTEST_HOME),)
$(info CPPUTEST_HOME not set! See README.txt)
else
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
endif
