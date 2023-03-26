g++ -c libs/common.cpp
g++ -c classes/Cell.cpp
g++ -c classes/Animal.cpp
g++ -o $1.out $1.cpp Animal.o Cell.o common.o
./$1.out