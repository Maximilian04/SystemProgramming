all: mmake mcmake

COMPILE_DEFAULT_FLAGS = -I . -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
#COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -D_DEBUG
COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) -DNDEBUG

mmake: build\main.o
	@ g++ $(COMPILE_FLAGS) build\main.o -o build\mmake

build\main.o: main.cpp
	@ g++ $(COMPILE_FLAGS) -c main.cpp
	@ move main.o build > NUL


mcmake: build\mcmake.o
	@ g++ $(COMPILE_FLAGS) build\mcmake.o -o build\mcmake

build\mcmake.o: mcmake.cpp
	@ g++ $(COMPILE_FLAGS) -c mcmake.cpp
	@ move mcmake.o build > NUL

build\cmdParser.o: cmdParser\cmdParser.cpp
	@ g++ $(COMPILE_FLAGS) -c cmdParser\cmdParser.cpp -I .
	@ move cmdParser.o build > NUL


clean:
	@ del build\*.o build\*.exe
