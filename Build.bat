@echo off
:: Batch file to build the Roguelike.sln solution

:: Step 1: Define paths and configuration
set SOLUTION_PATH=Roguelike.sln
set MSBUILD_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
set CONFIGURATIOn=Debug
set PLATFORM=x64

:: Step 2: Cheack if MSbuild exists
if not exist %MSBUILD_PATH% (
	echo MSBuild not found at %MSBUILD_PATH%. Please check your installation.
	pause
	exit /b 1
)

:: Step 3: Build the solution
echo Building solution: %SOLUTION_PATH%
echo Configuration: %CONFIGURATION%

%MSBUILD_PATH% %SOLUTION_PATH% ^
	/p:Configuration=%CONFIGURATION% ^
	/p:Platform=%PLATFORM% ^
	/t:Engine;Roguelike

:: Step 4: Check build result
if %ERRORLEVEL% neq 0 (
	echo Build failed
	pause
	exit /b %ERRORLEVEL%
)

:: Step 5: Copy required DLL file
if exist "%CD%\SFML\SFML-2.5.1\bin\" (
	mkdir "%CD%\%PLATFORM%\%CONFIGURATION%" >nul
	copy "%CD%\SFML\SFML-2.5.1\bin\openal32.dll" "%CD%\%PLATFORM%\%CONFIGURATION%" >nul
	echo Copied DLL files to output directory.
)

:: Step 6: Copy resource files
if exist "%CD%\Roguelike\Resources\" (
	mkdir "%CD%\%PLATFORM%\%CONFIGuRATION%\Resources\" >nul
	xcopy /E /I /Y "%CD%\Roguelike\Resources\*" "%CD%\%PLATFORM%\%CONFIGURATION%\Resources\" >nul
       echo Copied resource files to output directory.
)

echo Build completed successfully.
