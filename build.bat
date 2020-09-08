@echo off

set install_dir=C:\intelFPGA_lite\18.1\
set bin_tools=%install_dir%University_Program\Monitor_Program\arm_tools\baremetal\bin\
set quartus_tools=%install_dir%quartus\bin64\
set arm_tools=%install_dir%University_Program\Monitor_Program\arm_tools\

%bin_tools%arm-altera-eabi-gcc -Wall -c -std=c99 -g -mfloat-abi=soft -march=armv7-a -mtune=cortex-a9 -mcpu=cortex-a9 src/boot.c -o bin/os.c.o

IF %errorlevel% == 1 (
   exit
)

%bin_tools%arm-altera-eabi-gcc -Wl,--defsym  -Wl,arm_program_mem=0x0  -Wl,--defsym  -Wl,arm_available_mem_size=0x3ffffff8 -Wl,--defsym  -Wl,__cs3_stack=0x3ffffff8 -T"C:/intelFPGA_lite/20.1/University_Program/Monitor_Program/build/altera-socfpga-hosted.ld"  bin/os.c.o -o bin/os.axf

IF %errorlevel% == 1 (
   exit
)

%bin_tools%arm-altera-eabi-objcopy -O srec bin/os.axf bin/os.srec

IF %errorlevel% == 1 (
   exit
)

%bin_tools%arm-altera-eabi-nm -p bin/os.axf >nul 2>nul
%bin_tools%arm-altera-eabi-objdump -d -S "-M reg-names-std" bin/os.axf >nul 2>nul

%quartus_tools%quartus_pgm --quiet -c "DE-SoC [USB-1]" --auto >nul 2>nul
%quartus_tools%quartus_pgm --quiet -c "DE-SoC [USB-1]" -m jtag -o P;%install_dir%University_Program/Computer_Systems/DE1-SoC/DE1-SoC_Computer/verilog/DE1_SoC_Computer.sof@2 >nul 2>nul

start "" %bin_tools%arm-altera-eabi-gdb -ex "target remote localhost:3128"  -symbols bin/os.axf

%quartus_tools%quartus_hps --cable="DE-SoC [USB-1]" -o GDBSERVER --gdbport0=3128 --preloader=%arm_tools%u-boot-spl.de1-soc.srec --preloaderaddr=0xffff13a0 --source=bin/os.srec >nul 2>nul