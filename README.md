# std2
My implementation of C++ containers with modern C++23

# Project structure
Each typical C++ std library (i.e. vector, queue, etc...) has it's own directory under the project root directory

# Building the libraries
- At the root level, use the make commands to build all libraries
```bash
make all
```
- or choose certain targets to build:
```bash
make memory
```
- The flag `-DCMAKE_CXX_COMPILER=g++-14` should not be needed

# Creating a release
- Triggering the workflow to build and publish a release requires a `git tag` push
- Create and push a tag:
```bash
git tag -a v1.0.0 -m "First release version"
git push origin --tags
```
> Note the tag version must be higher than the current tag

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
