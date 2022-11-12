# Stack
#### Project with implementation of Stack and functions for work with it

The project has its own doxygen documentation: [badlink](https://github.com/MaximilianYan/SystemProgramming/wiki)

## Features

* Run make with [**makefile**](https://github.com/MaximilianYan/SystemProgramming/blob/main/Autumn22/004.Stack/makefile). Standart tests will be done automaticly.
* Run **build/tests.exe** without cmd arguments for run [**standart tests**](https://github.com/MaximilianYan/SystemProgramming/blob/main/Autumn22/004.Stack/tests/standartTests.txt).
* Run **build/tests.exe** with *-f* and file name as cmd argument for run your own tests. (example: [**myTest.txt**](https://github.com/MaximilianYan/SystemProgramming/blob/main/Summer22/002.StrLib/myTest.txt))
* Run **build/tests.exe** with *-h* as cmd argument to see help message.
* Run **build/Stack.exe** to get **build/tests.exe** in *-i* mode.
* Run doxygen with [**Doxyfile**](https://github.com/MaximilianYan/SystemProgramming/blob/main/Autumn22/004.Stack/Doxyfile) for genarate documentation. Ready-to-use script [**runDoxygen.bat**](https://github.com/MaximilianYan/SystemProgramming/blob/main/Autumn22/004.Stack/runDoxygen.bat).

## Tools

* **C/C++ compiler:** GCC (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

## Documentation

* Doxygen documentation: **html/index.html** (see how to generate documentation above)

##

### Typical errors

* *mingw32-make: \*\*\* [makefile:19: tests] Error -1073741819* - in file **tests/tests.h** wrong value in **NUMBER_OF_TEST_FUNCS**
