################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/signal/abortsignal.c 

OBJS += \
./src/signal/abortsignal.o 

C_DEPS += \
./src/signal/abortsignal.d 


# Each subdirectory must supply rules for building sources it contributes
src/signal/%.o: ../src/signal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


