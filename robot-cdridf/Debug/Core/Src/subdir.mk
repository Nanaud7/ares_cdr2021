################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AX12.c \
../Core/Src/DRV8825.c \
../Core/Src/HC-SR04.c \
../Core/Src/actionneurs.c \
../Core/Src/adc.c \
../Core/Src/asservissement.c \
../Core/Src/gpio.c \
../Core/Src/ihm.c \
../Core/Src/lidar.c \
../Core/Src/main.c \
../Core/Src/moteurs.c \
../Core/Src/odometrie.c \
../Core/Src/retarget.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/strategie.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/AX12.o \
./Core/Src/DRV8825.o \
./Core/Src/HC-SR04.o \
./Core/Src/actionneurs.o \
./Core/Src/adc.o \
./Core/Src/asservissement.o \
./Core/Src/gpio.o \
./Core/Src/ihm.o \
./Core/Src/lidar.o \
./Core/Src/main.o \
./Core/Src/moteurs.o \
./Core/Src/odometrie.o \
./Core/Src/retarget.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/strategie.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/AX12.d \
./Core/Src/DRV8825.d \
./Core/Src/HC-SR04.d \
./Core/Src/actionneurs.d \
./Core/Src/adc.d \
./Core/Src/asservissement.d \
./Core/Src/gpio.d \
./Core/Src/ihm.d \
./Core/Src/lidar.d \
./Core/Src/main.d \
./Core/Src/moteurs.d \
./Core/Src/odometrie.d \
./Core/Src/retarget.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/strategie.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

