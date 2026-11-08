Linux / WSL
mkdir build && cd build
cmake ..
make
./lab7

Windows（cmake）
mkdir build
cd build
cmake ..
cmake --build .
.\Debug\lab7.exe

Windows（g++ 直接编译）
g++ -std=c++17 -o lab7 test.cpp
.\lab7.exe