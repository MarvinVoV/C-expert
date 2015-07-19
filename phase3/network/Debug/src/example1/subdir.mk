################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/example1/daytimetcpsrv.c 

OBJS += \
./src/example1/daytimetcpsrv.o 

C_DEPS += \
./src/example1/daytimetcpsrv.d 


# Each subdirectory must supply rules for building sources it contributes
src/example1/%.o: ../src/example1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


