################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Primitivas/PR_Display7Seg.c \
../Primitivas/PR_LCD.c \
../Primitivas/PR_Teclado.c \
../Primitivas/PR_UART1_RS232.c 

OBJS += \
./Primitivas/PR_Display7Seg.o \
./Primitivas/PR_LCD.o \
./Primitivas/PR_Teclado.o \
./Primitivas/PR_UART1_RS232.o 

C_DEPS += \
./Primitivas/PR_Display7Seg.d \
./Primitivas/PR_LCD.d \
./Primitivas/PR_Teclado.d \
./Primitivas/PR_UART1_RS232.d 


# Each subdirectory must supply rules for building sources it contributes
Primitivas/%.o: ../Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\FatFs library" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\CMSISv2p00_LPC17xx\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\LPC1769_DRIVERS\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\SD-MMC Drivers\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Includes" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Inicializacion_Kit" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


