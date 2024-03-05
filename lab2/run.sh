gcc -Wall -c invsqrt.c -o invsqrt.o
gcc -Wall -O3 -ffast-math -c opt_invsqrt.c -o opt_invsqrt.o
# gcc -Wall -c main.c -o main.o
# gcc main.o invsqrt.o opt_invsqrt.o -o ./program -lm

ar r libinvsqrt.a invsqrt.o opt_invsqrt.o
gcc -Wall -c main.c -o main.o -lm
gcc main.o -L. -linvsqrt -o ./program_static -lm

gcc -Wall -fPIC -c invsqrt.c
gcc -Wall -O3 -ffast-math -fPIC -c opt_invsqrt.c
gcc invsqrt.o opt_invsqrt.o -shared -o lib_functions.so -lm
gcc main.o -L. lib_functions.so -o program_dynamic -lm
