################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CNetApp.cpp \
../CTimer.cpp \
../robot.cpp 

OBJS += \
./CNetApp.o \
./CTimer.o \
./robot.o 

CPP_DEPS += \
./CNetApp.d \
./CTimer.d \
./robot.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../raknet_ex_4065 -I../../raknet_4065/include -I../../include -I../../common -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


