################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/periph_init/adc.c \
../Src/periph_init/gpio.c \
../Src/periph_init/spi.c \
../Src/periph_init/stm32f4xx_hal_msp.c \
../Src/periph_init/stm32f4xx_it.c \
../Src/periph_init/system_stm32f4xx.c \
../Src/periph_init/tim.c 

OBJS += \
./Src/periph_init/adc.o \
./Src/periph_init/gpio.o \
./Src/periph_init/spi.o \
./Src/periph_init/stm32f4xx_hal_msp.o \
./Src/periph_init/stm32f4xx_it.o \
./Src/periph_init/system_stm32f4xx.o \
./Src/periph_init/tim.o 

C_DEPS += \
./Src/periph_init/adc.d \
./Src/periph_init/gpio.d \
./Src/periph_init/spi.d \
./Src/periph_init/stm32f4xx_hal_msp.d \
./Src/periph_init/stm32f4xx_it.d \
./Src/periph_init/system_stm32f4xx.d \
./Src/periph_init/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/periph_init/%.o: ../Src/periph_init/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F407xx -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Ayilay/Documents/SystemWorkbench/MicroMouse/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


