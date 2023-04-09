g++ -c libs/*.cpp
g++ -c classes/*.cpp
g++ -o test.exe test.cpp *.o
test.exe