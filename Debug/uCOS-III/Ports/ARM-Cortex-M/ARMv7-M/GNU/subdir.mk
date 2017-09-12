################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_c.c 

S_UPPER_SRCS += \
../uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.S 

OBJS += \
./uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.o \
./uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_c.o 

S_UPPER_DEPS += \
./uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.d 

C_DEPS += \
./uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_c.d 


# Each subdirectory must supply rules for building sources it contributes
uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/%.o: ../uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -x assembler-with-cpp -DUSE_HAL_DRIVER -DSTM32F767xx -I"D:\Oxygen\chicken\core" -I"D:\Oxygen\chicken\hallib" -I"D:\Oxygen\chicken\hallib\Inc" -I"D:\Oxygen\chicken\hallib\Inc\Legacy" -I"D:\Oxygen\chicken\uc-bsp" -I"D:\Oxygen\chicken\uc-config" -I"D:\Oxygen\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"D:\Oxygen\chicken\uC-CPU" -I"D:\Oxygen\chicken\uC-LIB" -I"D:\Oxygen\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"D:\Oxygen\chicken\uCOS-III\Source" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/%.o: ../uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -DARM_MATH_ROUNDING -DARM_MATH_MATRIX_CHECK -I"D:\Oxygen\chicken\core" -I"D:\Oxygen\chicken\hallib" -I"D:\Oxygen\chicken\hallib\Inc" -I"D:\Oxygen\chicken\hallib\Inc\Legacy" -I"D:\Oxygen\chicken\uc-bsp" -I"D:\Oxygen\chicken\uc-config" -I"D:\Oxygen\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"D:\Oxygen\chicken\uC-CPU" -I"D:\Oxygen\chicken\uC-LIB" -I"D:\Oxygen\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"D:\Oxygen\chicken\uCOS-III\Source" -I"D:\Oxygen\chicken\Config" -I"D:\Oxygen\chicken\GUI\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


