.PHONY: all clean
all: alphaBlendingFast alphaBlending alphaBlendingAVX

MULTIPLIERPLAIN = 50
MULTIPLIER      = 10 * MULTIPLIERPLAIN

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

# CONFIG_INCLUDE :=  -I "..\config"

COMPILE_FLAGS += $(LIBOPENCV_INCLUDE)
COMPILE_FLAGS_O0 += $(LIBOPENCV_INCLUDE)
LINK_FLAGS     = $(LIBOPENCV_LINK)


NAME = main
OBJECTSFAST     := ${OBJECTSFAST}     build\${NAME}.o
OBJECTS         := ${OBJECTS}         build\${NAME}.o
OBJECTSAVX      := ${OBJECTSAVX}      build\${NAME}.o
OBJECTSMUL      := ${OBJECTSMUL}      build\${NAME}.o
OBJECTSAVXMUL   := ${OBJECTSAVXMUL}   build\${NAME}.o
OBJECTSO0       := ${OBJECTSO0}       build\${NAME}.o
OBJECTSAVXO0    := ${OBJECTSAVXO0}    build\${NAME}.o
OBJECTSMULO0    := ${OBJECTSMULO0}    build\${NAME}.o
OBJECTSAVXMULO0 := ${OBJECTSAVXMULO0} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O} 

NAME = fileIO
OBJECTSFAST     := ${OBJECTSFAST}     build\${NAME}.o
OBJECTS         := ${OBJECTS}         build\${NAME}.o
OBJECTSAVX      := ${OBJECTSAVX}      build\${NAME}.o
OBJECTSMUL      := ${OBJECTSMUL}      build\${NAME}.o
OBJECTSAVXMUL   := ${OBJECTSAVXMUL}   build\${NAME}.o
OBJECTSO0       := ${OBJECTSO0}       build\${NAME}.o
OBJECTSAVXO0    := ${OBJECTSAVXO0}    build\${NAME}.o
OBJECTSMULO0    := ${OBJECTSMULO0}    build\${NAME}.o
OBJECTSAVXMULO0 := ${OBJECTSAVXMULO0} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O}


NAMEcpp = blend
NAME = blendFast
OBJECTSFAST := ${OBJECTSFAST} build\${NAME}.o
build\${NAME}.o: sources\${NAMEcpp}.cpp
	${COMPILE_O}                               -DCOMPILENAME='"fast"'

NAME = blend
OBJECTS := ${OBJECTS} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	${COMPILE_O} -DMULTIPLY=${MULTIPLIERPLAIN} -DCOMPILENAME='"Of single plain"'

NAME = blendAVX
OBJECTSAVX := ${OBJECTSAVX} build\${NAME}.o
build\${NAME}.o: sources\${NAME}.cpp
	$(COMPILE_O) -DMULTIPLY=${MULTIPLIERPLAIN} -DCOMPILENAME='"Of single avx  "'

# NAMEcpp = drawM
# NAME = drawMMUL
# OBJECTSMUL := ${OBJECTSMUL} build\${NAME}.o
# build\${NAME}.o: sources\${NAMEcpp}.cpp
# 	$(COMPILE_O) -DMULTIPLY=${MULTIPLIER} -DCOMPILENAME='"Of mul10  plain"'

# NAMEcpp = drawMAVX
# NAME = drawMAVXMUL
# OBJECTSAVXMUL := ${OBJECTSAVXMUL} build\${NAME}.o
# build\${NAME}.o: sources\${NAMEcpp}.cpp
# 	$(COMPILE_O) -DMULTIPLY=${MULTIPLIER} -DCOMPILENAME='"Of mul10  avx  "'

# NAMEcpp = drawM
# NAME = drawMO0
# OBJECTSO0 := ${OBJECTSO0} build\${NAME}.o
# build\${NAME}.o: sources\${NAMEcpp}.cpp
# 	${COMPILE_O_O0}                          -DCOMPILENAME='"O0 single plain"'

# NAMEcpp = drawMAVX
# NAME = drawMAVXO0
# OBJECTSAVXO0 := ${OBJECTSAVXO0} build\${NAME}.o
# build\${NAME}.o: sources\${NAMEcpp}.cpp
# 	$(COMPILE_O_O0)                          -DCOMPILENAME='"O0 single avx  "'

# NAMEcpp = drawM
# NAME = drawMMULO0
# OBJECTSMULO0 := ${OBJECTSMULO0} build\${NAME}.o
# build\${NAME}.o: sources\${NAMEcpp}.cpp
# 	$(COMPILE_O_O0) -DMULTIPLY=${MULTIPLIER} -DCOMPILENAME='"O0 mul10  plain"'

# NAMEcpp = drawMAVX
# NAME = drawMAVXMULO0
# OBJECTSAVXMULO0 := ${OBJECTSAVXMULO0} build\${NAME}.o
# build\${NAME}.o: sources\${NAMEcpp}.cpp
# 	$(COMPILE_O_O0) -DMULTIPLY=${MULTIPLIER} -DCOMPILENAME='"O0 mul10  avx  "'


alphaBlendingFast: ${OBJECTSFAST}
	@ g++ $(COMPILE_FLAGS) $^ -o build\alphaBlendingFast $(LINK_FLAGS)
alphaBlending: ${OBJECTS}
	@ g++ $(COMPILE_FLAGS) $^ -o build\alphaBlending $(LINK_FLAGS)
alphaBlendingAVX: ${OBJECTSAVX}
	@ g++ $(COMPILE_FLAGS) $^ -o build\alphaBlendingAVX $(LINK_FLAGS)
# mandelbrotMUL: ${OBJECTSMUL}
# 	@ g++ $(COMPILE_FLAGS) $^ -o build\mandelbrotMUL $(LINK_FLAGS)
# mandelbrotAVXMUL: ${OBJECTSAVXMUL}
# 	@ g++ $(COMPILE_FLAGS) $^ -o build\mandelbrotAVXMUL $(LINK_FLAGS)
# mandelbrotO0: ${OBJECTSO0}
# 	@ g++ $(COMPILE_FLAGS_O0) $^ -o build\mandelbrotO0 $(LINK_FLAGS)
# mandelbrotAVXO0: ${OBJECTSAVXO0}
# 	@ g++ $(COMPILE_FLAGS_O0) $^ -o build\mandelbrotAVXO0 $(LINK_FLAGS)
# mandelbrotMULO0: ${OBJECTSMULO0}
# 	@ g++ $(COMPILE_FLAGS_O0) $^ -o build\mandelbrotMULO0 $(LINK_FLAGS)
# mandelbrotAVXMULO0: ${OBJECTSAVXMULO0}
# 	@ g++ $(COMPILE_FLAGS_O0) $^ -o build\mandelbrotAVXMULO0 $(LINK_FLAGS)

clean:
	@ del build\*.o build\*.exe build\*.lib
