################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../glm/test/gtc/gtc_bitfield.cpp \
../glm/test/gtc/gtc_constants.cpp \
../glm/test/gtc/gtc_epsilon.cpp \
../glm/test/gtc/gtc_integer.cpp \
../glm/test/gtc/gtc_matrix_access.cpp \
../glm/test/gtc/gtc_matrix_integer.cpp \
../glm/test/gtc/gtc_matrix_inverse.cpp \
../glm/test/gtc/gtc_matrix_transform.cpp \
../glm/test/gtc/gtc_noise.cpp \
../glm/test/gtc/gtc_packing.cpp \
../glm/test/gtc/gtc_quaternion.cpp \
../glm/test/gtc/gtc_random.cpp \
../glm/test/gtc/gtc_reciprocal.cpp \
../glm/test/gtc/gtc_round.cpp \
../glm/test/gtc/gtc_type_precision.cpp \
../glm/test/gtc/gtc_type_ptr.cpp \
../glm/test/gtc/gtc_ulp.cpp \
../glm/test/gtc/gtc_user_defined_types.cpp \
../glm/test/gtc/gtc_vec1.cpp 

OBJS += \
./glm/test/gtc/gtc_bitfield.o \
./glm/test/gtc/gtc_constants.o \
./glm/test/gtc/gtc_epsilon.o \
./glm/test/gtc/gtc_integer.o \
./glm/test/gtc/gtc_matrix_access.o \
./glm/test/gtc/gtc_matrix_integer.o \
./glm/test/gtc/gtc_matrix_inverse.o \
./glm/test/gtc/gtc_matrix_transform.o \
./glm/test/gtc/gtc_noise.o \
./glm/test/gtc/gtc_packing.o \
./glm/test/gtc/gtc_quaternion.o \
./glm/test/gtc/gtc_random.o \
./glm/test/gtc/gtc_reciprocal.o \
./glm/test/gtc/gtc_round.o \
./glm/test/gtc/gtc_type_precision.o \
./glm/test/gtc/gtc_type_ptr.o \
./glm/test/gtc/gtc_ulp.o \
./glm/test/gtc/gtc_user_defined_types.o \
./glm/test/gtc/gtc_vec1.o 

CPP_DEPS += \
./glm/test/gtc/gtc_bitfield.d \
./glm/test/gtc/gtc_constants.d \
./glm/test/gtc/gtc_epsilon.d \
./glm/test/gtc/gtc_integer.d \
./glm/test/gtc/gtc_matrix_access.d \
./glm/test/gtc/gtc_matrix_integer.d \
./glm/test/gtc/gtc_matrix_inverse.d \
./glm/test/gtc/gtc_matrix_transform.d \
./glm/test/gtc/gtc_noise.d \
./glm/test/gtc/gtc_packing.d \
./glm/test/gtc/gtc_quaternion.d \
./glm/test/gtc/gtc_random.d \
./glm/test/gtc/gtc_reciprocal.d \
./glm/test/gtc/gtc_round.d \
./glm/test/gtc/gtc_type_precision.d \
./glm/test/gtc/gtc_type_ptr.d \
./glm/test/gtc/gtc_ulp.d \
./glm/test/gtc/gtc_user_defined_types.d \
./glm/test/gtc/gtc_vec1.d 


# Each subdirectory must supply rules for building sources it contributes
glm/test/gtc/%.o: ../glm/test/gtc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


