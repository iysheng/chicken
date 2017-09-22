################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include uc-config/subdir.mk
-include uc-bsp/subdir.mk
-include uCOS-III/Source/subdir.mk
-include uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/subdir.mk
-include uC-LIB/Ports/ARM-Cortex-M4/GNU/subdir.mk
-include uC-LIB/subdir.mk
-include uC-CPU/Cache/ARM/armv7m_generic_l1/subdir.mk
-include uC-CPU/ARM-Cortex-M4/GNU/subdir.mk
-include uC-CPU/subdir.mk
-include hallib/Src/subdir.mk
-include hallib/subdir.mk
-include core/subdir.mk
-include STM32_USB_Host_Library/Core/Src/subdir.mk
-include STM32_USB_Host_Library/Core/Inc/subdir.mk
-include STM32_USB_Host_Library/Class/MSC/Src/subdir.mk
-include GUI/Core/subdir.mk
-include Config/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
chicken.hex \

SECONDARY_SIZE += \
chicken.siz \


# All Target
all: chicken.elf secondary-outputs

# Tool invocations
chicken.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -T "D:\Oxygen\chicken\STM32F767ZITx_FLASH.ld" -Xlinker --gc-sections -L"D:\Oxygen\chicken\GUI\Core" -L"D:\Oxygen\chicken\core" -Wl,-Map,"chicken.map" -u _printf_float -u _scanf_float -specs=nosys.specs -o "chicken.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

chicken.hex: chicken.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "chicken.elf"  "chicken.hex"
	@echo 'Finished building: $@'
	@echo ' '

chicken.siz: chicken.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "chicken.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) chicken.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
