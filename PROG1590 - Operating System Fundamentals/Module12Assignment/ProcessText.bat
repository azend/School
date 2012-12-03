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

REM set /p choice="Enter your choice: "

echo Enter your choice
read.exe
goto processMenu

:processMenu
if "%errorlevel%"=="1" goto openInNotepad
if "%errorlevel%"=="2" goto openInWord
if "%errorlevel%"=="3" goto openInTextpad
if "%errorlevel%"=="4" goto print
goto exit

:openInNotepad
notepad "%1"
goto exit

:openInWord
if exist "%ProgramFiles(x86)%" (
	start /B "%ProgramFiles(x86)%\Microsoft Office\OFFICE14\winword.exe" "%1"
) else (
	start /B "%ProgramFiles%\Microsoft Office\OFFICE14\winword.exe" "%1"
)
 "%1"
goto exit

:openInTextpad
if exist "%ProgramFiles(x86)%" (
	start /B "%ProgramFiles(x86)%\TextPad 6\TextPad.exe" "%1"
) else (
	start /B "%ProgramFiles%\TextPad 6\TextPad.exe" "%1"
)
goto exit

:print
notepad /p "%1"
goto exit

:exit
echo Goodbye.
exit





