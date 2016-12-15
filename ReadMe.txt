A. 首先运行 IAR.vbs 脚本
  1. 在IAR EWARM 安装文件夹创建 OutputJunction 到 系统临时文件夹(RAMDISK?), 用于保存生成的临时文件
  2. 复制 IAR 文件夹中的文件夹到IAR安装文件夹, 即用arm文件夹覆盖IAR安装文件夹中的arm文件夹.
B. 然后才可以打开工作区或者工程.

-------------------因为脚本执行和工程生成依赖文件夹结构, 请保持相同的文件夹结构!--------------------

Ameba
+--.gitignore                 Git 忽略文件
+--Ameba.eww                  Ameba工作区包含所有工程
+--IAR.vbs                    用于配置 IAR 的脚本
+--ReadMe.txt                 此文件
+--Common                     工程共用的文件：源代码, 头文件以及库文件等等
|   +--MCU                        RTL8195AM 等 CMSIS 支持文件以及外设驱动等等
|   +--Network                    lwIP 相关文件等等
|   +--RTOS                       CMSIS RTOS2 相关文件等等
|   +--......                     其他公用文件等等
|
+--Config                     工程共用配置文件：ICCARM, AARM, ILINK, CSPY, Build脚本等等
|   +--IAR_AARM_Define.h              RTL8195AM_PreBuild.vbs 生成, 用于 AARM 汇编
|   +--IAR_CSPY_Parameters.mac        RTL8195AM_PreBuild.vbs 生成, 用于 CSPY 调试
|   +--IAR_ICCARM_Define.h            RTL8195AM_PreBuild.vbs 生成, 用于 ICCARM 编译
|   +--IAR_ILINK_Parameters.icf       RTL8195AM_PreBuild.vbs 生成, 用于 ILINK 链接
|   +--RTL8195AM_ROM.txt              用于处理 rom.a 的符号导出的过滤器
|   +--RTL8195AM_ROM.bat              用于处理 rom.a 的符号导出, 生成 rtl8195am_rom.sym
|   +--RTL8195AM_ROM.icf              用于处理 rom.a 的链接配置, 生成 rtl8195am_rom.sym
|   +--RTL8195AM.icf                  链接配置文件, 引用 IAR_ILINK_Parameters.icf 的定义
|   +--RTL8195AM.mac                  CSPY调试文件, 引用 IAR_CSPY_Parameters.mac 的定义
|   +--RTL8195AM_SDRAM.mac            配置 RTL8195AM 以及 RTL8711AM 内部 SDRAM 的配置
|   +--RTL8195AM_PreBuild.vbs         用于编译之前生成头文件和配置参数文件
|   +--RTL8195AM_PostBuild.vbs        用于链接之后生产 .bin .hex 文件, 可用于JFlash烧录
|
+--IAR                        需要复制到IAR安装文件夹, 可以通过GUI选择MCU型号并选择相应的配置文件
|   +--arm
|       +--config
|           +--debugger
|           |   +--RealTek    RTL8195AM.ddf RTL8195AM.svd
|           +--devices
|               +--RealTek    RTL8xxxXX.i79 RTL8xxxXX.menu
|
+--Projects                   工程文件夹, 在此文件夹下面创建新工程, 可复制 Application 作为模板修改
|  |
|  +--Application             应用程序文件夹, *.ewp等等保存在此文件夹 --[0x9800B000]----- IMAGE2
|  |   +--Option              应用程序相关的配置文件夹, 配置MCU, Network, RTOS等等
|  |   +--Source              应用程序相关的源文件
|  |
|  +--Bootloader              烧录在Flash 0x98000000 处, 用于加载Appliction ------------- IMAGE1
|  |   +--Option
|  |   +--Source
|  |
|  +--Flashloader             用于IAR来烧录IMAGE1和IMAGE2到Flash
|  |   +--Option
|  |   +--Source
|  |
|  +--JFlashloader            用于JFlash来烧录整个Flash映像
|  |   +--Option
|  |   +--Source
|  |
|  +--ROMExporter             用于IAR, 生成包含rom.a所有符号的符号文件, 可以在源文件中引用
|      +--Option
|      +--Source
|
+--Tools                      相关工具文件, 用来生成配置文件, Flash映像等等


