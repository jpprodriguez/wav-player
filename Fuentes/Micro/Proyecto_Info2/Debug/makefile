################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Primitivas/subdir.mk
-include Inicializacion_Kit/subdir.mk
-include Drivers/SD/SD-MMC\ Drivers/src/subdir.mk
-include Drivers/SD/LPC1769_DRIVERS/src/subdir.mk
-include Drivers/SD/FatFs\ library/option/subdir.mk
-include Drivers/SD/FatFs\ library/hardware/subdir.mk
-include Drivers/SD/FatFs\ library/subdir.mk
-include Drivers/subdir.mk
-include Aplicacion/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Proyecto_Info2.axf

# Tool invocations
Proyecto_Info2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="Proyecto_Info2.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Proyecto_Info2_Debug.ld" -o "Proyecto_Info2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Proyecto_Info2.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Proyecto_Info2.axf"; # arm-none-eabi-objcopy -O binary "Proyecto_Info2.axf" "Proyecto_Info2.bin" ; checksum -p LPC1769 -d "Proyecto_Info2.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
