@ECHO OFF
SETLOCAL EnableDelayedExpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do     rem"') do (
  set "DEL=%%a"
)

set COUNT=0
for %%x in (%*) do set /A COUNT+=1

if %COUNT%==1 (
	goto do_file_check
) else (
	echo Usage: makelib.bat ^<file.cc^>
	pause
	exit /b
)

:do_file_check
set fname=%1
if exist %fname% (
	goto do_compile
) else (
	call :colorEcho 0c "File %fname% not found!"
	echo.
	pause
	exit /b
)

:do_compile

echo Building %fname%...

set fname_noext=%~n1
set lib_str=lib
set dll_str=.dll
set lib_fname=%lib_str%%fname_noext%%dll_str%
cl.exe -O2 %fname% /link /DLL /MD /OUT:%lib_fname%

if errorlevel 1 (
	call :colorEcho 0c "Error - "
	echo  Failed to build Library.
) else (
	call :colorEcho 0a "%lib_fname% - Custom library successfully generated!"
	echo.
	del *.obj
)

pause
exit /b

:colorEcho
echo off
<nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1i