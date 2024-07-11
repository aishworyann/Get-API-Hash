This repo contains a cpp code attached with assembly code for ror function. 
Enter the dll files name in the code from whose you want to find the the api hash and on running enter the hash, you will get the particular api name.
Eg. You got a hash of LoadLibraryA while debugging or reversing, let it be 77332425 (arbitarary), check the cpp file for all int imports of that PE file.
You will get the LoadLibraryA api name of that hash.

Step to compile and link .cpp and .asm file:
1. Compile assembly in separate file: **_nasm -f win32 stud.asm_**
2. Already used **extern** keyword to link the funcitons of asm to cpp
3. Compine the cpp file and link it to the assembly using the MS Visual C++ compiler :  _**cl -EHsc main.cpp stub.o**_
