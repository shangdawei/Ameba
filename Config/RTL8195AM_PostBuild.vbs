'===================================================================================================
' Option :: Build Actions :: Pre-build command line
'---------------------------------------------------------------------------------------------------
' CSCRIPT "$PROJ_DIR$\..\..\Config\RTL8195AM_PostBuild.vbs" "$PROJ_DIR$" "$TARGET_PATH$" "$CONFIG_NAME$"
'
' X:\Ameba\Projects\Application                         "$PROJ_DIR$"       WScript.Arguments.Item(0)
' X:\Ameba\Projects\Application\...\Exe\Application.out "$TARGET_PATH$"    WScript.Arguments.Item(2)
' RAM                                                   "$CONFIG_NAME$"    WScript.Arguments.Item(2)
' Flash                                                 "$CONFIG_NAME$"    WScript.Arguments.Item(2)
'---------------------------------------------------------------------------------------------------
' Options :: Linker : Config : Configuration file symbol definitions:
'---------------------------------------------------------------------------------------------------
' GEN_IMAGE=0 : RAM Configuration -------- Do nothing
' GEN_IMAGE=1 : Flash Configuration ------ Generate .bin .hex
'+--------------------------------------------------------+--------+-------+--------------+--------+
'|BTL : |---SIGNATURE-----|----HEADER------|VECT - RO TAIL|        |       |              |        |
'|APP : |---SIGNATURE-----|----HEADER------|VECT - RO TAIL|---RW---|.......|HEAD RO  TAIL |---RW---|
'|HEX : |0x1000-0BA8      |0x1000-0BC8     |0x1000-0C00   |        |       |0x3000-0000   |        |
'|BIN : |0x0000-0000      |0x0000-0020     |0x0000-0058   |        |       |0x0000-0000   |        |
'+--------------------------------------------------------+--------+-------+--------------+--------+
'    SIGNATURE : 0x000 : 0x96969999 0xFC66CC3F 0x03CC33C0 0x6231DCE5
'       HEADER : 0x020 : RAM_SIZE, RAM_ADDR, SDR_START, SDR_END
'---------------------------------------------------------------------------------------------------
'
'===================================================================================================
Dim oShell
Dim oFileSystem
Dim oLogFile
Dim oCaptureFile
Dim CaptureFilePathName
Dim oArgs, Var1, Var2, Var3, Var4, Var5, Var6, Var7, Var8, Var9

Const OverwriteExisting = TRUE
Const ForReading = 1, ForWriting = 2, ForAppending = 8
Const TristateUseDefault = -2, TristateTru = -1, TristateFalse = 0
Const WindowsFolder = 0, SystemFolder = 1, TemporaryFolder = 2
'===================================================================================================

Const ComSpec = "%comspec% /c "
Const ToolsFolderName = "Tools"
Const ConfigFolderName = "Config"
Const SrecCatCmdLine = "srec_cat.exe"
Const BusyBoxCmdLine = "busybox.exe"
Const IElfToolCmdLine = "ielftool.exe"
Const IElfDumpArmCmdLine = "ielfdumparm.exe"

Const IAR_AARM_Define_FileName = "IAR_AARM_Define.h"


'===================================================================================================
' X:\Ameba\Projects\Application
Dim ProjectPath

' X:\Ameba\Tools
Dim ToolsPath

' X:\Ameba\Projects\Application\...\Exe\ : GetParentFolderName( TargetFilePathName )
Dim TargetFileParentFolderName

' RAM or Flash
Dim ConfigurationName

' Application     [.out] : GetBaseName( TargetFilePathName )
Dim TargetFileBaseName

' X:\Ameba\Tools\ielftool.exe
Dim IElfToolExeFilePathName

' X:\Ameba\Tools\ielfdumparm.exe
Dim IElfDumpArmExeFilePathName

' X:\Ameba\Tools\busybox.exe : busybox grep
Dim BusyBoxExeFilePathName

' X:\Ameba\Tools\srec_cat.exe
Dim SrecCatExeFilePathName

' X:\Ameba\Config\IAR_AARM_Define.h
Dim IAR_AARM_Define_FilePathName
Dim F_GEN_IMAGE    ' From IAR_AARM_Define.h

'===================================================================================================
' X:\Ameba\Projects\Application\...\Exe\Application.out
Dim TargetFilePathName

' TargetFileParentFolderName & TargetFileBaseName & ".hex"
' X:\Ameba\Projects\Application\...\Exe\Applicaton_Flash.hex
Dim HexOutFilePathName

' TargetFileParentFolderName & TargetFileBaseName & ".bin"
' X:\Ameba\Projects\Application\...\Exe\Applicaton_Flash.bin
Dim BinOutFilePathName

' TargetFileParentFolderName & TargetFileBaseName & ".log"
' X:\Ameba\Projects\Application\...\Exe\Applicaton_Flash.log
Dim LogOutFilePathName

Dim SegmentsInformationArray()
Dim SegmentsInformationCount
Dim SegmentsInformationIndex

'===================================================================================================

'---------------------------------------------------------------------------------------------------
' ielfdumparm.exe X:\Ameba\Projects\Application\...\Exe\Application.out
'---------------------------------------------------------------------------------------------------
'     2 program headers, each 32 bytes, at offset 0xcd70
'    16 section headers, each 40 bytes, at offset 0xcdb0
'  SEGMENTS:
'     Type Offset    Virtual   Physical File Sz Mem Sz Flags   Align
'     ---- ------    -------   -------- ------- ------ -----   -----
'  0: load   0x34 0x10000ba8 0x10000ba8    0x58   0x58 0x4   R   0x4
'  1: load   0x8c 0x10000c00 0x10000c00  0x29a0 0x29a0 0x5 X R   0x4
'---------------------------------------------------------------------------------------------------
'     3 program headers, each 32 bytes, at offset 0xce24
'    18 section headers, each 40 bytes, at offset 0xce84
'  SEGMENTS:
'     Type Offset    Virtual   Physical File Sz Mem Sz Flags   Align
'     ---- ------    -------   -------- ------- ------ -----   -----
'  0: load   0x34 0x10000ba8 0x10000ba8    0x58   0x58 0x4   R   0x4
' "0: load"   "34" "10000ba8" "10000ba8"    "58"   "58" "4   R"   "4"  <--- Split and Trim
'        0      1          2         3        4      5       6     7
'  1: load   0x8c 0x10000c00 0x10000c00  0x29a8 0x29a8 0x5 X R   0x4
'  2: load 0x2a34 0x301ffff0 0x301ffff0    0x10   0x10 0x5 X R   0x4
'---------------------------------------------------------------------------------------------------
Sub ExtractSegmentsInformation()
  Dim StrArray
  Dim strLine, SubString
  Dim Pos
  Dim Index
  Dim Size

  Call WriteLogFile("")
  Call WriteLogFile("====================================================================================================")
  Call WriteLogFile("Extract Information From Target File")
  Call WriteLogFile("====================================================================================================")
  Call WriteLogFile("")

  '-------------------------------------------------------------------------------------------------
  Call WriteLogFile("Uses ielfdumparm to dump target file")
  Call WriteLogFile("")

  Dim CommandLine
  CommandLine = Quotes( IElfDumpArmExeFilePathName )                    _
              & ASpace() & Quotes( TargetFilePathName )                 _
              & ASpace() & ">" & ASpace() & Quotes( NewCaptureFileName() )
  oShell.Run ComSpec & Quotes( CommandLine ), 0, True

  Call DumpCaptureFile( False ) ' Copy Capture File to Log File

  '-------------------------------------------------------------------------------------------------
  Call OpenCaptureFile()

  SegmentsInformationCount = 0
  Do While not EndOfCaptureFile()
    strLine = ReadCaptureFile()

    if SegmentsInformationCount = 0 Then
      Pos = InStr(strLine, "program headers")
      if Pos > 0 Then
        SubString = Mid( strLine, 1, Pos - 2)  ' [    2] program headers
        SubString = LTrim( SubString )
        SegmentsInformationCount = CInt(SubString)
        ReDim SegmentsInformationArray(SegmentsInformationCount-1, 3 ) ' UBound, not Count
      End If
    Else
      Pos = InStr(strLine, "load")
      if Pos > 0 Then
        Size = 0
        SegmentsInformationIndex = 0
        Do While SegmentsInformationIndex < SegmentsInformationCount
          StrArray = Split( strLine, "0x", 8)
          ' Physical FileSize Offset LastAddr [ = Physical + FileSize ]
          SegmentsInformationArray(SegmentsInformationIndex, 0) = CLng( "&H" & Trim( StrArray(3) ) )
          SegmentsInformationArray(SegmentsInformationIndex, 1) = CLng( "&H" & Trim( StrArray(4) ) )
          SegmentsInformationArray(SegmentsInformationIndex, 2) = _
          SegmentsInformationArray(SegmentsInformationIndex, 0) - Size
          SegmentsInformationArray(SegmentsInformationIndex, 3) = _
          SegmentsInformationArray(SegmentsInformationIndex, 0) + _
          SegmentsInformationArray(SegmentsInformationIndex, 1)

          Size = Size + SegmentsInformationArray(SegmentsInformationIndex, 1)
          SegmentsInformationIndex = SegmentsInformationIndex + 1
          strLine = ReadCaptureFile()
        Loop
        Exit Do
      End If
    End If
  Loop

  Call CloseCaptureFile( True )

  '-------------------------------------------------------------------------------------------------
  Call WriteLogFile("")
  Call WriteLogFile("----------------------------------------------------------------------------------------------------")
  Call WriteLogFile("Segment No. ==== Segment Start ===== Segment End ==== Segment Size ==== Segment Offset =============")
  Call WriteLogFile("----------------------------------------------------------------------------------------------------")

  Size = 0
  SegmentsInformationIndex = 0
  Do While SegmentsInformationIndex < SegmentsInformationCount
    strLine =           "        " & CStr( SegmentsInformationIndex + 1)
    strLine = strLine & "        0x" & Right( "00000000" & Hex( SegmentsInformationArray(SegmentsInformationIndex, 0) ), 8 )
    strLine = strLine & "          0x" & Right( "00000000" & Hex( SegmentsInformationArray(SegmentsInformationIndex, 3) ), 8 )
    strLine = strLine & "       0x" & Right( "00000000" & Hex( SegmentsInformationArray(SegmentsInformationIndex, 1) ), 8 )
    strLine = strLine & "        0x" & Right( "00000000" & Hex( Size ), 8 )
    Call WriteLogFile(strLine )

    Size = Size + SegmentsInformationArray(SegmentsInformationIndex, 1)
    SegmentsInformationIndex = SegmentsInformationIndex + 1
  Loop

  Call WriteLogFile("----------------------------------------------------------------------------------------------------")

  strLine = "                                                      " _
  & "0x" & Right( "00000000" & Hex( Size ), 8 ) _
  & "                              "
  Call WriteLogFile(strLine )
  Call WriteLogFile("")

End Sub

'---------------------------------------------------------------------------------------------------
' Make CRC32 for .out by ielftool.exe
' TargetFilePathName ---> TargetFilePathName
'---------------------------------------------------------------------------------------------------
Sub MakeTargetCRC32()
  Call WriteLogFile("")
  Call WriteLogFile("====================================================================================================")
  Call WriteLogFile("Uses ielftool to make crc32")
  Call WriteLogFile("====================================================================================================")
  Call WriteLogFile("")

  Dim CommandLine
  ' if SDRAM is absent then __sdram_checksum is in SRAM, Make __sdram_checksum at first
  CommandLine = Quotes( IElfToolExeFilePathName )                       _
              & ASpace() & Quotes( TargetFilePathName )                 _
              & ASpace() & Quotes( TargetFilePathName )                 _
              & ASpace() & "--verbose --checksum"                       _
              & ASpace() & "__sdram_checksum:4,crc32,0x0;__sdram_start-__sdram_checksum+0xFFFFFFFF" _
              & ASpace() & ">> " & Quotes( NewCaptureFileName() )
  oShell.Run ComSpec & Quotes( CommandLine ), 0, True
  Call DumpCaptureFile( True )

  ' Dont care where __sdram_checksum is, Make __image_checksum now
  CommandLine = Quotes( IElfToolExeFilePathName )                       _
              & ASpace() & Quotes( TargetFilePathName )                 _
              & ASpace() & Quotes( TargetFilePathName )                 _
              & ASpace() & "--verbose --checksum"                       _
              & ASpace() & "__image_checksum:4,crc32,0x0;__image_start-__image_checksum+0xFFFFFFFF" _
              & ASpace() & ">> " & Quotes( NewCaptureFileName()  )
  oShell.Run ComSpec & Quotes( CommandLine ), 0, True
  Call DumpCaptureFile( True )
End Sub

'---------------------------------------------------------------------------------------------------
' Generate .hex from .out by ielftool.exe
' TargetFilePathName ---> HexOutFilePathName
'---------------------------------------------------------------------------------------------------
Sub ConvertTarget2HexOut()
  Call WriteLogFile("")
  Call WriteLogFile("====================================================================================================")
  Call WriteLogFile("Uses ielftool to generate .hex")
  Call WriteLogFile("====================================================================================================")

  Dim CommandLine
  CommandLine = Quotes( IElfToolExeFilePathName )         _
              & ASpace() & "--ihex --verbose"             _
              & ASpace() & Quotes( TargetFilePathName )   _
              & ASpace() & Quotes( HexOutFilePathName )   _
              & ASpace() & ">> " & Quotes( NewCaptureFileName()  )

  oShell.Run ComSpec & Quotes( CommandLine ), 0, True
  Call DumpCaptureFile( True )
End Sub

'---------------------------------------------------------------------------------------------------
' Generate .bin from .hex by srec_cat.exe
' HexOutFilePathName ---> BinOutFilePathName
' Physical  FileSize Offset                       LastAddr [ = Physical + FileSize ]
'---------------------------------------------------------------------------------------------------
'0x10000ba8    0x58  0x10000ba8                   0x10000c00 = 0x10000c00 + 0x58
'0x10000c00  0x29a8  0x10000c00 + 0x58            0x100035A8 = 0x10000c00 + 0x29a8
'0x301ffff0    0x10  0x301ffff0 + 0x58 + 0x29A8   0x30200000 = 0x301ffff0 + 0x10
'---------------------------------------------------------------------------------------------------
Sub ConvertHexOut2BinOut()
  Call WriteLogFile("")
  Call WriteLogFile("====================================================================================================")
  Call WriteLogFile("Uses srec_cat to generate .bin")
  Call WriteLogFile("====================================================================================================")
  Call WriteLogFile("")

  Dim strLine
  Dim CommandLine

  strLine = Quotes( SrecCatExeFilePathName )
  Call WriteLogFile(strLine)

  CommandLine = strLine

  SegmentsInformationIndex = 0
  Do While SegmentsInformationIndex < SegmentsInformationCount
    strLine = ASpace()                                                              _
    & ASpace() & Quotes( HexOutFilePathName )                                       _
    & ASpace() & "-intel"

    Call WriteLogFile(strLine)
    CommandLine = CommandLine & strLine

    strLine = ASpace()                                                                                            _
    & ASpace() & "-Crop"                                                                                          _
    & ASpace() & "0x" & Right( "00000000" & Hex( SegmentsInformationArray(SegmentsInformationIndex, 0) ), 8 )     _
    & ASpace() & "0x" & Right( "00000000" & Hex( SegmentsInformationArray(SegmentsInformationIndex, 3) ), 8 )     _
    & ASpace() & "-offset"                                                                                        _
    & ASpace() & "-" & "0x" & Right( "00000000" & Hex( SegmentsInformationArray(SegmentsInformationIndex, 2) ), 8 )

    Call WriteLogFile(strLine)
    CommandLine = CommandLine & strLine

    SegmentsInformationIndex = SegmentsInformationIndex + 1
  Loop

  strLine = ASpace()                          _
  & ASpace() & "-output"                      _
  & ASpace() & Quotes( BinOutFilePathName )   _
  & ASpace() & "-binary"
  Call WriteLogFile(strLine)
  CommandLine = CommandLine & strLine

  oShell.Run ComSpec & Quotes( CommandLine ), 0, True
End Sub

'===================================================================================================
Sub SetupGlobalVars
  ProjectPath = Var1
  TargetFilePathName = Var2
  ConfigurationName = Var3

  ToolsPath = ProjectPath & "\..\..\" & ToolsFolderName
  ConfigPath = ProjectPath & "\..\..\" & ConfigFolderName
  IAR_AARM_Define_FilePathName = ConfigPath  & "\" & IAR_AARM_Define_FileName

  TargetFileParentFolderName = oFileSystem.GetParentFolderName( TargetFilePathName )
  TargetFileBaseName = oFileSystem.GetBaseName( TargetFilePathName )
  HexOutFilePathName = TargetFileParentFolderName & "\" & TargetFileBaseName & ".hex"
  BinOutFilePathName = TargetFileParentFolderName & "\" & TargetFileBaseName & ".bin"
  LogOutFilePathName = TargetFileParentFolderName & "\" & TargetFileBaseName & ".log"

  SrecCatExeFilePathName = ToolsPath & "\" & SrecCatCmdLine
  IElfToolExeFilePathName = ToolsPath & "\" & IElfToolCmdLine
  BusyBoxExeFilePathName = ToolsPath & "\" & BusyBoxCmdLine
  IElfDumpArmExeFilePathName = ToolsPath & "\" & IElfDumpArmCmdLine

End Sub

'===================================================================================================
Sub QueryInformationFromAARM()
  Dim oAARMDefineFile
  Set oAARMDefineFile = oFileSystem.OpenTextFile( IAR_AARM_Define_FilePathName, ForReading )

  F_DEVICE_NAME = "Not_Available"
  F_GEN_IMAGE = 0

  Dim strLine
  Do While oAARMDefineFile.AtEndOfStream <> True
    strLine = oAARMDefineFile.ReadLine

    Pos = Instr( strLine, "__GEN_IMAGE__" )
    If Pos > 0 Then
      Pos = Instr( strLine, "0" )
      If Pos > 0 Then
        F_GEN_IMAGE = 0
      Else
        F_GEN_IMAGE = 1
      End If
    End If

  Loop 'Do While oAARMDefineFile.AtEndOfStream <> True

  oAARMDefineFile.Close
  Set oAARMDefineFile = Nothing
End Sub

'===================================================================================================
Sub Main()

  Call SetupGlobalVars()

  Call QueryInformationFromAARM() 'Find GEN_IMAGE
  If F_GEN_IMAGE = 0 Then         'Not found
    Exit Sub                      'Do nothing
  End If

  oShell.CurrentDirectory = TargetFileParentFolderName

  Call CreateLogFile( LogOutFilePathName )
  Call WriteLogFile( "================================ Post-Build Action Start ===========================================" )

  Call ExtractSegmentsInformation()

  ' Make CRC32 for .out by ielftool.exe
  ' TargetFilePathName ---> TargetFilePathName
  Call MakeTargetCRC32()

  ' Generate .hex from .out by ielftool.exe
  ' TargetFilePathName ---> HexOutFilePathName
  Call ConvertTarget2HexOut()

  ' Generate .bin from .hex by srec_cat.exe
  ' HexOutFilePathName ---> BinOutFilePathName
  Call ConvertHexOut2BinOut()

  Call WriteLogFile ( "================================ Post-Build Action Start ==========================================="  )
  Call CloseLogFile()

End Sub

'===================================================================================================
Function GetTempFolder()
  Dim strTempFolder
  ' Set strTempFolder = oFileSystem.GetSpecialFolder(TemporaryFolder)
  strTempFolder = oShell.ExpandEnvironmentStrings("%Temp%")
  GetTempFolder = strTempFolder
  ' C:\Windows\Temp
End Function

'===================================================================================================
Function GetTempFilePathName()
  Dim strTempFilePathName
  strTempFilePathName =  GetTempFolder & "\" & oFileSystem.GetTempName
  GetTempFilePathName = strTempFilePathName
End Function

'===================================================================================================
Function ASpace()
    ASpace = Space(1)
End Function

'===================================================================================================
Function Quotes(ByVal strValue)
    Quotes = Chr(34) & strValue & Chr(34)
End Function

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
Sub CreateLogFile( LogFilePathName )
  Set oLogFile = oFileSystem.CreateTextFile(LogFilePathName, True, False)
End Sub

Sub WriteLogFile( Text )
  oLogFile.WriteLine Text
End Sub

Sub CloseLogFile( )
  oLogFile.Close
  Set oLogFile = Nothing
End Sub

'===================================================================================================
Function NewCaptureFileName()
  CaptureFilePathName = GetTempFilePathName() ' May be read late
  NewCaptureFileName = CaptureFilePathName
End Function

Sub DumpCaptureFile( DeleteIt )
  Call OpenCaptureFile()

  Do While not EndOfCaptureFile()
    Call WriteLogFile( ReadCaptureFile() )
  Loop

  Call CloseCaptureFile( DeleteIt )
End Sub

Sub OpenCaptureFile()
  Set oCaptureFile = oFileSystem.OpenTextFile(CaptureFilePathName, ForReading)
End Sub

Function EndOfCaptureFile()
  EndOfCaptureFile = oCaptureFile.AtEndOfStream
End Function

Function ReadCaptureFile()
  ReadCaptureFile = oCaptureFile.ReadLine
End Function

Sub CloseCaptureFile( DeleteIt )
  oCaptureFile.Close
  Set oCaptureFile = Nothing
  if DeleteIt = True then
    DeleteCaptureFile()
  End if
End Sub

Sub DeleteCaptureFile()
  oFileSystem.DeleteFile CaptureFilePathName
End Sub

'===================================================================================================
'
Set oShell = WScript.CreateObject("WScript.Shell")
Set oFileSystem = Wscript.CreateObject("Scripting.FileSystemObject")
SetArgVars()

Main()

Set oFileSystem = Nothing
Set oShell = Nothing
WScript.Quit
'===================================================================================================
