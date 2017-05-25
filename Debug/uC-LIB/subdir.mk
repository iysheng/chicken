################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uC-LIB/lib_ascii.c \
../uC-LIB/lib_math.c \
../uC-LIB/lib_mem.c \
../uC-LIB/lib_str.c 

OBJS += \
./uC-LIB/lib_ascii.o \
./uC-LIB/lib_math.o \
./uC-LIB/lib_mem.o \
./uC-LIB/lib_str.o 

C_DEPS += \
./uC-LIB/lib_ascii.d \
./uC-LIB/lib_math.d \
./uC-LIB/lib_mem.d \
./uC-LIB/lib_str.d 


# Each subdirectory must supply rules for building sources it contributes
uC-LIB/%.o: ../uC-LIB/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:\Users\iysheng\workspace\chicken\core" -I"C:\Users\iysheng\workspace\chicken\hallib" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc\Legacy" -I"C:\Users\iysheng\workspace\chicken\uc-bsp" -I"C:\Users\iysheng\workspace\chicken\uc-config" -I"C:\Users\iysheng\workspace\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"C:\Users\iysheng\workspace\chicken\uC-CPU" -I"C:\Users\iysheng\workspace\chicken\uC-LIB" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Source" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


