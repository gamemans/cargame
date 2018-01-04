################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ddz/ddzgame.cpp \
../ddz/ddzroom.cpp \
../ddz/ddztable.cpp 

OBJS += \
./ddz/ddzgame.o \
./ddz/ddzroom.o \
./ddz/ddztable.o 

CPP_DEPS += \
./ddz/ddzgame.d \
./ddz/ddzroom.d \
./ddz/ddztable.d 


# Each subdirectory must supply rules for building sources it contributes
ddz/%.o: ../ddz/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../../raknet_ex_4065 -I../include -I../../raknet_4065/include -I../../common -I/usr/include/libxml2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


