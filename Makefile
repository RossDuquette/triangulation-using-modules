PROG_NAME ?= thread-msg-example
LIB_NAME ?= thread-msg
DEBUG ?= n
VERBOSE ?= n

OBJ_DIR = obj
MODULES_DIR = modules
MSG_TYPES_DIR = msg-types

SRCS += main.cpp
SRCS += $(MODULES_DIR)/stdout.cpp
SRCS += $(MSG_TYPES_DIR)/string.cpp

SRCS += $(MODULES_DIR)/beacon-sim.cpp
SRCS += $(MODULES_DIR)/kalman.cpp
SRCS += $(MODULES_DIR)/keyboard.cpp
SRCS += $(MODULES_DIR)/open-gl.cpp
SRCS += $(MODULES_DIR)/pose-estimator.cpp
SRCS += $(MODULES_DIR)/triangulation.cpp
SRCS += $(MODULES_DIR)/vehicle-sim.cpp
SRCS += $(MODULES_DIR)/viewer.cpp

SRCS += $(MSG_TYPES_DIR)/drive.cpp
SRCS += $(MSG_TYPES_DIR)/location-2d.cpp
SRCS += $(MSG_TYPES_DIR)/measured-dist.cpp
SRCS += $(MSG_TYPES_DIR)/pose-2d.cpp

LIB_DIR = $(LIB_NAME)
LIB = $(LIB_DIR)/lib$(LIB_NAME).a

ifeq ($(VERBOSE),y)
CC = g++
LD = g++
else
CC = @echo '   ' CC $@; g++
LD = @echo '   ' LD $@; g++
endif

INC_DIRS += .
INC_DIRS += ./$(MODULES_DIR)

CFLAGS += $(addprefix -I, $(INC_DIRS))
CFLAGS += -O0
CFLAGS += -Wno-format-truncation
ifeq ($(DEBUG),y)
CFLAGS += -g
endif

LDFLAGS += -lpthread
LDFLAGS += -lglut
LDFLAGS += -lGL
LDFLAGS += -lncurses
LDFLAGS += -L$(LIB_DIR) -l$(LIB_NAME)

DEPS := $(shell find . -name "*.h")
OBJS := $(addprefix $(OBJ_DIR)/, $(patsubst %.cpp,%.o,$(SRCS)))

all: lib $(PROG_NAME)

lib:
	@$(MAKE) -C $(LIB_DIR)

$(PROG_NAME): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -f $(PROG_NAME)
