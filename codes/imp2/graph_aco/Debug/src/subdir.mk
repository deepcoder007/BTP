################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Graph.cpp \
../src/commons.cpp \
../src/configGraph.cpp \
../src/configNode.cpp \
../src/configNodeIterator.cpp \
../src/configNodeStorage.cpp \
../src/genGraph.cpp \
../src/tmpSrc.cpp 

OBJS += \
./src/Graph.o \
./src/commons.o \
./src/configGraph.o \
./src/configNode.o \
./src/configNodeIterator.o \
./src/configNodeStorage.o \
./src/genGraph.o \
./src/tmpSrc.o 

CPP_DEPS += \
./src/Graph.d \
./src/commons.d \
./src/configGraph.d \
./src/configNode.d \
./src/configNodeIterator.d \
./src/configNodeStorage.d \
./src/genGraph.d \
./src/tmpSrc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/media/vibhanshu/mydisk/serious/BTP/codes/imp2/graph_aco/include" -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


