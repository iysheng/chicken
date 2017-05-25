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
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -x assembler-with-cpp -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:\Users\iysheng\workspace\chicken\core" -I"C:\Users\iysheng\workspace\chicken\hallib" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc\Legacy" -I"C:\Users\iysheng\workspace\chicken\uc-bsp" -I"C:\Users\iysheng\workspace\chicken\uc-config" -I"C:\Users\iysheng\workspace\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"C:\Users\iysheng\workspace\chicken\uC-CPU" -I"C:\Users\iysheng\workspace\chicken\uC-LIB" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Source" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/%.o: ../uCOS-III/Ports/ARM-Cortex-M/ARMv7-M/GNU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:\Users\iysheng\workspace\chicken\core" -I"C:\Users\iysheng\workspace\chicken\hallib" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc\Legacy" -I"C:\Users\iysheng\workspace\chicken\uc-bsp" -I"C:\Users\iysheng\workspace\chicken\uc-config" -I"C:\Users\iysheng\workspace\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"C:\Users\iysheng\workspace\chicken\uC-CPU" -I"C:\Users\iysheng\workspace\chicken\uC-LIB" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Source" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


