################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MAB/uart.c \
../MAB/utils.c 

OBJS += \
./MAB/uart.o \
./MAB/utils.o 

C_DEPS += \
./MAB/uart.d \
./MAB/utils.d 


# Each subdirectory must supply rules for building sources it contributes
MAB/%.o: ../MAB/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -I"/home/mafish/workspace/MAB_UART_Node/Inc" -I"/home/mafish/workspace/MAB_UART_Node/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/home/mafish/workspace/MAB_UART_Node/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/home/mafish/workspace/MAB_UART_Node/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/mafish/workspace/MAB_UART_Node/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


