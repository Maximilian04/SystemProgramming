.PHONY: all clean
all: libgraphvizBuf

COMPILE_DEFAULT_FLAGS := -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_DEFAULT_FLAGS += -I headers -I "..\config"
COMPILE_FLAGS := $(COMPILE_DEFAULT_FLAGS) -D_DEBUG
#COMPILE_FLAGS := $(COMPILE_DEFAULT_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@


LIBLOGGER_PATH := .\..\010.logger\build
LIBLOGGER_HEADERS := $(LIBLOGGER_PATH)\..\headers
LIBLOGGER_NAME := logger
LIBLOGGER_LINK := -L$(LIBLOGGER_PATH) -l$(LIBLOGGER_NAME)
LIBLOGGER_INCLUDE := -I$(LIBLOGGER_HEADERS)

COMPILE_FLAGS += $(LIBLOGGER_INCLUDE)
LINK_FLAGS = $(LIBLOGGER_LINK)


NAME = graphviz
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

libgraphvizBuf: ${OBJECTS}
	@ ar r build\graphvizBuf.lib "build\*.o"

clean:
	@ del build\*.o build\*.exe build\*.lib
