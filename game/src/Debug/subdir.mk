################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CBase.cpp \
../CBaseGame.cpp \
../CBaseUser.cpp \
../CBaselist.cpp \
../CMJGame.cpp \
../CMJUser.cpp \
../CPlayer.cpp \
../CServer.cpp \
../CTimer.cpp \
../main.cpp 

OBJS += \
./CBase.o \
./CBaseGame.o \
./CBaseUser.o \
./CBaselist.o \
./CMJGame.o \
./CMJUser.o \
./CPlayer.o \
./CServer.o \
./CTimer.o \
./main.o 

CPP_DEPS += \
./CBase.d \
./CBaseGame.d \
./CBaseUser.d \
./CBaselist.d \
./CMJGame.d \
./CMJUser.d \
./CPlayer.d \
./CServer.d \
./CTimer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../raknet_4065 -I../../common -I/usr/include/libxml2 -I/home/aaaa/workspace/game/include -I../../raknet_ex_4065 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


