################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/readline.c \
../src/lib/readn.c \
../src/lib/writen.c 

OBJS += \
./src/lib/readline.o \
./src/lib/readn.o \
./src/lib/writen.o 

C_DEPS += \
./src/lib/readline.d \
./src/lib/readn.d \
./src/lib/writen.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


