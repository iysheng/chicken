################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uCOS-III/Source/os_cfg_app.c \
../uCOS-III/Source/os_core.c \
../uCOS-III/Source/os_dbg.c \
../uCOS-III/Source/os_flag.c \
../uCOS-III/Source/os_mem.c \
../uCOS-III/Source/os_mon.c \
../uCOS-III/Source/os_msg.c \
../uCOS-III/Source/os_mutex.c \
../uCOS-III/Source/os_prio.c \
../uCOS-III/Source/os_q.c \
../uCOS-III/Source/os_sem.c \
../uCOS-III/Source/os_stat.c \
../uCOS-III/Source/os_task.c \
../uCOS-III/Source/os_tick.c \
../uCOS-III/Source/os_time.c \
../uCOS-III/Source/os_tmr.c \
../uCOS-III/Source/os_var.c 

OBJS += \
./uCOS-III/Source/os_cfg_app.o \
./uCOS-III/Source/os_core.o \
./uCOS-III/Source/os_dbg.o \
./uCOS-III/Source/os_flag.o \
./uCOS-III/Source/os_mem.o \
./uCOS-III/Source/os_mon.o \
./uCOS-III/Source/os_msg.o \
./uCOS-III/Source/os_mutex.o \
./uCOS-III/Source/os_prio.o \
./uCOS-III/Source/os_q.o \
./uCOS-III/Source/os_sem.o \
./uCOS-III/Source/os_stat.o \
./uCOS-III/Source/os_task.o \
./uCOS-III/Source/os_tick.o \
./uCOS-III/Source/os_time.o \
./uCOS-III/Source/os_tmr.o \
./uCOS-III/Source/os_var.o 

C_DEPS += \
./uCOS-III/Source/os_cfg_app.d \
./uCOS-III/Source/os_core.d \
./uCOS-III/Source/os_dbg.d \
./uCOS-III/Source/os_flag.d \
./uCOS-III/Source/os_mem.d \
./uCOS-III/Source/os_mon.d \
./uCOS-III/Source/os_msg.d \
./uCOS-III/Source/os_mutex.d \
./uCOS-III/Source/os_prio.d \
./uCOS-III/Source/os_q.d \
./uCOS-III/Source/os_sem.d \
./uCOS-III/Source/os_stat.d \
./uCOS-III/Source/os_task.d \
./uCOS-III/Source/os_tick.d \
./uCOS-III/Source/os_time.d \
./uCOS-III/Source/os_tmr.d \
./uCOS-III/Source/os_var.d 


# Each subdirectory must supply rules for building sources it contributes
uCOS-III/Source/%.o: ../uCOS-III/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wall  -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -D__FPU_PRESENT=1 -DARM_MATH_CM7 -DARM_MATH_ROUNDING -DARM_MATH_MATRIX_CHECK -I"D:\Oxygen\chicken\core" -I"D:\Oxygen\chicken\hallib" -I"D:\Oxygen\chicken\hallib\Inc" -I"D:\Oxygen\chicken\hallib\Inc\Legacy" -I"D:\Oxygen\chicken\uc-bsp" -I"D:\Oxygen\chicken\uc-config" -I"D:\Oxygen\chicken\uC-CPU\ARM-Cortex-M4\GNU" -I"D:\Oxygen\chicken\uC-CPU" -I"D:\Oxygen\chicken\uC-LIB" -I"D:\Oxygen\chicken\uCOS-III\Ports\ARM-Cortex-M\ARMv7-M\GNU" -I"D:\Oxygen\chicken\uCOS-III\Source" -I"D:\Oxygen\chicken\Config" -I"D:\Oxygen\chicken\GUI\inc" -I"D:\Oxygen\chicken\STM32_USB_Host_Library\Class\MSC\Inc" -I"D:\Oxygen\chicken\STM32_USB_Host_Library\Core\Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


