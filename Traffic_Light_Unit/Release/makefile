################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Traffic_Light_Unit.lss \

FLASH_IMAGE += \
Traffic_Light_Unit.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Traffic_Light_Unit.elf secondary-outputs

# Tool invocations
Traffic_Light_Unit.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Traffic_Light_Unit.map -mmcu=atmega32 -o "Traffic_Light_Unit.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Traffic_Light_Unit.lss: Traffic_Light_Unit.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Traffic_Light_Unit.elf  >"Traffic_Light_Unit.lss"
	@echo 'Finished building: $@'
	@echo ' '

Traffic_Light_Unit.hex: Traffic_Light_Unit.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Traffic_Light_Unit.elf  "Traffic_Light_Unit.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Traffic_Light_Unit.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Traffic_Light_Unit.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Traffic_Light_Unit.elf
	@echo 'Invoking: AVRDude'
	C:\IMT_SDK_Win_64\WinAVR\bin\avrdude -pm32 -cusbasp -Uflash:w:Traffic_Light_Unit.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Traffic_Light_Unit.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
