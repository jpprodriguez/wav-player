################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FW_DAC.c \
../Drivers/FW_DMA.c \
../Drivers/FW_Display7Seg.c \
../Drivers/FW_LCD.c \
../Drivers/FW_Teclado.c \
../Drivers/FW_Timer1.c \
../Drivers/FW_Timertick.c \
../Drivers/FW_UART1_RS232.c 

OBJS += \
./Drivers/FW_DAC.o \
./Drivers/FW_DMA.o \
./Drivers/FW_Display7Seg.o \
./Drivers/FW_LCD.o \
./Drivers/FW_Teclado.o \
./Drivers/FW_Timer1.o \
./Drivers/FW_Timertick.o \
./Drivers/FW_UART1_RS232.o 

C_DEPS += \
./Drivers/FW_DAC.d \
./Drivers/FW_DMA.d \
./Drivers/FW_Display7Seg.d \
./Drivers/FW_LCD.d \
./Drivers/FW_Teclado.d \
./Drivers/FW_Timer1.d \
./Drivers/FW_Timertick.d \
./Drivers/FW_UART1_RS232.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\FatFs library" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\CMSISv2p00_LPC17xx\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\LPC1769_DRIVERS\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\SD-MMC Drivers\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Includes" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Inicializacion_Kit" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


