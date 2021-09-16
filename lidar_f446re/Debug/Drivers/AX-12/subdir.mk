################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/AX-12/servoAX12.c 

OBJS += \
./Drivers/AX-12/servoAX12.o 

C_DEPS += \
./Drivers/AX-12/servoAX12.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/AX-12/servoAX12.o: ../Drivers/AX-12/servoAX12.c Drivers/AX-12/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Git Folder/lidar_ares_ensea/lidar_f446re/Drivers/VL53L0X_API/core/inc" -I"C:/Git Folder/lidar_ares_ensea/lidar_f446re/Drivers/VL53L0X_API/platform/inc" -I"C:/Git Folder/lidar_ares_ensea/lidar_f446re/Drivers/AX-12" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/AX-12/servoAX12.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

