::===================================================================================================
:: Option :: Build Actions :: Pre-build command line
::---------------------------------------------------------------------------------------------------
::$PROJ_DIR$\..\..\Config\RTL8195AM_ROM.bat "$PROJ_DIR$" "$TARGET_PATH$"

%1\..\..\Tools\isymexport.exe %2 %1\..\..\Common\MCU\rtl8195am_rom.sym --edit  %1\..\..\Config\RTL8195AM_ROM.txt
::%1\..\..\Tools\ielfdumparm.exe %2 -s .symtab -o %1\RTL8195AM_ROM.log
