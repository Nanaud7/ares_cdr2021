################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/VL53L0X_API/platform/src/vl53l0x_platform.c 

OBJS += \
./Drivers/VL53L0X_API/platform/src/vl53l0x_platform.o 

C_DEPS += \
./Drivers/VL53L0X_API/platform/src/vl53l0x_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/VL53L0X_API/platform/src/%.o: ../Drivers/VL53L0X_API/platform/src/%.c Drivers/VL53L0X_API/platform/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303x8 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"E:/Git folder/ares_cdr2021/lidar_f303k8/Drivers/AX-12" -I"E:/Git folder/ares_cdr2021/lidar_f303k8/Drivers/VL53L0X_API/core/inc" -I"E:/Git folder/ares_cdr2021/lidar_f303k8/Drivers/VL53L0X_API/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

