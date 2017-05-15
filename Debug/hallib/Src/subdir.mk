################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hallib/Src/stm32f7xx_hal.c \
../hallib/Src/stm32f7xx_hal_adc.c \
../hallib/Src/stm32f7xx_hal_cortex.c \
../hallib/Src/stm32f7xx_hal_dma.c \
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
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:\Users\iysheng\workspace\chicken\core" -I"C:\Users\iysheng\workspace\chicken\hallib" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc" -I"C:\Users\iysheng\workspace\chicken\hallib\Inc\Legacy" -I"C:\Users\iysheng\workspace\chicken\uc-bsp" -I"C:\Users\iysheng\workspace\chicken\uc-config" -I"C:\Users\iysheng\workspace\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"C:\Users\iysheng\workspace\chicken\uC-CPU" -I"C:\Users\iysheng\workspace\chicken\uC-LIB" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"C:\Users\iysheng\workspace\chicken\uCOS-III\Source" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


