gcc -c -Wall -fPIC -D_GNU_SOURCE dynamic.c
gcc dynamic.o -shared -o lib_dynamic.so
