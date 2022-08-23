all: QuadrEquation

COMPILE_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE

QuadrEquation: build\main.o build\QuadrEquation.o
	@ g++ $(COMPILE_FLAGS) build\main.o build\QuadrEquation.o -o build\QuadrEquation

build\main.o: main.cpp
	@ g++ $(COMPILE_FLAGS) -c main.cpp
	@ move main.o build > NUL

build\QuadrEquation.o: QuadrEquation.cpp
	@ g++ $(COMPILE_FLAGS) -c QuadrEquation.cpp
	@ move QuadrEquation.o build > NUL


tests: build\tests.o
	@ g++ $(COMPILE_FLAGS) build\tests.o -o build\tests
	@ .\build\tests.exe

build\tests.o: tests.c
	@ g++ $(COMPILE_FLAGS) -c tests.c
	@ move tests.o build > NUL

clean:
	@ del build\*.o build\*.exe
