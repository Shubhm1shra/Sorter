@echo off
setlocal

set SOURCE_FILE=main.cpp
set OUTPUT_FILE=main
set DEPENDENT=TRUE
set DEPENDENCY=Sorter.cpp

echo.
echo [101mCompiling :[0m %SOURCE_FILE%
echo.

if /i %DEPENDENT%==TRUE (
    g++ -O3 %~dp0%DEPENDENCY% -o %~dp0%OUTPUT_FILE% %~dp0%SOURCE_FILE% -I\"C:\\msys64\\mingw64\\include\" -L\"C:\\msys64\\mingw64\\lib\" -lsfml-graphics -lsfml-window -lsfml-system
) else (
    g++ -O3 -o %~dp0%OUTPUT_FILE% %~dp0%SOURCE_FILE% -I\"C:\\msys64\\mingw64\\include\" -L\"C:\\msys64\\mingw64\\lib\" -lsfml-graphics -lsfml-window -lsfml-system
)

echo.

REM Calculating Time in 12 Hour HH : MM : SS Format

for /f "delims=." %%a in ('echo %TIME%') do (
    set fulltime=%%a
)

set hour=%fulltime:~0,2%

if %hour% leq 9 (
    set hour=0%hour:~0,1%
    set minute=%fulltime:~2, 2%
    set second=%fulltime:~5, 2%
) else (
    set minute=%fulltime:~3,2%
    set second=%fulltime:~6,2%
)

set ampm=AM
if %hour% geq 12 (
    set ampm=PM
    if %hour% gtr 12 set /a hour-=12
)

echo [102mFinished Compiling,[0m 
echo On [91m^<Date^>[0m : [36m%DATE:/=-%[0m
echo At [91m^<Time^>[0m : [36m%hour%:%minute%:%second% %ampm%[0m

echo.

pause

endlocal