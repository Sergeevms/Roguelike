!include "MUI2.nsh"

Name "Roguelike"
OutFile "RoguelikeInstaller.exe"
InstallDir "$PROGRAMFILES\Roguelike"

!ifdef VERSION
	VIProductVersion "${VERSION}.0"
	VIFIleVersion "${VERSION}.0"
	VIAddVersionKey "FileVersion" "${VERSION}.0"
!endif

!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "Russian"
!insertmacro MUI_LANGUAGE "English"

Section "Roguelike"
	SetOutPath "$INSTDIR"
	File "..\x64\Release\Roguelike.exe"
	File "..\x64\Release\openal32.dll"
	File "README.txt"
	
	CreateDirectory "$INSTDIR\Resources"

	CreateDirectory "$INSTDIR\Resources\Fonts"
	SetOutPath "$INSTDIR\Resources\Fonts"
	File "..\Roguelike\Resources\Fonts\Roboto-Regular.ttf"

	CreateDirectory "$INSTDIR\Resources\Sounds"
	SetOutPath "$INSTDIR\Resources\Sounds"
	File "..\Roguelike\Resources\Sounds\Clinthammer__Background_Music.wav"
	
	
	CreateDirectory "$INSTDIR\Resources\TextureMaps"
	SetOutPath "$INSTDIR\Resources\TextureMaps"
	File "..\Roguelike\Resources\TextureMaps\Enemy.png"
	File "..\Roguelike\Resources\TextureMaps\Player.png"
	File "..\Roguelike\Resources\TextureMaps\Floor.png"
	File "..\Roguelike\Resources\TextureMaps\Wall.png"

	WriteUninstaller "$INSTDIR\Uninstall.exe"
	
	SetOutPath "$INSTDIR"
	CreateDirectory "$SMPROGRAMS\Roguelike"
	CreateShortcut "$SMPROGRAMS\Roguelike\Roguelike.lnk" "$INSTDIR\Roguelike.exe"
	CreateShortcut "$SMPROGRAMS\Roguelike\Uninstall.lnk" "$INSTDIR\Uninstall.exe"

	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Roguelike" \
        "DisplayName" "Roguelike"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Roguelike" \
        "UninstallString" '"$INSTDIR\Uninstall.exe"'
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Roguelike" \
        "DisplayVersion" "${VERSION}"
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Roguelike" \
        "NoModify" 1
    WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Roguelike" \
        "NoRepair" 1
SectionEnd

Section "Uninstall"
	Delete "$INSTDIR\Roguelike.exe"
	Delete "$INSTDIR\Uninstall.exe"
	Delete "$INSTDIR\README.txt"
	Delete "$INSTDIR\openal32.dll"
	Delete "$INSTDIR\Resources\Fonts\Roboto-Regular.ttf"
	RMDir "$INSTDIR\Resources\Fonts"
	Delete "$INSTDIR\Resources\Sounds\Clinthammer__Background_Music.wav"
	RMDir "$INSTDIR\Resources\Sounds"
    Delete "$INSTDIR\Resources\TextureMaps\Enemy.png"
    Delete "$INSTDIR\Resources\TextureMaps\Player.png"
    Delete "$INSTDIR\Resources\TextureMaps\Floor.png"
    Delete "$INSTDIR\Resources\TextureMaps\Wall.png"
	RMDir "$INSTDIR\Resources\TextureMaps"
	RMDir "$INSTDIR\Resources"
	RMDir "$INSTDIR"

    Delete "$SMPROGRAMS\Roguelike\Roguelike.lnk" 
	Delete "$SMPROGRAMS\Roguelike\Uninstall.lnk"
	RMDir "$SMPROGRAMS\Roguelike"

	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Roguelike"
SectionEnd

