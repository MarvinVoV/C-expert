################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lib/sun_io.c \
../src/lib/sun_linux.c \
../src/lib/sun_math.c \
../src/lib/sun_socket.c \
../src/lib/sun_stdio.c 

OBJS += \
./src/lib/sun_io.o \
./src/lib/sun_linux.o \
./src/lib/sun_math.o \
./src/lib/sun_socket.o \
./src/lib/sun_stdio.o 

C_DEPS += \
./src/lib/sun_io.d \
./src/lib/sun_linux.d \
./src/lib/sun_math.d \
./src/lib/sun_socket.d \
./src/lib/sun_stdio.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


