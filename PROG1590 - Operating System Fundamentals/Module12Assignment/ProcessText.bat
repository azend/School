@ECHO off

:start
goto checkIfFileExists

:checkIfFileExists
if exist "%1" (
	goto menu
) else (
	echo File does not exist.
	goto exit
)

:menu
echo What would you like to do?
echo 1)	Open in Notepad
echo 2) Open in Word
echo 3) Open in TextPad
echo 4) Print
echo

set /p choice="Enter your choice: "
goto processMenu

:processMenu
if "%choice%"=="1" goto openInNotepad
if "%choice%"=="2" goto openInWord
if "%choice%"=="3" goto openInTextpad
if "%choice%"=="4" goto print
goto exit

:openInNotepad
notepad "%1"
goto exit

:openInWord
winword "%1"
goto exit

:openInTextpad
if exist "%ProgramFiles(x86)%" (
	"%ProgramFiles(x86)%\TextPad 6\TextPad.exe" "%1"
) else (
	"%ProgramFiles%\TextPad 6\TextPad.exe" "%1"
)
goto exit

:print
notepad /p "%1"
goto exit

:exit
echo Goodbye.
exit





