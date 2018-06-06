; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "SiriKali"
#define MyAppVersion "1.3.4"
#define MyAppPublisher "Francis Banyikwa"
#define MyAppURL "https://mhogomchungu.github.io/sirikali"
#define MyAppExeName "sirikali.exe"
#define MyLibrariesLocation "C:\projects\SiriKali.libraries.Qt-5.9.5"
#define MyEXELocation "C:\projects\build-sirikali-Desktop_Qt_5_9_5_MinGW_32bit3-Release\sirikali.exe"
#define MyOutPutPath "C:\Users\Francis Banyikwa\Desktop\SiriKali"
#define MyGcryptLibraryPath "C:\projects\sirikali\libs\lib"
#define MySourcesPath "C:\projects\sirikali"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{677BCC48-2AC2-4CBC-B826-A94324C26988}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
LicenseFile={#MySourcesPath}\LICENSE.txt
OutputDir={#MyOutPutPath}
SetupIconFile={#MySourcesPath}\icons\256x256\sirikali.ico
Compression=lzma
SolidCompression=yes
DisableProgramGroupPage=yes
OutputBaseFilename=SiriKali-setup

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "{#MyEXELocation}"; DestDir: "{app}"; Flags: ignoreversion

Source: "{#MyLibrariesLocation}\*.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#MyGcryptLibraryPath}\*.dll"; DestDir: "{app}"; Flags: ignoreversion    

Source: "{#MySourcesPath}\LICENSE.txt"; DestDir: "{app}"; Flags: ignoreversion

Source: "{#MyLibrariesLocation}\bearer\*"; DestDir: "{app}\bearer"; Flags: ignoreversion

Source: "{#MyLibrariesLocation}\iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion

Source: "{#MyLibrariesLocation}\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion

Source: "{#MyLibrariesLocation}\styles\*"; DestDir: "{app}\styles"; Flags: ignoreversion

Source: "{#MyLibrariesLocation}\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion

Source: "{#MyLibrariesLocation}\translations\*"; DestDir: "{app}\translations"; Flags: ignoreversion

Source: "{#MySourcesPath}\translations\*.qm"; DestDir: "{app}\translations"; Flags: ignoreversion

Source: "{#MySourcesPath}\icons\256x256\sirikali.ico"; DestDir: "{app}\icons"; Flags: ignoreversion

; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\icons\sirikali.ico"; WorkingDir: "{app}"
;Name: "{commonprograms}\Uninstall {#MyAppName}"; Filename: "{uninstallexe}"; IconFilename: "{app}\icons\sirikali.ico"; WorkingDir: "{app}"

Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\icons\sirikali.ico"; WorkingDir: "{app}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\icons\sirikali.ico"; WorkingDir: "{app}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "corsican"; MessagesFile: "compiler:Languages\Corsican.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "greek"; MessagesFile: "compiler:Languages\Greek.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "scottishgaelic"; MessagesFile: "compiler:Languages\ScottishGaelic.isl"
Name: "serbiancyrillic"; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
Name: "serbianlatin"; MessagesFile: "compiler:Languages\SerbianLatin.isl"
Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "turkish"; MessagesFile: "compiler:Languages\Turkish.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

