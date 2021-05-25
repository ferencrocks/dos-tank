mkdir build
del build\*.*
copy assets\*.* build
wcl386 src\*.c -fo=build\.obj -fe=build\tank.exe -fr=build\.err -i=c:\watcom\h -l=dos4g -bt=dos -wx -we -hw -d2