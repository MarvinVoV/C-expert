################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/example2/tcpcli01.c \
../src/example2/tcpserv01.c 

OBJS += \
./src/example2/tcpcli01.o \
./src/example2/tcpserv01.o 

C_DEPS += \
./src/example2/tcpcli01.d \
./src/example2/tcpserv01.d 


# Each subdirectory must supply rules for building sources it contributes
src/example2/%.o: ../src/example2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


