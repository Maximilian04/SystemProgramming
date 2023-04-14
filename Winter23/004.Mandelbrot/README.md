# Mandelbrot set
Accelerate the calculation of the Mandelbrot set with AVX intrinsic instructions.

![image](https://user-images.githubusercontent.com/33744661/232028526-9282078a-1f37-46e9-a1d3-99b12d58352c.png)
*(fps counter in top-left corner)*

## Compiled and measured variants:

| tag            | postfix | | gcc optimization | number of computations | with AVX intrinsics | | average fps |
|:---------------|:--------|-|:----------------:|:----------------------:|:-------------------:|-|:------------|
|Of single plain |         | | -Ofast           | 1 per frame            | no                  | | 2.86        |
|Of single avx   |AVX      | | -Ofast           | 1 per frame            | yes                 | | 15.86       |
|Of mul10  plain |MUL      | | -Ofast           | 10 per frame           | no                  | | 0.29        |
|Of mul10  avx   |AVXMUL   | | -Ofast           | 10 per frame           | yes                 | | 1.80        |
|O0 single plain |O0       | | -O0              | 1 per frame            | no                  | | 0.76        |
|O0 single avx   |AVXO0    | | -O0              | 1 per frame            | yes                 | | 1.75        |
|O0 mul10  plain |MULO0    | | -O0              | 10 per frame           | no                  | | 0.073       |
|O0 mul10  avx   |AVXMULO0 | | -O0              | 10 per frame           | yes                 | | 0.18        |

Raw measurments in [logfps-measured](https://github.com/MaximilianYan/SystemProgramming/blob/main/Winter23/004.Mandelbrot/logfps-measured.txt).
Windows11, AMD ryzen 7, while no other applications is working.
For every measuring more than ~30 frames was processed.
All measurments were run twice in different sequence.
Computer conditions were stable as possible.

**Compiler** - gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

## Ratios analysis:

- **(Ox-single-y)/(Ox-mul10-y)** - **control index**. The closer the index is to 10.0, the greater share of the time interesting function takes.
- s

