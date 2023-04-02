g++ -c libs/*.cpp
g++ -c classes/*.cpp
g++ -o $1.out $1.cpp *.o
./$1.out
