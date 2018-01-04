################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CNetApp.cpp \
../src/CTimer.cpp \
../src/mjclient.cpp 

OBJS += \
./src/CNetApp.o \
./src/CTimer.o \
./src/mjclient.o 

CPP_DEPS += \
./src/CNetApp.d \
./src/CTimer.d \
./src/mjclient.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/aaaa/workspace/game/include -I/home/aaaa/workspace/game/raknetsdk64/include -I/home/aaaa/workspace/game/raknet64 -I/home/aaaa/workspace/game/common -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


