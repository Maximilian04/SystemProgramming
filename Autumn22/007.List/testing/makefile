all: Testing

COMPILE_DEFAULT_FLAGS := -I. -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_DEFAULT_FLAGS := $(COMPILE_DEFAULT_FLAGS) -I$(LIBLIST_HEADERS)
COMPILE_FLAGS := $(COMPILE_DEFAULT_FLAGS) -D_DEBUG
#COMPILE_FLAGS := $(COMPILE_DEFAULT_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@


LIBLIST_PATH := .\..\build
LIBLIST_HEADERS := $(LIBLIST_PATH)\..\headers
LIBLIST_NAME := List
LIBLIST_LINK := -L$(LIBLIST_PATH) -l$(LIBLIST_NAME)
LIBLIST_INCLUDE := -I$(LIBLIST_HEADERS)

COMPILE_FLAGS := $(COMPILE_FLAGS) $(LIBLIST_INCLUDE)


NAME = main
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: ${NAME}.cpp
	${COMPILE_O}

Testing: ${OBJECTS} ${LIBLIST_PATH}\$(LIBLIST_NAME).lib
	@ g++ $(COMPILE_FLAGS) $^ -o build\testing $(LIBLIST_LINK)
#	echo relink

clean:
	@ del build\*.o build\*.exe
