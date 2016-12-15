'===================================================================================================
' Option :: Build Actions :: Pre-build command line
'---------------------------------------------------------------------------------------------------
' CSCRIPT "$PROJ_DIR$\..\..\Config\RTL8195AM_PreBuild.vbs" "$PROJ_DIR$" "$PROJ_PATH$" "$CONFIG_NAME$"
'
' X:\Ameba\Projects\Application                   "$PROJ_DIR$"       WScript.Arguments.Item(0)
' X:\Ameba\Projects\Application\Application.ewp   "$PROJ_PATH$"      WScript.Arguments.Item(1)
' RAM                                             "$CONFIG_NAME$"    WScript.Arguments.Item(2)
' Flash                                           "$CONFIG_NAME$"    WScript.Arguments.Item(2)
'---------------------------------------------------------------------------------------------------
' Options :: Linker : Config : Configuration file symbol definitions:
'---------------------------------------------------------------------------------------------------
' GEN_IMAGE=0 : RAM Configuration -------- Do nothing
' GEN_IMAGE=1 : Flash Configuration ------ Generate .bin .hex
'---------------------------------------------------------------------------------------------------
' Aplication.ewp
'---------------------------------------------------------------------------------------------------
'
' <project>
'   <configuration>
'     <name>RAM</name> : "$CONFIG_NAME$"
'     <settings>
'       <name>General</name>
'       <data>
'         <option>
'           <name>OGChipSelectEditMenu</name>
'           <state>RTL8195AM[TAB]RTL8195AM</state>
'         </option>
'       </data>
'     </settings>
'    <settings>
'    <settings>
'      <name>BUILDACTION</name>
'      <archiveVersion>1</archiveVersion>
'      <data>
'        <prebuild>CSCRIPT "$PROJ_DIR$\..\..\Config\RTL8195AM_PreBuild.vbs" "$PROJ_DIR$" "$PROJ_PATH$" "$CONFIG_NAME$"</prebuild>
'        <postbuild>CSCRIPT "$PROJ_DIR$\..\..\Config\RTL8195AM_PostBuild.vbs" "$PROJ_DIR$" "$TARGET_PATH$" "$CONFIG_NAME$"</postbuild>
'      </data>
'    </settings>
'    <settings>
'      <name>ILINK</name>
'      <archiveVersion>0</archiveVersion>
'      <data>
'        <option>
'          <name>IlinkConfigDefines</name>
'          <state>GEN_IMAGE=0</state>
'          <state>GEN_IMAGE=1</state>
'          <state>__GEN_IMAGE=1</state>
'          <state>__GEN_IMAGE__=1</state>
'        </option>
'     </settings>
'   </configuration>
' </project>
'===================================================================================================
Const ToolsFolderName = "Tools"
Const ConfigFolderName = "Config"
Const IAR_ICCARM_Define_FileName = "IAR_ICCARM_Define.h"
Const IAR_AARM_Define_FileName = "IAR_AARM_Define.h"
Const IAR_ILINK_Parameters_FileName = "IAR_ILINK_Parameters.icf"
Const IAR_CSPY_Parameters_FileName = "IAR_CSPY_Parameters.mac"
Const AutoGenDontTouch = "// Automatically generated content, Don't touch!"

' *.i79, *.menu
Const DN_RTL8710AF            = "#define RTL8710AF 0"
Const DN_RTL8711AF            = "#define RTL8711AF 1"
Const DN_RTL8711AM            = "#define RTL8711AM 2"
Const DN_RTL8195AM            = "#define RTL8195AM 3"

Const ICCARM_AARM_HAS_SDRAM_0 = "#define __HAS_SDRAM__ 0"
Const ICCARM_AARM_HAS_SDRAM_1 = "#define __HAS_SDRAM__ 1"
Const AARM_GEN_IMAGE_0        = "#define __GEN_IMAGE__ 0"
Const AARM_GEN_IMAGE_1        = "#define __GEN_IMAGE__ 1"
Const ILINK_HAS_SDRAM_0 = "define symbol __HAS_SDRAM__=0;"
Const ILINK_HAS_SDRAM_1 = "define symbol __HAS_SDRAM__=1;"
Const ILINK_GEN_IMAGE_0 = "define symbol __GEN_IMAGE__=0;"
Const ILINK_GEN_IMAGE_1 = "define symbol __GEN_IMAGE__=1;"
Const CSPY_HAS_SDRAM_0            = "__param HAS_SDRAM=0;"
Const CSPY_HAS_SDRAM_1            = "__param HAS_SDRAM=1;"
'===================================================================================================
Dim P_GEN_IMAGE    ' From Project.eww
Dim P_DEVICE_NAME  ' From Project.eww
Dim P_HAS_SDRAM    ' By Device Name
Dim F_DEVICE_NAME  ' From IAR_AARM_Define.h
Dim F_GEN_IMAGE    ' From IAR_AARM_Define.h
Dim F_HAS_SDRAM    ' From IAR_AARM_Define.h
' X:\Ameba\Projects\Application
Dim ProjectPath
' X:\Ameba\Projects\Application\Application.ewp
Dim ProjectFilePathName
' RAM or Flash
Dim ConfigurationName
Dim ConfigPath

' X:\Ameba\Config\IAR_ICCARM_Define_FileName
Dim IAR_ICCARM_Define_FilePathName
Dim IAR_AARM_Define_FilePathName
Dim IAR_ILINK_Parameters_FilePathName
Dim IAR_CSPY_Parameters_FilePathName

Dim SubString, Size, Pos, Pos0, Pos1
'===================================================================================================
Dim oShell
Dim oFileSystem
Dim oArgs, Var1, Var2, Var3, Var4, Var5, Var6, Var7, Var8, Var9

Const OverwriteExisting = TRUE
Const ForReading = 1, ForWriting = 2, ForAppending = 8
Const TristateUseDefault = -2, TristateTru = -1, TristateFalse = 0
Const WindowsFolder = 0, SystemFolder = 1, TemporaryFolder = 2
'===================================================================================================

Sub SetHasSDRAMByDeviceName
  If ( InStr(P_DEVICE_NAME, "RTL8195AM" ) > 0 ) _
  Or ( InStr(P_DEVICE_NAME, "RTL8711AM" ) > 0 ) Then
    P_HAS_SDRAM = 1
  Else
    P_HAS_SDRAM = 0
  End If
End Sub

Sub OnDeviceNameChanged()
  Make_IAR_ICCARM_Define_File()
  Make_IAR_AARM_Define_File()
  Make_IAR_ILINK_Parameters_File()
  Make_IAR_CSPY_Parameters_File()
End Sub

Sub OnILINKDefineChanged()
  if ( F_GEN_IMAGE <> P_GEN_IMAGE ) Then
    Make_IAR_AARM_Define_File()
    Make_IAR_ILINK_Parameters_File()
  End If
End Sub

'===================================================================================================
Sub SetupGlobalVars
  ProjectPath = Var1
  ProjectFilePathName = Var2
  ConfigurationName = Var3
  ConfigPath = ProjectPath & "\..\..\" & ConfigFolderName
  IAR_ICCARM_Define_FilePathName = ConfigPath  & "\" & IAR_ICCARM_Define_FileName
  IAR_AARM_Define_FilePathName = ConfigPath  & "\" & IAR_AARM_Define_FileName
  IAR_ILINK_Parameters_FilePathName = ConfigPath  & "\" & IAR_ILINK_Parameters_FileName
  IAR_CSPY_Parameters_FilePathName = ConfigPath  & "\" & IAR_CSPY_Parameters_FileName
End Sub

'===================================================================================================
Sub Make_IAR_ICCARM_Define_File()
  Dim oICCARM_DefineFile
  Set oICCARM_DefineFile = oFileSystem.CreateTextFile(IAR_ICCARM_Define_FilePathName, True, False)

  oICCARM_DefineFile.WriteLine AutoGenDontTouch
  oICCARM_DefineFile.WriteLine ""
  oICCARM_DefineFile.WriteLine "#ifndef __IAR_ICCARM_DEFINE__"
  oICCARM_DefineFile.WriteLine "#define __IAR_ICCARM_DEFINE__"
  oICCARM_DefineFile.WriteLine ""

  oICCARM_DefineFile.WriteLine DN_RTL8710AF
  oICCARM_DefineFile.WriteLine DN_RTL8711AF
  oICCARM_DefineFile.WriteLine DN_RTL8711AM
  oICCARM_DefineFile.WriteLine DN_RTL8195AM
  oICCARM_DefineFile.WriteLine ""

  oICCARM_DefineFile.WriteLine "#define __DEVICE_NAME__ " + P_DEVICE_NAME
  oICCARM_DefineFile.WriteLine ""

  If P_HAS_SDRAM = 1 Then
    oICCARM_DefineFile.WriteLine ICCARM_AARM_HAS_SDRAM_1
  Else
    oICCARM_DefineFile.WriteLine ICCARM_AARM_HAS_SDRAM_0
  End If
  oICCARM_DefineFile.WriteLine ""

  oICCARM_DefineFile.WriteLine "#endif /* __IAR_ICCARM_DEFINE__ */"

  oICCARM_DefineFile.Close

  Set oICCARM_DefineFile = Nothing
End Sub

'===================================================================================================
Sub Make_IAR_AARM_Define_File()
  Dim oAARM_DefineFile
  Set oAARM_DefineFile = oFileSystem.CreateTextFile(IAR_AARM_Define_FilePathName, True, False)

  oAARM_DefineFile.WriteLine AutoGenDontTouch
  oAARM_DefineFile.WriteLine ""

  oAARM_DefineFile.WriteLine "#ifndef __IAR_AARM_DEFINE__"
  oAARM_DefineFile.WriteLine "#define __IAR_AARM_DEFINE__"
  oAARM_DefineFile.WriteLine ""

  oAARM_DefineFile.WriteLine DN_RTL8710AF
  oAARM_DefineFile.WriteLine DN_RTL8711AF
  oAARM_DefineFile.WriteLine DN_RTL8711AM
  oAARM_DefineFile.WriteLine DN_RTL8195AM
  oAARM_DefineFile.WriteLine ""

  oAARM_DefineFile.WriteLine "#define __DEVICE_NAME__ " + P_DEVICE_NAME
  oAARM_DefineFile.WriteLine ""

  If P_HAS_SDRAM = 1 Then
    oAARM_DefineFile.WriteLine ICCARM_AARM_HAS_SDRAM_1
  Else
    oAARM_DefineFile.WriteLine ICCARM_AARM_HAS_SDRAM_0
  End If

  If P_GEN_IMAGE = 1 Then
    oAARM_DefineFile.WriteLine AARM_GEN_IMAGE_1
  Else
    oAARM_DefineFile.WriteLine AARM_GEN_IMAGE_0
  End If

  oAARM_DefineFile.WriteLine ""
  oAARM_DefineFile.WriteLine "#endif /* __IAR_AARM_DEFINE__ */"

  oAARM_DefineFile.Close

  Set oAARM_DefineFile = Nothing
End Sub

'===================================================================================================
Sub Make_IAR_ILINK_Parameters_File()
  Dim oILINK_ParametersFile
  Set oILINK_ParametersFile = oFileSystem.CreateTextFile(IAR_ILINK_Parameters_FilePathName, True, False)

  oILINK_ParametersFile.WriteLine AutoGenDontTouch
  oILINK_ParametersFile.WriteLine ""

  If P_HAS_SDRAM = 1 Then
    oILINK_ParametersFile.WriteLine ILINK_HAS_SDRAM_1
  Else
    oILINK_ParametersFile.WriteLine ILINK_HAS_SDRAM_0
  End If

  If P_GEN_IMAGE = 1 Then
    oILINK_ParametersFile.WriteLine ILINK_GEN_IMAGE_1
  Else
    oILINK_ParametersFile.WriteLine ILINK_GEN_IMAGE_0
  End If

  oILINK_ParametersFile.Close

  Set oILINK_ParametersFile = Nothing
End Sub

'===================================================================================================
Sub Make_IAR_CSPY_Parameters_File()
  Dim oCSPY_ParametersFile
  Set oCSPY_ParametersFile = oFileSystem.CreateTextFile(IAR_CSPY_Parameters_FilePathName, True, False)

  oCSPY_ParametersFile.WriteLine AutoGenDontTouch
  oCSPY_ParametersFile.WriteLine ""

  If P_HAS_SDRAM = 1 Then
    oCSPY_ParametersFile.WriteLine CSPY_HAS_SDRAM_1
  Else
    oCSPY_ParametersFile.WriteLine CSPY_HAS_SDRAM_0
  End If

  oCSPY_ParametersFile.Close

  Set oCSPY_ParametersFile = Nothing
End Sub

'===================================================================================================
Sub QueryInformationFromProjectFile()
  Dim oProjectFile
  Set oProjectFile = oFileSystem.OpenTextFile( ProjectFilePathName, ForReading )

  Dim ConfigurationSectionFound
  Dim ConfigurationNameMatched
  Dim OGChipSelectEditMenuHandled
  Dim IlinkConfigDefinesHandled

  ConfigurationSectionFound = False
  ConfigurationNameMatched = False
  OGChipSelectEditMenuHandled = False
  IlinkConfigDefinesHandled = False

  P_GEN_IMAGE = 0

  Dim strLine
  Do While oProjectFile.AtEndOfStream <> True

    strLine = oProjectFile.ReadLine

    If ConfigurationSectionFound = False Then
      Pos = Instr( strLine, "<configuration>" )
      If Pos > 0 Then
        ConfigurationSectionFound = True
      End If
    ElseIf ConfigurationNameMatched = False then
      Pos0 = Instr( strLine, "<name>" )
      Pos1 = Instr( strLine, "</name>" )
      If ( Pos0 > 0 ) And ( Pos1 > 0 ) Then
        Size = Pos1 - Pos0 - 6
        SubString = Mid( strLine, Pos0 + 6, Size )
        If ConfigurationName = SubString Then
          ConfigurationNameMatched = True
        Else
          ConfigurationSectionFound = False
        End If
      End If
    ElseIf OGChipSelectEditMenuHandled = False then
    ' ConfigurationNameMatched = True
      Pos = Instr( strLine, "<name>OGChipSelectEditMenu</name>" )
      If Pos > 0 Then
        Do While oProjectFile.AtEndOfStream <> True
          strLine = oProjectFile.ReadLine

          '<state>Default  None</state>
          '<state>TAG Display Name</state>
          Pos0 = Instr( strLine, "<state>" )
          Pos1 = Instr( strLine, "</state>" )
          If ( Pos0 > 0 ) And ( Pos1 > 0 ) Then
            Size = Pos1 - Pos0 - 7
            SubString = Mid( strLine, Pos0 + 7, Size )
            'Default[TAB]None
            Pos = Instr( SubString, vbTab )
            If Pos = 0 Then
              'TAG as Display Name
              Pos = Instr( SubString, " " )
            End If

            ' TAG as Display Name
            Size = Pos - 1
            P_DEVICE_NAME = Mid( SubString, 1, Size )
            OGChipSelectEditMenuHandled = True
            Exit Do
          End If
        Loop
      End If ' Instr( strLine, "<name>OGChipSelectEditMenu</name>" ) > 0
    ElseIf IlinkConfigDefinesHandled = False then
    ' OGChipSelectEditMenuHandled = True
      Pos = Instr( strLine, "<name>IlinkConfigDefines</name>" )
      If Pos > 0 Then
        Do While oProjectFile.AtEndOfStream <> True
          strLine = oProjectFile.ReadLine
          Pos0 = Instr( strLine, "<state>" )
          Pos1 = Instr( strLine, "</state>" )
          If ( Pos0 > 0 ) And ( Pos1 > 0 ) Then
            Size = Pos1 - Pos0 - 7
            ' <state></state> -- Nothing Defined
            If Size = 0 Then
              IlinkConfigDefinesHandled = True
              Exit Do
            End If
            ' <state>GEN_IMAGE=1</state>
            SubString = Mid( strLine, Pos0 + 7, Size )
            Pos = Instr( SubString, "GEN_IMAGE" )
            If Pos > 0 Then
              Pos = Instr( SubString, "0" )
              If Pos > 0 Then
                P_GEN_IMAGE = 0
              Else
                P_GEN_IMAGE = 1
              End If
              IlinkConfigDefinesHandled = True
              Exit Do
            End If
          End If
        Loop ' Do While oProjectFile.AtEndOfStream <> True
      End If
    Else
      Exit Do
    End If
  Loop

  oProjectFile.Close
  Set oProjectFile = Nothing
End Sub

'===================================================================================================
Sub QueryInformationFromAARM()
  Dim oAARMDefineFile
  Set oAARMDefineFile = oFileSystem.OpenTextFile( IAR_AARM_Define_FileName, ForReading )

  F_DEVICE_NAME = "Not_Available"
  F_GEN_IMAGE = 0
  F_HAS_SDRAM = 0

  Dim strLine
  Do While oAARMDefineFile.AtEndOfStream <> True
    strLine = oAARMDefineFile.ReadLine

    Pos = Instr( strLine, "__DEVICE_NAME__" )
    If Pos > 0 Then
      Pos = InStrRev( strLine, " " )
      Size = Len( strLine ) - Pos
      Pos = Pos + 1
      If Size > 0 Then
        F_DEVICE_NAME = Mid( strLine, Pos, Size)
      End If
    Else
      Pos = Instr( strLine, "__GEN_IMAGE__" )
      If Pos > 0 Then
        Pos = Instr( strLine, "0" )
        If Pos > 0 Then
          F_GEN_IMAGE = 0
        Else
          F_GEN_IMAGE = 1
        End If
      Else
        Pos = Instr( strLine, "__HAS_SDRAM__" )
        If Pos > 0 Then
          Pos = Instr( strLine, "0" )
          If Pos > 0 Then
            F_HAS_SDRAM = 0
          Else
            F_HAS_SDRAM = 1
          End If
        End If
      End If
    End If

  Loop 'Do While oAARMDefineFile.AtEndOfStream <> True

  oAARMDefineFile.Close
  Set oAARMDefineFile = Nothing
End Sub

'===================================================================================================
Sub Main()

  SetupGlobalVars()

  ' X:\Ameba\Config
  oShell.CurrentDirectory = ConfigPath

  ' P_DEVICE_NAME = XXXXXXXX
  Call QueryInformationFromProjectFile()

  Call SetHasSDRAMByDeviceName()

  If (  oFileSystem.FileExists( IAR_ICCARM_Define_FilePathName ) ) _
  AND ( oFileSystem.FileExists( IAR_AARM_Define_FilePathName ) ) _
  AND ( oFileSystem.FileExists( IAR_ILINK_Parameters_FilePathName ) ) _
  AND ( oFileSystem.FileExists( IAR_CSPY_Parameters_FilePathName ) ) Then
    ' F_DEVICE_NAME = XXXXXXXX
    QueryInformationFromAARM()
  Else
    F_DEVICE_NAME = "File_Not_Found"
  End If

  If ( F_DEVICE_NAME <> P_DEVICE_NAME ) _
  OR ( F_HAS_SDRAM <> P_HAS_SDRAM ) Then
    Call OnDeviceNameChanged()
    Exit Sub
  End If

  ' AASM and ILINK
  If ( F_GEN_IMAGE <> P_GEN_IMAGE ) Then
    Call OnILINKDefineChanged()
  End If

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

'===================================================================================================
Set oShell = WScript.CreateObject("WScript.Shell")
Set oFileSystem = Wscript.CreateObject("Scripting.FileSystemObject")
SetArgVars()
Main()
Set oFileSystem = Nothing
Set oShell = Nothing
WScript.Quit
'===================================================================================================
