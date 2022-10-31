.PHONY: all clean
all: libTestingSystem

COMPILE_DEFAULT_FLAGS := -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_DEFAULT_FLAGS := $(COMPILE_DEFAULT_FLAGS) -I headers
COMPILE_FLAGS := $(COMPILE_DEFAULT_FLAGS) -D_DEBUG
#COMPILE_FLAGS := $(COMPILE_DEFAULT_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@

LIBCMDPARSER_PATH := ..\009.cmdParser\build
LIBCMDPARSER_HEADERS := $(LIBCMDPARSER_PATH)\..\headers
LIBCMDPARSER_NAME := cmdParser
LIBCMDPARSER_LINK := -L$(LIBLIST_PATH) -l$(LIBLIST_NAME)
LIBCMDPARSER_INCLUDE := -I$(LIBCMDPARSER_HEADERS)

COMPILE_FLAGS := $(COMPILE_FLAGS) $(LIBCMDPARSER_INCLUDE)

NAME := testingSystem
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

NAME := autoTest
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

libTestingSystem: ${OBJECTS}
	@ ar r build\TestingSystem.lib "build\*.o"

clean:
	@ del build\*.o build\*.exe build\*.lib
