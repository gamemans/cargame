################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Base/CBase.cpp \
../Base/CBaseGame.cpp \
../Base/CBaseRoom.cpp \
../Base/CBaseTable.cpp \
../Base/CBaseUser.cpp \
../Base/CBaselist.cpp \
../Base/CDateTimeEx.cpp 

OBJS += \
./Base/CBase.o \
./Base/CBaseGame.o \
./Base/CBaseRoom.o \
./Base/CBaseTable.o \
./Base/CBaseUser.o \
./Base/CBaselist.o \
./Base/CDateTimeEx.o 

CPP_DEPS += \
./Base/CBase.d \
./Base/CBaseGame.d \
./Base/CBaseRoom.d \
./Base/CBaseTable.d \
./Base/CBaseUser.d \
./Base/CBaselist.d \
./Base/CDateTimeEx.d 


# Each subdirectory must supply rules for building sources it contributes
Base/%.o: ../Base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../raknet_ex_4065 -I../include -I../../raknet_4065/include -I../../common -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


