################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/first\ program.c 

C_DEPS += \
./src/first\ program.d 

OBJS += \
./src/first\ program.o 


# Each subdirectory must supply rules for building sources it contributes
src/first\ program.o: ../src/first\ program.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/first program.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/first\ program.d ./src/first\ program.o

.PHONY: clean-src

