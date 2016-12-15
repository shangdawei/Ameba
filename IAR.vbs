Option Explicit

' [HKEY_LOCAL_MACHINE\ SOFTWARE\IAR Systems\Embedded Workbench \5.0\Locations\Location1]
' [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\IAR Systems\Embedded Workbench\5.0\Locations\Location1]
' "InstallPath"="C:\\Program Files (x86)\\IAR Systems\\EWARM"
' [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\IAR Systems\Embedded Workbench\5.0\Locations\Location1\Product Families\ARM]

Dim oShell
Dim oRegistry
Dim oFileSystem

Dim oArgs, Var1, Var2, Var3, Var4, Var5, Var6, Var7, Var8, Var9

Const OverwriteExisting = TRUE
Const ForReading = 1, ForWriting = 2, ForAppending = 8
Const TristateUseDefault = -2, TristateTru = -1, TristateFalse = 0
Const WindowsFolder = 0, SystemFolder = 1, TemporaryFolder = 2

' Registry Hives
Const HKEY_CLASSES_ROOT   = &H80000000
Const HKEY_CURRENT_USER   = &H80000001
Const HKEY_LOCAL_MACHINE  = &H80000002
Const HKEY_USERS          = &H80000003
Const HKEY_CURRENT_CONFIG = &H80000005
Const HKEY_DYN_DATA       = &H80000006

Const HKCR = &H80000000 'HKEY_CLASSES_ROOT
Const HKCU = &H80000001 'HKEY_CURRENT_USER
Const HKLM = &H80000002 'HKEY_LOCAL_MACHINE
Const HKUS = &H80000003 'HKEY_USERS
Const HKCC = &H80000005 'HKEY_CURRENT_CONFIG

' Reg Value Types
Const REG_SZ = 1
Const REG_EXPAND_SZ = 2
Const REG_BINARY = 3
Const REG_DWORD = 4
Const REG_DWORD_BIG_ENDIAN = 5
Const REG_LINK = 6
Const REG_MULTI_SZ = 7
Const REG_RESOURCE_LIST = 8
Const REG_FULL_RESOURCE_DESCRIPTOR = 9
Const REG_RESOURCE_REQUIREMENTS_LIST = 10
Const REG_QWORD = 11

' Registry Permissions
Const KEY_QUERY_VALUE = &H00001
Const KEY_SET_VALUE = &H00002
Const KEY_CREATE_SUB_KEY = &H00004
Const KEY_ENUMERATE_SUB_KEYS = &H00008
Const KEY_NOTIFY = &H00016
Const KEY_CREATE = &H00032
Const KEY_DELETE = &H10000
Const KEY_READ_CONTROL = &H20000
Const KEY_WRITE_DAC = &H40000
Const KEY_WRITE_OWNER = &H80000

Const strKeyPath32 = "SOFTWARE\IAR Systems\Embedded Workbench"
Const strKeyPath64 = "SOFTWARE\Wow6432Node\IAR Systems\Embedded Workbench"

Dim strInstallPathArray()
Dim strSubKeyLocationPathArray()
Dim strSubKeyLocationsPath

' HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\IAR Systems\Embedded Workbench\5.0\Locations\Location1
' [HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\IAR Systems\Embedded Workbench\5.0\Locations\Location1\Product Families\ARM]
' "InstallPath"="C:\\Program Files (x86)\\IAR Systems\\EWARM"
Function GetInstallPath( strSubKeyLocationPath )
  Dim arrSubKeys
  Dim strValue : strValue = ""
  If oRegistry.EnumKey(HKLM, strSubKeyLocationPath & "\Product Families\ARM", arrSubKeys) = 0 then
    Call oRegistry.GetStringValue( HKEY_LOCAL_MACHINE,strSubKeyLocationPath, "InstallPath", strValue)
  End If
  GetInstallPath = strValue
End Function

Sub GetSubKeyLocationsPath()
  Dim strKeyPath
  Dim strSubKeyPath
  Dim arrSubKeys
  If oRegistry.EnumKey(HKLM, strKeyPath32, arrSubKeys) = 0 then
    strKeyPath = strKeyPath32
  ElseIf oRegistry.EnumKey(HKLM, strKeyPath64, arrSubKeys) = 0 then
    strKeyPath = strKeyPath64
  Else
    Exit Sub
  End if

  Dim Subkey, SubKey2
  Dim arrSubKey2s
  For Each Subkey in arrSubKeys
    strSubKeyPath = strKeyPath & "\" & Subkey
    Call oRegistry.EnumKey( HKLM, strSubKeyPath, arrSubKey2s )
    For Each Subkey2 in arrSubKey2s
      if InStr(Subkey2, "Locations") > 0 Then
        strSubKeyLocationsPath = strSubKeyPath & "\" & Subkey2
        Exit For
      End If
    Next
    if strSubKeyLocationsPath <> "" Then Exit For
  Next
End Sub

Sub GetSubKeyLocationPathArray()
  Dim Index
  Dim Subkey
  Dim arrSubKeys
  Call oRegistry.EnumKey(HKLM, strSubKeyLocationsPath, arrSubKeys)
  ReDim strSubKeyLocationPathArray( uBound( arrSubKeys ) )

  Index = 0
  Dim strInstallPath
  For Each Subkey in arrSubKeys
    strSubKeyLocationPathArray( Index ) = strSubKeyLocationsPath & "\" & Subkey
    Index = Index + 1
  Next

  Index = Index - 1
  If Index <> UBound(strSubKeyLocationPathArray) Then
    ReDim strSubKeyLocationPathArray( Index  )
  End If
End Sub

Sub GetInstallPathArray()
  ReDim strInstallPathArray( UBound(strSubKeyLocationPathArray) )

  Dim APath
  Dim Index : Index = 0
  Dim I
  For I = LBound(strSubKeyLocationPathArray) to UBound(strSubKeyLocationPathArray)
    APath = GetInstallPath( strSubKeyLocationPathArray(I) )
    If APath <> "" Then
      strInstallPathArray(I) = APath
      Index = Index + 1
    End If
  Next

  Index = Index - 1
  If Index <> UBound(strInstallPathArray) Then
    ReDim strInstallPathArray( Index  )
  End If

End Sub

Function ASpace()
    ASpace = Space(1)
End Function

Function Quotes(ByVal strValue)
    Quotes = Chr(34) & strValue & Chr(34)
End Function

' Create InstallPath\Output Junction to %Temp% : mklink /J Output Z:\Output
' Copy IAR\arm\... to InstallPath\arm\...
Sub HandleInstallPath( APath )
  Const ComSpec = "%comspec% /c "
  Dim CommandLine
  Dim CurrentDirectory : CurrentDirectory = APath ' C:\Program Files (x86)\IAR Systems\EWARM
  oShell.CurrentDirectory = CurrentDirectory
  If oFileSystem.FolderExists( "OutputJunction") Then
    'oFileSystem.DeleteFolder ( "OutputJunction")
    CommandLine = "cmd /c rmdir OutputJunction"
    oShell.Run ComSpec & Quotes( CommandLine ), 0, True
  End If

  CommandLine = "mklink /J OutputJunction %Temp%"
  oShell.Run ComSpec & Quotes( CommandLine ), 0, True

  CurrentDirectory = oFileSystem.GetFile( WScript.ScriptFullName ).ParentFolder.Path
  oShell.CurrentDirectory = CurrentDirectory

  If not oFileSystem.FolderExists( "IAR" ) Then
    oShell.Popup "Run script from Ameba Folder."
    Exit Sub
  End If

  If not oFileSystem.FolderExists( CurrentDirectory & "\IAR\arm" ) Then
    oShell.Popup "Can not find IAR config files."
    Exit Sub
  End If

  CommandLine = "xcopy " & CurrentDirectory & "\IAR " & Quotes( APath ) _
  & " /s /y /b"
  oShell.Run ComSpec & Quotes( CommandLine ), 0, True
End Sub

Sub Main()

  strSubKeyLocationsPath = ""
  Call GetSubKeyLocationsPath()
  if strSubKeyLocationsPath = "" Then
    oShell.Popup "Can not find IAR EWARM"
    Exit Sub
  End if

  Call GetSubKeyLocationPathArray()

  Call GetInstallPathArray()

  Dim I
  For I = LBound(strInstallPathArray) to UBound(strInstallPathArray)
    Call HandleInstallPath( strInstallPathArray(I) )
  Next

  oShell.Popup "Done."
End Sub

Sub SetArgVars()
  Set oArgs = WScript.Arguments

  If WScript.Arguments.Count > 8 Then
    Var9 = oArgs(8)
  End If

  If WScript.Arguments.Count > 7 Then
    Var8 = oArgs(7)
  End If

  If WScript.Arguments.Count > 6 Then
    Var7 = oArgs(6)
  End If

  If WScript.Arguments.Count > 5 Then
    Var6 = oArgs(5)
  End If

  If WScript.Arguments.Count > 4 Then
    Var5 = oArgs(4)
  End If

  If WScript.Arguments.Count > 3 Then
    Var4 = oArgs(3)
  End If

  If WScript.Arguments.Count > 2 Then
    Var3 = oArgs(2)
  End If

  If WScript.Arguments.Count > 1 Then
    Var2 = oArgs(1)
  End If

  If WScript.Arguments.Count > 0 Then
    Var1 = oArgs(0)
  End If
End Sub

'object.OpenTextFile(filename[, iomode[, create[, format]]])
'iomode : ForReading, ForWriting, or ForAppending
'create : The value is True if a new file is created
Function OpenTextFileToRead( TextFilePathNmae)
  Dim oTextFile
  Set oTextFile = oFileSystem.OpenTextFile( TextFilePathNmae, ForReading )
  Set OpenTextFileToRead = oTextFile
End Function

' object.CreateTextFile(filename[, overwrite[, unicode]])
Function CreateTextFileToWrite( TextFilePathNmae)
  Dim oTextFile
  Set oTextFile = oFileSystem.CreateTextFile(TextFilePathNmae, True, False)
  Set CreateTextFileToWrite = oTextFile
End Function

'===================================================================================================
Set oShell = WScript.CreateObject("WScript.Shell")
Set oFileSystem = Wscript.CreateObject("Scripting.FileSystemObject")
Set oRegistry = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\default:StdRegProv")

SetArgVars()

Main()

Set oFileSystem = Nothing
Set oRegistry = Nothing
Set oShell = Nothing

WScript.Quit
'===================================================================================================
