################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../glm/glm/detail/dummy.cpp \
../glm/glm/detail/glm.cpp 

OBJS += \
./glm/glm/detail/dummy.o \
./glm/glm/detail/glm.o 

CPP_DEPS += \
./glm/glm/detail/dummy.d \
./glm/glm/detail/glm.d 


# Each subdirectory must supply rules for building sources it contributes
glm/glm/detail/%.o: ../glm/glm/detail/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


