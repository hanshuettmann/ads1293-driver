################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_Debounce.c \
../Drivers/API/Src/API_Delay.c \
../Drivers/API/Src/API_Uart.c 

OBJS += \
./Drivers/API/Src/API_Debounce.o \
./Drivers/API/Src/API_Delay.o \
./Drivers/API/Src/API_Uart.o 

C_DEPS += \
./Drivers/API/Src/API_Debounce.d \
./Drivers/API/Src/API_Delay.d \
./Drivers/API/Src/API_Uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"C:/Hans/UBA/CommProtocols/PdC_Workspace/Tp_SpiAds1293/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Hans/UBA/CommProtocols/PdC_Workspace/Tp_SpiAds1293/Drivers/CMSIS/Include" -I"C:/Hans/UBA/CommProtocols/PdC_Workspace/Tp_SpiAds1293/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Hans/UBA/CommProtocols/PdC_Workspace/Tp_SpiAds1293/Drivers/BSP/STM32F4xx_Nucleo_144" -I"C:/Hans/UBA/CommProtocols/PdC_Workspace/Tp_SpiAds1293/Drivers/Core/Inc" -I"C:/Hans/UBA/CommProtocols/PdC_Workspace/Tp_SpiAds1293/Drivers/API/Inc" -I"C:/Hans/UBA/CommProtocols/PdC_Workspace/Tp_SpiAds1293/Drivers/API/ADS1293/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_Debounce.d ./Drivers/API/Src/API_Debounce.o ./Drivers/API/Src/API_Debounce.su ./Drivers/API/Src/API_Delay.d ./Drivers/API/Src/API_Delay.o ./Drivers/API/Src/API_Delay.su ./Drivers/API/Src/API_Uart.d ./Drivers/API/Src/API_Uart.o ./Drivers/API/Src/API_Uart.su

.PHONY: clean-Drivers-2f-API-2f-Src

