g++ -c Cell.cpp
g++ -c Animal.cpp
g++ -o $1.out $1.cpp Animal.o Cell.o
./$1.out