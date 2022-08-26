all: StrLib tests

COMPILE_FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE

StrLib: build\main.o
	@ g++ $(COMPILE_FLAGS) build\main.o -o build\StrLib

build\main.o: main.cpp
	@ g++ $(COMPILE_FLAGS) -c main.cpp
	@ move main.o build > NUL


tests: build\testMain.o build\cmdParser.o build\testUI.o build\autoTest.o build\tests.o
	@ g++ $(COMPILE_FLAGS) build\testMain.o build\cmdParser.o build\testUI.o build\autoTest.o build\tests.o -o build\tests
	@ .\build\tests.exe

build\testMain.o: tests\testMain.cpp
	@ g++ $(COMPILE_FLAGS) -c tests\testMain.cpp -I .
	@ move testMain.o build > NUL

build\tests.o: tests\tests.cpp
	@ g++ $(COMPILE_FLAGS) -c tests\tests.cpp -I .
	@ move tests.o build > NUL


build\testUI.o: testingSystem\testUI.cpp
	@ g++ $(COMPILE_FLAGS) -c testingSystem\testUI.cpp -I .
	@ move testUI.o build > NUL

build\autoTest.o: testingSystem\autoTest.cpp
	@ g++ $(COMPILE_FLAGS) -c testingSystem\autoTest.cpp -I .
	@ move autoTest.o build > NUL


build\cmdParser.o: cmdParser\cmdParser.cpp
	@ g++ $(COMPILE_FLAGS) -c cmdParser\cmdParser.cpp -I .
	@ move cmdParser.o build > NUL


clean:
	@ del build\*.o build\*.exe
