################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include libs/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
tiny85-alarm.lss \

FLASH_IMAGE += \
tiny85-alarm.hex \

EEPROM_IMAGE += \
tiny85-alarm.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: tiny85-alarm.elf secondary-outputs

# Tool invocations
tiny85-alarm.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,tiny85-alarm.map -mmcu=attiny85 -o "tiny85-alarm.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

tiny85-alarm.lss: tiny85-alarm.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S tiny85-alarm.elf  >"tiny85-alarm.lss"
	@echo 'Finished building: $@'
	@echo ' '

tiny85-alarm.hex: tiny85-alarm.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex tiny85-alarm.elf  "tiny85-alarm.hex"
	@echo 'Finished building: $@'
	@echo ' '

tiny85-alarm.eep: tiny85-alarm.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex tiny85-alarm.elf  "tiny85-alarm.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: tiny85-alarm.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny85 tiny85-alarm.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) tiny85-alarm.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
