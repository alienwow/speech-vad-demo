mkdir build
mkdir output_pcm
del build\*.* /Q /F
del output_pcm\*.* /Q /F
cd build

REM cmake .. -A x64				&& ^
cmake .. -G "MinGW Makefiles"					&& ^
mingw32-make -j4							    && ^
copy libvad-demo.dll ..							&& ^
echo #-----------build succeeded----------#		&& ^
REM ..\vad-demo.exe

cd ..
@pause