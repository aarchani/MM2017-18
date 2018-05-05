################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/gpio.c \
../Src/main.c \
../Src/motors.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/adc.o \
./Src/gpio.o \
./Src/main.o \
./Src/motors.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/adc.d \
./Src/gpio.d \
./Src/main.d \
./Src/motors.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -DUSE_FULL_LL_DRIVER -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/CMSIS/Include" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


