################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uc-bsp/bsp.c \
../uc-bsp/bsp_clock.c \
../uc-bsp/bsp_led.c \
../uc-bsp/bsp_os.c \
../uc-bsp/bsp_sdram.c \
../uc-bsp/bsp_tim.c \
../uc-bsp/bsp_uart.c \
../uc-bsp/cpu_bsp.c 

OBJS += \
./uc-bsp/bsp.o \
./uc-bsp/bsp_clock.o \
./uc-bsp/bsp_led.o \
./uc-bsp/bsp_os.o \
./uc-bsp/bsp_sdram.o \
./uc-bsp/bsp_tim.o \
./uc-bsp/bsp_uart.o \
./uc-bsp/cpu_bsp.o 

C_DEPS += \
./uc-bsp/bsp.d \
./uc-bsp/bsp_clock.d \
./uc-bsp/bsp_led.d \
./uc-bsp/bsp_os.d \
./uc-bsp/bsp_sdram.d \
./uc-bsp/bsp_tim.d \
./uc-bsp/bsp_uart.d \
./uc-bsp/cpu_bsp.d 


# Each subdirectory must supply rules for building sources it contributes
uc-bsp/%.o: ../uc-bsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:\Users\iysheng\workspace\chicken\core" -I"C:\Users\iysheng\workspace\chicken\hallib" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc\Legacy" -I"C:\Users\iysheng\workspace\chicken\uc-bsp" -I"C:\Users\iysheng\workspace\chicken\uc-config" -I"C:\Users\iysheng\workspace\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"C:\Users\iysheng\workspace\chicken\uC-CPU" -I"C:\Users\iysheng\workspace\chicken\uC-LIB" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Source" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


