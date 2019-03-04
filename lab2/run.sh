gcc -c static.c -o static.o
ar r lib_static.a static.o
gcc -c -Wall -fPIC -D_GNU_SOURCE dynamic.c
gcc dynamic.o -shared -o lib_dynamic.so

gcc -c main.c -o main.o

gcc main.o lib_static.a -L. -l_dynamic -o wynik.out
chmod 777 lib_dynamic.so
./wynik.out

