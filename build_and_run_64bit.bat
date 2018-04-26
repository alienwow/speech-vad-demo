mkdir build
mkdir output_pcm
del build\*.* /Q /F
del output_pcm\*.* /Q /F
cd build

cmake .. -G "MinGW Makefiles"					&& ^
mingw32-make -j4							    && ^
copy libFileCutUtil.dll ..						&& ^
echo #-----------build succeeded----------#		&& ^

cd ..
@pause