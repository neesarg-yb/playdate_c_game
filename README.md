# WIP Game where you play as a Sheep dog

### SDK & Development Tools
1. Get latest [Playdate SDK](https://play.date/dev/) & Simulator
2. Have Visual Studio 2019 installed
3. gcc-arm-none-eabi compiler [download here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
4. Install CMake [link](https://cmake.org/download/)  
<!-- -->
**Note!** Mark Add PATH variables during the cmake & gcc installations + Remeber the SDK & cmake install locations for next step

### Set Environment Variables
1. Open the Environment Variables of Windows OS
2. Add below two in its System Variables section
  * `PLAYDATE_SDK_PATH` = install directory of Playdate SDK. Mine is `C:\Program Files (x86)\Playdate\`
  * `PLAYDATE_VS_CMAKE` = location of cmake executable. For me it is `C:\Program Files\CMake\bin\cmake.exe`

### Repo Structure
/build: Visual Studio Solution files\
/src: C code\
/docs: Other project related documentation

### Building for Playdate Simulator
Simply use `Visual Studio > Build > Build pd_c_game` which'd generate .pdx file

### Output
/.pdx: Game that can be ran on Playdate Simulator\
/build/Debug & /build/Release: Output from VS compilation

### Building for Playdate Console
1. Open *x64 Native Tools Command Prompt for VS 2019* from Start Menu
2. Go to build directory of the project
3. Execute command `cmake .. -G "NMake Makefiles" --toolchain="%PLAYDATE_SDK_PATH%\C_API\buildsupport\arm.cmake"` 
4. Execute command `nmake`
<!-- -->
**Note!** I had to make sure that Source/ folder was created before running make steps
