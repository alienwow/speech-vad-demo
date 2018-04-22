set PATH=C:\Program Files\mingw-w64\x86_64-7.3.0-posix-seh-rt_v5-rev0\mingw64\bin;%PATH%
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