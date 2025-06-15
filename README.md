# std2
Implantation of C++ containers with modern C++23

# Build the library
```bash
cd build
cmake .. -G Ninja
ninja
```
- The flag `-DCMAKE_CXX_COMPILER=g++-14` should not be needed

# Run with main to test
```bash
./test_memory
```

# C++23 Setup

## Update CMake:
- CMake must be greater than version 3.30 for C++23 features
```bash
sudo apt install cmake
sudo apt install ninja-build
```
- Follow this answer to get the latest version: https://askubuntu.com/a/1157132

## Setup `g++`
### 1. Install Ubuntu 24.04
- On my WSL2, I simply ran the command to upgrade my Ubuntu version to 24.04:
```bash
sudo do-release-upgrade -d
```
- The `-d` gives the developer version of the latest
- Ubuntu 24.04 already comes with g++-13

### 2. Install `g++-14`
```bash
sudo apt-get update
sudo apt-get install g++-14
g++ --version
```
- If the version of g++ is still not >= 14, do the following step

### 3. Sym Link `g++-14`
- `/usr/bin/g++` is a symlink to the active g++ version being used
- Remove it and create a new symlink to g++-14
```bash
file /usr/bin/g++
sudo rm /usr/bin/g++
sudo ln -s /usr/bin/g++-14 /usr/bin/g++
g++ --version
```
- Now the version should be >= 14
