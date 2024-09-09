# Playdate Hello World - Visual Studio C Project

### SDK & Development Tools
1. Get latest [Playdate SDK](https://play.date/dev/) & Simulator
2. Have Visual Studio 2019 installed
3. gcc-arm-none-eabi compiler [download here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
4. Install CMake [link](https://cmake.org/download/)  
<!-- -->
**Note!**
* Make sure to mark Add PATH variables during the cmake & gcc installations
* Remeber the install locations for the next section

### Set Environment Variables
Visual Studio solution uses below two environment variables..
<!-- -->
1. Open the Environment Variables of Windows
2. In the System variables section, add below two
  * `PLAYDATE_SDK_PATH` : Value is the install directory of Playdate SDK. Mine is `C:\Program Files (x86)\Playdate\`
  * `PLAYDATE_VS_CMAKE` : Value is the location of cmake.exe, for me it is `C:\Program Files\CMake\bin\cmake.exe`

### Repo Structure
/build: Visual Studio Solution files\
/src: C code\
/docs: Other project related documentation

### Output
/.pdx: Game package get created on compilation (you'd run this on Playdate Simulator)\
/build/Debug & /build/Release: Output from VS compilation

### Building for Playdate Simulator
Simply use Visual Studio to build .pdx files. That would run on simulator just fine.

### Building for Playdate Console
1. Open *x64 Native Tools Command Prompt for VS 2019* from Start Menu
2. Go to build directory of the project
3. Execute command `cmake .. -G "NMake Makefiles" --toolchain="%PLAYDATE_SDK_PATH%\C_API\buildsupport\arm.cmake"` 
4. Execute command `nmake`
<!-- -->
**Note!** 
I had to make sure that Source/ folder was created before running make steps.