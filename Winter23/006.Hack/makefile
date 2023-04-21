.PHONY: all clean
all: mandelbrotAVX

MULTIPLIER = 10

COMPILE_DEFAULT_FLAGS_WITHOUTO = -I headers -Wno-attributes -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_EJUDGE_CLIENT_SIDE
COMPILE_DEFAULT_FLAGS = $(COMPILE_DEFAULT_FLAGS_WITHOUTO) -Ofast
COMPILE_DEFAULT_O0_FLAGS = $(COMPILE_DEFAULT_FLAGS_WITHOUTO) -O0
COMPILE_AVX_FLAGS = -march=native -mavx -mavx2
# COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) $(COMPILE_AVX_FLAGS) -D_DEBUG
COMPILE_FLAGS = $(COMPILE_DEFAULT_FLAGS) $(COMPILE_AVX_FLAGS) -DNDEBUG
COMPILE_FLAGS_O0 = $(COMPILE_DEFAULT_O0_FLAGS) $(COMPILE_AVX_FLAGS) -DNDEBUG

COMPILE_O = @ g++ $(COMPILE_FLAGS) -c $^ -o $@
COMPILE_O_O0 = @ g++ $(COMPILE_FLAGS_O0) -c $^ -o $@

LIBOPENCV_PATH := D:\programming\libraries\opencv-4.6.0\opencv-build-release-freetype
LIBOPENCV_HEADERS := $(LIBOPENCV_PATH)\install\include
LIBOPENCV_NAME := opencv_world460
LIBOPENCV_LINK := -L$(LIBOPENCV_PATH)\bin -l$(LIBOPENCV_NAME)
LIBOPENCV_INCLUDE := -isystem$(LIBOPENCV_HEADERS)

# LIBWINMM_PATH := "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64"
# LIBWINMM_NAME := WinMM
# LIBWINMM_LINK := -L$(LIBWINMM_PATH) -l$(LIBWINMM_NAME)
#LIBWINMM_PATH := .\..
#LIBWINMM_NAME := WinMM
#LIBWINMM_LINK := -L$(LIBWINMM_PATH) -l$(LIBWINMM_NAME)

# CONFIG_INCLUDE :=  -I "..\config"

COMPILE_FLAGS += $(LIBOPENCV_INCLUDE)
COMPILE_FLAGS_O0 += $(LIBOPENCV_INCLUDE)
LINK_FLAGS     = $(LIBOPENCV_LINK)


NAME = main
OBJECTSAVX      := ${OBJECTSAVX}      build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O} -DCOMPILENAME=$(COMPILENAME)


NAME = drawMAVX
OBJECTSAVX := ${OBJECTSAVX} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	$(COMPILE_O)                          -DCOMPILENAME='"Of single avx  "'

NAME = mouse
OBJECTSAVX := ${OBJECTSAVX} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	$(COMPILE_O)

NAME = hack
OBJECTSAVX := ${OBJECTSAVX} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	$(COMPILE_O)


mandelbrotAVX: ${OBJECTSAVX}
	@ g++ $(COMPILE_FLAGS) $^ -o build\mandelbrotAVX $(LINK_FLAGS)

clean:
	@ del build\*.o build\*.exe build\*.lib
