################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SD/FatFs\ library/option/ccsbcs.c 

OBJS += \
./Drivers/SD/FatFs\ library/option/ccsbcs.o 

C_DEPS += \
./Drivers/SD/FatFs\ library/option/ccsbcs.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SD/FatFs\ library/option/ccsbcs.o: ../Drivers/SD/FatFs\ library/option/ccsbcs.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\FatFs library" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\CMSISv2p00_LPC17xx\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\LPC1769_DRIVERS\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Drivers\SD\SD-MMC Drivers\inc" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Includes" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Inicializacion_Kit" -I"C:\Users\JuanPablo\Documents\LPCXpresso_6.1.4_194\workspace\Proyecto_Info2\Primitivas" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"Drivers/SD/FatFs library/option/ccsbcs.d" -MT"Drivers/SD/FatFs\ library/option/ccsbcs.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


