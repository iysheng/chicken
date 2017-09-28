################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uc-bsp/bsp.c \
../uc-bsp/bsp_adc.c \
../uc-bsp/bsp_beep.c \
../uc-bsp/bsp_clock.c \
../uc-bsp/bsp_led.c \
../uc-bsp/bsp_nand.c \
../uc-bsp/bsp_os.c \
../uc-bsp/bsp_rgb.c \
../uc-bsp/bsp_rtc.c \
../uc-bsp/bsp_sdcard.c \
../uc-bsp/bsp_sdram.c \
../uc-bsp/bsp_tim.c \
../uc-bsp/bsp_touch.c \
../uc-bsp/bsp_uart.c \
../uc-bsp/cpu_bsp.c \
../uc-bsp/pcf8574.c 

OBJS += \
./uc-bsp/bsp.o \
./uc-bsp/bsp_adc.o \
./uc-bsp/bsp_beep.o \
./uc-bsp/bsp_clock.o \
./uc-bsp/bsp_led.o \
./uc-bsp/bsp_nand.o \
./uc-bsp/bsp_os.o \
./uc-bsp/bsp_rgb.o \
./uc-bsp/bsp_rtc.o \
./uc-bsp/bsp_sdcard.o \
./uc-bsp/bsp_sdram.o \
./uc-bsp/bsp_tim.o \
./uc-bsp/bsp_touch.o \
./uc-bsp/bsp_uart.o \
./uc-bsp/cpu_bsp.o \
./uc-bsp/pcf8574.o 

C_DEPS += \
./uc-bsp/bsp.d \
./uc-bsp/bsp_adc.d \
./uc-bsp/bsp_beep.d \
./uc-bsp/bsp_clock.d \
./uc-bsp/bsp_led.d \
./uc-bsp/bsp_nand.d \
./uc-bsp/bsp_os.d \
./uc-bsp/bsp_rgb.d \
./uc-bsp/bsp_rtc.d \
./uc-bsp/bsp_sdcard.d \
./uc-bsp/bsp_sdram.d \
./uc-bsp/bsp_tim.d \
./uc-bsp/bsp_touch.d \
./uc-bsp/bsp_uart.d \
./uc-bsp/cpu_bsp.d \
./uc-bsp/pcf8574.d 


# Each subdirectory must supply rules for building sources it contributes
uc-bsp/%.o: ../uc-bsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -DARM_MATH_ROUNDING -DARM_MATH_MATRIX_CHECK -I"D:\Oxygen\chicken\core" -I"D:\Oxygen\chicken\hallib" -I"D:\Oxygen\chicken\hallib\Inc" -I"D:\Oxygen\chicken\hallib\Inc\Legacy" -I"D:\Oxygen\chicken\uc-bsp" -I"D:\Oxygen\chicken\uc-config" -I"D:\Oxygen\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"D:\Oxygen\chicken\uC-CPU" -I"D:\Oxygen\chicken\uC-LIB" -I"D:\Oxygen\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"D:\Oxygen\chicken\uCOS-III\Source" -I"D:\Oxygen\chicken\Config" -I"D:\Oxygen\chicken\GUI\inc" -I"D:\Oxygen\chicken\STM32_USB_Host_Library\Class\MSC\Inc" -I"D:\Oxygen\chicken\STM32_USB_Host_Library\Core\Inc" -I"D:\Oxygen\chicken\LWIP\lwip_app\web_server_demo" -I"D:\Oxygen\chicken\LWIP\lwip-1.4.1\src\include" -I"D:\Oxygen\chicken\LWIP\lwip_app\lwip_comm" -I"D:\Oxygen\chicken\LWIP" -I"D:\Oxygen\chicken\LWIP\lwip-1.4.1\src\include\ipv4" -I"D:\Oxygen\chicken\LWIP\LAN8720" -I"D:\Oxygen\chicken\LWIP\lwip-1.4.1\src\include\netif" -I"D:\Oxygen\chicken\LWIP\lwip_app" -I"D:\Oxygen\chicken\LWIP\lwip_app\tcp_server_demo" -I"D:\Oxygen\chicken\LWIP\lwip_app\tcp_client_demo" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


