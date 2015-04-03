################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ImageMeshConvertor.cpp \
../Line2.cpp \
../Main.cpp \
../Mesh.cpp \
../Vector2.cpp \
../Vector3.cpp 

OBJS += \
./ImageMeshConvertor.o \
./Line2.o \
./Main.o \
./Mesh.o \
./Vector2.o \
./Vector3.o 

CPP_DEPS += \
./ImageMeshConvertor.d \
./Line2.d \
./Main.d \
./Mesh.d \
./Vector2.d \
./Vector3.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


