@echo off

set CONFIG=%~1
if "%CONFIG%"=="" set CONFIG=Debug

set GEN="Visual Studio 18 2026"
set OUT=./tout

echo(=== Target: %CONFIG% ^| Generator: %GEN% ===

:CONFIGURE
echo(=== Configuring CMake ===
cmake -S ./tests -G %GEN% -B %OUT% 
if errorlevel 1 exit /b 1

:BUILD
echo(=== Building %CONFIG% ===
cmake --build %OUT% --config %CONFIG%
if errorlevel 1 exit /b 1

echo(=== Running Tests: %EXE% in %CONFIG% ===

set EXE=%OUT%/Debug/DatabaseTest.exe
for %%D in ("%EXE%") do (set "EXEDIR=%%~dpD" & set "EXENAME=%%~nxD")
if exist %OUT%/Debug/DatabaseTest.exe (
    pushd "%EXEDIR%" >nul
    "%EXENAME%"
    set "ERR=%ERRORLEVEL%"
    popd >nul
    exit /b %ERR%
)
