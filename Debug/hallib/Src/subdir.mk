################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hallib/Src/stm32f7xx_hal.c \
../hallib/Src/stm32f7xx_hal_adc.c \
../hallib/Src/stm32f7xx_hal_cortex.c \
../hallib/Src/stm32f7xx_hal_dma.c \
../hallib/Src/stm32f7xx_hal_dma2d.c \
../hallib/Src/stm32f7xx_hal_gpio.c \
../hallib/Src/stm32f7xx_hal_ltdc.c \
../hallib/Src/stm32f7xx_hal_pwr.c \
../hallib/Src/stm32f7xx_hal_pwr_ex.c \
../hallib/Src/stm32f7xx_hal_rcc.c \
../hallib/Src/stm32f7xx_hal_rcc_ex.c \
../hallib/Src/stm32f7xx_hal_sdram.c \
../hallib/Src/stm32f7xx_hal_tim.c \
../hallib/Src/stm32f7xx_hal_tim_ex.c \
../hallib/Src/stm32f7xx_hal_uart.c \
../hallib/Src/stm32f7xx_ll_fmc.c 

OBJS += \
./hallib/Src/stm32f7xx_hal.o \
./hallib/Src/stm32f7xx_hal_adc.o \
./hallib/Src/stm32f7xx_hal_cortex.o \
./hallib/Src/stm32f7xx_hal_dma.o \
./hallib/Src/stm32f7xx_hal_dma2d.o \
./hallib/Src/stm32f7xx_hal_gpio.o \
./hallib/Src/stm32f7xx_hal_ltdc.o \
./hallib/Src/stm32f7xx_hal_pwr.o \
./hallib/Src/stm32f7xx_hal_pwr_ex.o \
./hallib/Src/stm32f7xx_hal_rcc.o \
./hallib/Src/stm32f7xx_hal_rcc_ex.o \
./hallib/Src/stm32f7xx_hal_sdram.o \
./hallib/Src/stm32f7xx_hal_tim.o \
./hallib/Src/stm32f7xx_hal_tim_ex.o \
./hallib/Src/stm32f7xx_hal_uart.o \
./hallib/Src/stm32f7xx_ll_fmc.o 

C_DEPS += \
./hallib/Src/stm32f7xx_hal.d \
./hallib/Src/stm32f7xx_hal_adc.d \
./hallib/Src/stm32f7xx_hal_cortex.d \
./hallib/Src/stm32f7xx_hal_dma.d \
./hallib/Src/stm32f7xx_hal_dma2d.d \
./hallib/Src/stm32f7xx_hal_gpio.d \
./hallib/Src/stm32f7xx_hal_ltdc.d \
./hallib/Src/stm32f7xx_hal_pwr.d \
./hallib/Src/stm32f7xx_hal_pwr_ex.d \
./hallib/Src/stm32f7xx_hal_rcc.d \
./hallib/Src/stm32f7xx_hal_rcc_ex.d \
./hallib/Src/stm32f7xx_hal_sdram.d \
./hallib/Src/stm32f7xx_hal_tim.d \
./hallib/Src/stm32f7xx_hal_tim_ex.d \
./hallib/Src/stm32f7xx_hal_uart.d \
./hallib/Src/stm32f7xx_ll_fmc.d 


# Each subdirectory must supply rules for building sources it contributes
hallib/Src/%.o: ../hallib/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -DARM_MATH_ROUNDING -DARM_MATH_MATRIX_CHECK -I"D:\Oxygen\chicken\core" -I"D:\Oxygen\chicken\hallib" -I"D:\Oxygen\chicken\hallib\Inc" -I"D:\Oxygen\chicken\hallib\Inc\Legacy" -I"D:\Oxygen\chicken\uc-bsp" -I"D:\Oxygen\chicken\uc-config" -I"D:\Oxygen\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"D:\Oxygen\chicken\uC-CPU" -I"D:\Oxygen\chicken\uC-LIB" -I"D:\Oxygen\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"D:\Oxygen\chicken\uCOS-III\Source" -I"D:\Oxygen\chicken\Config" -I"D:\Oxygen\chicken\GUI\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


