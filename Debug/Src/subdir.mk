################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/SF3.c \
../Src/gpio.c \
../Src/main.c \
../Src/spi.c \
../Src/spi_flash.c \
../Src/spiffs_cache.c \
../Src/spiffs_check.c \
../Src/spiffs_gc.c \
../Src/spiffs_hydrogen.c \
../Src/spiffs_nucleus.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/SF3.o \
./Src/gpio.o \
./Src/main.o \
./Src/spi.o \
./Src/spi_flash.o \
./Src/spiffs_cache.o \
./Src/spiffs_check.o \
./Src/spiffs_gc.o \
./Src/spiffs_hydrogen.o \
./Src/spiffs_nucleus.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/SF3.d \
./Src/gpio.d \
./Src/main.d \
./Src/spi.d \
./Src/spi_flash.d \
./Src/spiffs_cache.d \
./Src/spiffs_check.d \
./Src/spiffs_gc.d \
./Src/spiffs_hydrogen.d \
./Src/spiffs_nucleus.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' -DNO_TEST '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F429xx -I"C:/Users/Tomek/workspace/SPIFFS/Inc" -I"C:/Users/Tomek/workspace/SPIFFS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Tomek/workspace/SPIFFS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Tomek/workspace/SPIFFS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Tomek/workspace/SPIFFS/Drivers/CMSIS/Include" -I"C:/Users/Tomek/workspace/SPIFFS/Inc"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


