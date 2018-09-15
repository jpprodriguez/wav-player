################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_clkpwr.c \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_gpio.c \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_libcfg_default.c \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_pinsel.c \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_rtc.c \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_ssp.c \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_systick.c \
../Drivers/SD/LPC17xx_drivers/src/lpc17xx_timer.c 

OBJS += \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_clkpwr.o \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_gpio.o \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_libcfg_default.o \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_pinsel.o \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_rtc.o \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_ssp.o \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_systick.o \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_timer.o 

C_DEPS += \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_clkpwr.d \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_gpio.d \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_libcfg_default.d \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_pinsel.d \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_rtc.d \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_ssp.d \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_systick.d \
./Drivers/SD/LPC17xx_drivers/src/lpc17xx_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SD/LPC17xx_drivers/src/%.o: ../Drivers/SD/LPC17xx_drivers/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -I"C:\Documents and Settings\Juan Pablo\My Documents\LPCXpresso_6.0.4_159\workspace\Proyecto_Info2\Drivers\SD\LPC17xx_drivers\inc" -I"C:\Documents and Settings\Juan Pablo\My Documents\LPCXpresso_6.0.4_159\workspace\Proyecto_Info2\Drivers\SD\FatFs library" -I"../Proyecto_Info2/CMSISv2p00_LPC17xx/inc" -I"../Proyecto_Info2/Proyecto_Info2/Drivers/SD/SD-MMC Drivers/inc" -I"../Proyecto_Info2/Proyecto_Info2/Aplicacion" -I"../Proyecto_Info2/Proyecto_Info2/Includes" -I"../Proyecto_Info2/Proyecto_Info2/Primitivas" -I"../Proyecto_Info2/Proyecto_Info2/Drivers" -I"../Proyecto_Info2/Proyecto_Info2/Inicializacion_Kit" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


