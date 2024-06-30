@echo off

echo Compilando...
gcc -pedantic -g -o main.exe ./src/avl.c ./src/lista.c ./src/hash.c ./src/json.c ./main.c

START main.exe municipios.json