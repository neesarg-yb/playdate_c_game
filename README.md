# Playdate Hello World - Visual Studio C Project

### SDK & Development Tools
1. Get [Playdate SDK 1.7.0](https://devforum.play.date/) & Simulator
2. Have Visual Studio 2019 installed
3. gcc-arm-none-eabi compiler [download here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
4. Install CMake [link](https://cmake.org/download/)  
<!-- -->
**Note:** Make sure to mark Add PATH variables during the cmake & gcc installations

### Make sure!
SDK is installed at C:\Program Files (x86)\Playdate\
CMake is at C:\Program Files\CMake\bin\cmake.exe\  
<!-- -->
**Note:** There are still some references hardcoded from VS solution to those locations.

### Repo Structure
/build: Visual Studio Solution files\
/src: C code\
/docs: Other project related documentation

### Output
/.pdx: Game package get created on compilation (you'd run this on Playdate Simulator)\
/build/Debug & /build/Release: Output from VS compilation
