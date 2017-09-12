################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../uC-LIB/Ports/ARM-Cortex-M4/GNU/lib_mem_a.S 

OBJS += \
./uC-LIB/Ports/ARM-Cortex-M4/GNU/lib_mem_a.o 

S_UPPER_DEPS += \
./uC-LIB/Ports/ARM-Cortex-M4/GNU/lib_mem_a.d 


# Each subdirectory must supply rules for building sources it contributes
uC-LIB/Ports/ARM-Cortex-M4/GNU/%.o: ../uC-LIB/Ports/ARM-Cortex-M4/GNU/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -x assembler-with-cpp -DUSE_HAL_DRIVER -DSTM32F767xx -I"D:\Oxygen\chicken\core" -I"D:\Oxygen\chicken\hallib" -I"D:\Oxygen\chicken\hallib\Inc" -I"D:\Oxygen\chicken\hallib\Inc\Legacy" -I"D:\Oxygen\chicken\uc-bsp" -I"D:\Oxygen\chicken\uc-config" -I"D:\Oxygen\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"D:\Oxygen\chicken\uC-CPU" -I"D:\Oxygen\chicken\uC-LIB" -I"D:\Oxygen\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"D:\Oxygen\chicken\uCOS-III\Source" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


