.PHONY: all clean
all: akinator

COMPILE_DEFAULT_FLAGS = -I headers -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -D_DEBUG
#COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@

LIBTREE_PATH := .\..\014.Tree\build
LIBTREE_HEADERS := $(LIBTREE_PATH)\..\headers
LIBTREE_NAME := Tree
LIBTREE_LINK := -L$(LIBTREE_PATH) -l$(LIBTREE_NAME)
LIBTREE_INCLUDE := -I$(LIBTREE_HEADERS)

LIBLOGGER_PATH := .\..\010.logger\build
LIBLOGGER_HEADERS := $(LIBLOGGER_PATH)\..\headers
LIBLOGGER_NAME := logger
LIBLOGGER_LINK := -L$(LIBLOGGER_PATH) -l$(LIBLOGGER_NAME)
LIBLOGGER_INCLUDE := -I$(LIBLOGGER_HEADERS)

LIBGRAPHVIZPTR_PATH := .\..\012.graphvizPtr\build
LIBGRAPHVIZPTR_HEADERS := $(LIBGRAPHVIZPTR_PATH)\..\headers
LIBGRAPHVIZPTR_NAME := graphvizPtr
LIBGRAPHVIZPTR_LINK := -L$(LIBGRAPHVIZPTR_PATH) -l$(LIBGRAPHVIZPTR_NAME)
LIBGRAPHVIZPTR_INCLUDE := -I$(LIBGRAPHVIZPTR_HEADERS)

LIBCMDPARSER_PATH := .\..\009.cmdParser\build
LIBCMDPARSER_HEADERS := $(LIBCMDPARSER_PATH)\..\headers
LIBCMDPARSER_NAME := cmdParser
LIBCMDPARSER_LINK := -L$(LIBCMDPARSER_PATH) -l$(LIBCMDPARSER_NAME)
LIBCMDPARSER_INCLUDE := -I$(LIBCMDPARSER_HEADERS)

CONFIG_INCLUDE :=  -I "..\config"

COMPILE_FLAGS += $(LIBTREE_INCLUDE) $(LIBLOGGER_INCLUDE) $(LIBGRAPHVIZPTR_INCLUDE) $(LIBCMDPARSER_INCLUDE) $(CONFIG_INCLUDE)
LINK_FLAGS     = $(LIBTREE_LINK)    $(LIBLOGGER_LINK)    $(LIBGRAPHVIZPTR_LINK)    $(LIBCMDPARSER_LINK)


NAME = main
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

NAME = Akinator
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

NAME = akinatorIO
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

NAME = cmdParsing
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}


akinator: ${OBJECTS}
	@ g++ $(COMPILE_FLAGS) $^ -o build\akinator $(LINK_FLAGS)

clean:
	@ del build\*.o build\*.exe build\*.lib
