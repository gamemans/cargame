################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CDDZGame.cpp \
../src/CMJGame.cpp \
../src/CMJUser.cpp \
../src/CPlayer.cpp \
../src/CServer.cpp \
../src/CTimer.cpp \
../src/main.cpp 

OBJS += \
./src/CDDZGame.o \
./src/CMJGame.o \
./src/CMJUser.o \
./src/CPlayer.o \
./src/CServer.o \
./src/CTimer.o \
./src/main.o 

CPP_DEPS += \
./src/CDDZGame.d \
./src/CMJGame.d \
./src/CMJUser.d \
./src/CPlayer.d \
./src/CServer.d \
./src/CTimer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../raknet_ex_4065 -I../include -I../../raknet_4065/include -I../../common -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


