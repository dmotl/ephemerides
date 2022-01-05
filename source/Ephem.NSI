;--------------------------------
; Pøedpovìdi -- installer script
; Copyright 2020 David Motl
;--------------------------------

!include "MUI.nsh"
!define VERSION "1.22"
!define SRCDIR  ".."
!define DOCDIR  ".."
!define OUTDIR  ".."
!define URL     "http://www.motl.cz/dmotl/predpovedi/"

; The name of the installer
Name "Ephemerides ${VERSION}"

; The file to write
OutFile "${OUTDIR}\ephemerides-${VERSION}-win32.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\Ephemerides"

;--------------------------------
; Pages

!define MUI_FINISHPAGE_LINK "Internet: ${URL}"
!define MUI_FINISHPAGE_LINK_LOCATION "${URL}"

!define MUI_FINISHPAGE_RUN "$INSTDIR\Ephem.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Run program"
!define MUI_FINISHPAGE_NOREBOOTSUPPORT
!define MUI_COMPONENTSPAGE_NODESC

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "COPYING"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;---------------------------------
; Languages

!insertmacro MUI_LANGUAGE "English"

;--------------------------------
; The stuff to install

Section "!Ephemerides (required)" 
  SetOutPath $INSTDIR
  File ${SRCDIR}\ephem.exe
  CreateDirectory "$SMPROGRAMS\Ephemerides"
  CreateShortCut "$SMPROGRAMS\Ephemerides\Ephemerides.lnk" "$INSTDIR\ephem.exe" "" "$INSTDIR\ephem.exe" 0
  CreateShortCut "$DESKTOP\Ephemerides.lnk" "$INSTDIR\Ephem.exe" "" "$INSTDIR\Ephem.exe" 0
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  CreateShortCut "$SMPROGRAMS\Ephemerides\Uninstall program.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\Uninstall.exe" 0
  ;Add uninstall info to "Add/Remove programs"
  WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegExpandStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "DisplayName" "Ephemerides"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "DisplayIcon" "$INSTDIR\ephem.exe,0"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "DisplayVersion" "${VERSION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "URLInfoAbout" "http://www.motl.cz/dmotl/predpovedi/"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "NoModify" "1"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides" "NoRepair" "1"
SectionEnd 

SectionGroup "Electronic help"
  Section "Czech language"
    SetOutPath $INSTDIR
    File ${SRCDIR}\help-cs.chm
    CreateShortCut "$SMPROGRAMS\Ephemerides\Czech help.lnk"   "$INSTDIR\help-cs.chm" "" "$INSTDIR\help-cs.chm" 0
  SectionEnd
  Section "English language"
    SetOutPath $INSTDIR
    File ${SRCDIR}\help-en.chm
    CreateShortCut "$SMPROGRAMS\Ephemerides\English help.lnk"   "$INSTDIR\help-en.chm" "" "$INSTDIR\help-en.chm" 0
  SectionEnd
SectionGroupEnd

SectionGroup "Catalogues"
  Section "B.R.N.O. 12/2010"
    SetOutPath $INSTDIR
    File ${SRCDIR}\brno.dat
  SectionEnd
  Section "Prosper 08/2006"
    SetOutPath $INSTDIR
    File ${SRCDIR}\prosper.dat
  SectionEnd
  Section "BRKA 2005"
    SetOutPath $INSTDIR
    File ${SRCDIR}\brka_2005.dat
    Delete "$INSTDIR\brka.dat"
  SectionEnd
SectionGroupEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  Delete "$SMPROGRAMS\Ephemerides\*.lnk"
  Delete "$DESKTOP\Ephemerides.lnk"
  RMDir  "$SMPROGRAMS\Ephemerides"
  Delete "$INSTDIR\*.exe"
  Delete "$INSTDIR\*.chm"
  Delete "$INSTDIR\*.ini"
  Delete "$INSTDIR\brka_2005.dat"
  Delete "$INSTDIR\brno.dat"
  Delete "$INSTDIR\prosper.dat"
  RMDir  "$INSTDIR"
  ;Delete icons in Start menu
  RMDir /r "$SMPROGRAMS\Ephemerides"
  ;Delete uninstall info in "Add/Remove programs"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Ephemerides"
SectionEnd
