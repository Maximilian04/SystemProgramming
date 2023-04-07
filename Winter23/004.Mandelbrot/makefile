.PHONY: all clean
all: err mandelbrot mandelbrotAVX asm

COMPILE_DEFAULT_FLAGS = -I headers -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_AVX_FLAGS = -march=native -mavx -mavx2
COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) $(COMPILE_AVX_FLAGS) -D_DEBUG
# COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) $(COMPILE_AVX_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@

LIBOPENCV_PATH := D:\programming\libraries\opencv-4.6.0\opencv-build-release-freetype
LIBOPENCV_HEADERS := $(LIBOPENCV_PATH)\install\include
LIBOPENCV_NAME := opencv_world460
LIBOPENCV_LINK := -L$(LIBOPENCV_PATH)\bin -l$(LIBOPENCV_NAME)
LIBOPENCV_INCLUDE := -I$(LIBOPENCV_HEADERS)

# LIBWINMM_PATH := "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64"
# LIBWINMM_NAME := WinMM
# LIBWINMM_LINK := -L$(LIBWINMM_PATH) -l$(LIBWINMM_NAME)
#LIBWINMM_PATH := .\..
#LIBWINMM_NAME := WinMM
#LIBWINMM_LINK := -L$(LIBWINMM_PATH) -l$(LIBWINMM_NAME)

# CONFIG_INCLUDE :=  -I "..\config"

COMPILE_FLAGS += $(LIBOPENCV_INCLUDE)
LINK_FLAGS     = $(LIBOPENCV_LINK)


NAME = main
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

NAME = mainAVX
OBJECTSAVX := ${OBJECTSAVX} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}

NAME = mainErr
OBJECTSERR := ${OBJECTSERR} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}



mandelbrot: ${OBJECTS}
	@ g++ $(COMPILE_FLAGS) $^ -o build\mandelbrot $(LINK_FLAGS)
mandelbrotAVX: ${OBJECTSAVX}
	@ g++ $(COMPILE_FLAGS) $^ -o build\mandelbrotAVX $(LINK_FLAGS)
err: ${OBJECTSERR}
	@ g++ $(COMPILE_FLAGS) $^ -o build\err $(LINK_FLAGS)
asm: sources\mainAVX.cpp
	@ g++ $(COMPILE_FLAGS) -c $^ -S

clean:
	@ del build\*.o build\*.exe build\*.lib
