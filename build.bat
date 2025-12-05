cls
cd build
gcc ..\src\*.c -c ^
-I..\include
ar rcs libdata_structures.a stack.o
cd ..
