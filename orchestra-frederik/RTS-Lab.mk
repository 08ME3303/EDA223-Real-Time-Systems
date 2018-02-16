##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=RTS-Lab
ConfigurationName      :=Debug
WorkspacePath          :=/home/sanoop/Documents/EDA223-Real-Time-Systems
ProjectPath            :=/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Anoop
Date                   :=16/02/18
CodeLitePath           :=/home/sanoop/.codelite
LinkerName             :=/usr/bin/arm-none-eabi-g++
SharedObjectLinkerName :=/usr/bin/arm-none-eabi-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).elf
Preprocessors          :=$(PreprocessorSwitch)STM32F40_41xxx 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="RTS-Lab.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  --specs=nano.specs -mthumb -o $(IntermediateDirectory)/$(ProjectName).elf  -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -nostartfiles -T$(ProjectPath)/md407-ram.x -Wl,-Map=$(IntermediateDirectory)/$(ProjectName).map,--cref
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)$(ProjectPath) $(IncludeSwitch)$(ProjectPath)/device/inc $(IncludeSwitch)$(ProjectPath)/driver/inc 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/arm-none-eabi-ar rcu
CXX      := /usr/bin/arm-none-eabi-g++
CC       := /usr/bin/arm-none-eabi-gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fverbose-asm $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/arm-none-eabi-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/application.c$(ObjectSuffix) $(IntermediateDirectory)/sciTinyTimber.c$(ObjectSuffix) $(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IntermediateDirectory)/TinyTimber.c$(ObjectSuffix) $(IntermediateDirectory)/dispatch.s$(ObjectSuffix) $(IntermediateDirectory)/canTinyTimber.c$(ObjectSuffix) $(IntermediateDirectory)/conductor.c$(ObjectSuffix) $(IntermediateDirectory)/controller.c$(ObjectSuffix) $(IntermediateDirectory)/instrument.c$(ObjectSuffix) $(IntermediateDirectory)/performer.c$(ObjectSuffix) \
	$(IntermediateDirectory)/tonegen.c$(ObjectSuffix) $(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(ObjectSuffix) $(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(ObjectSuffix) $(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(ObjectSuffix) $(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(ObjectSuffix) $(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(ObjectSuffix) $(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	arm-none-eabi-objcopy -S -O srec  ./Debug/RTS-Lab.elf ./Debug/RTS-Lab.s19
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/application.c$(ObjectSuffix): application.c $(IntermediateDirectory)/application.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/application.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/application.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/application.c$(DependSuffix): application.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/application.c$(ObjectSuffix) -MF$(IntermediateDirectory)/application.c$(DependSuffix) -MM application.c

$(IntermediateDirectory)/application.c$(PreprocessSuffix): application.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/application.c$(PreprocessSuffix) application.c

$(IntermediateDirectory)/sciTinyTimber.c$(ObjectSuffix): sciTinyTimber.c $(IntermediateDirectory)/sciTinyTimber.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/sciTinyTimber.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sciTinyTimber.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sciTinyTimber.c$(DependSuffix): sciTinyTimber.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sciTinyTimber.c$(ObjectSuffix) -MF$(IntermediateDirectory)/sciTinyTimber.c$(DependSuffix) -MM sciTinyTimber.c

$(IntermediateDirectory)/sciTinyTimber.c$(PreprocessSuffix): sciTinyTimber.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sciTinyTimber.c$(PreprocessSuffix) sciTinyTimber.c

$(IntermediateDirectory)/startup.c$(ObjectSuffix): startup.c $(IntermediateDirectory)/startup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/startup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup.c$(DependSuffix): startup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/startup.c$(DependSuffix) -MM startup.c

$(IntermediateDirectory)/startup.c$(PreprocessSuffix): startup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup.c$(PreprocessSuffix) startup.c

$(IntermediateDirectory)/TinyTimber.c$(ObjectSuffix): TinyTimber.c $(IntermediateDirectory)/TinyTimber.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/TinyTimber.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TinyTimber.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TinyTimber.c$(DependSuffix): TinyTimber.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TinyTimber.c$(ObjectSuffix) -MF$(IntermediateDirectory)/TinyTimber.c$(DependSuffix) -MM TinyTimber.c

$(IntermediateDirectory)/TinyTimber.c$(PreprocessSuffix): TinyTimber.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TinyTimber.c$(PreprocessSuffix) TinyTimber.c

$(IntermediateDirectory)/dispatch.s$(ObjectSuffix): dispatch.s $(IntermediateDirectory)/dispatch.s$(DependSuffix)
	$(AS) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/dispatch.s" $(ASFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dispatch.s$(ObjectSuffix) -I$(IncludePath)
$(IntermediateDirectory)/dispatch.s$(DependSuffix): dispatch.s
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dispatch.s$(ObjectSuffix) -MF$(IntermediateDirectory)/dispatch.s$(DependSuffix) -MM dispatch.s

$(IntermediateDirectory)/dispatch.s$(PreprocessSuffix): dispatch.s
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dispatch.s$(PreprocessSuffix) dispatch.s

$(IntermediateDirectory)/canTinyTimber.c$(ObjectSuffix): canTinyTimber.c $(IntermediateDirectory)/canTinyTimber.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/canTinyTimber.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/canTinyTimber.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/canTinyTimber.c$(DependSuffix): canTinyTimber.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/canTinyTimber.c$(ObjectSuffix) -MF$(IntermediateDirectory)/canTinyTimber.c$(DependSuffix) -MM canTinyTimber.c

$(IntermediateDirectory)/canTinyTimber.c$(PreprocessSuffix): canTinyTimber.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/canTinyTimber.c$(PreprocessSuffix) canTinyTimber.c

$(IntermediateDirectory)/conductor.c$(ObjectSuffix): conductor.c $(IntermediateDirectory)/conductor.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/conductor.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/conductor.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/conductor.c$(DependSuffix): conductor.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/conductor.c$(ObjectSuffix) -MF$(IntermediateDirectory)/conductor.c$(DependSuffix) -MM conductor.c

$(IntermediateDirectory)/conductor.c$(PreprocessSuffix): conductor.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/conductor.c$(PreprocessSuffix) conductor.c

$(IntermediateDirectory)/controller.c$(ObjectSuffix): controller.c $(IntermediateDirectory)/controller.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/controller.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/controller.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/controller.c$(DependSuffix): controller.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/controller.c$(ObjectSuffix) -MF$(IntermediateDirectory)/controller.c$(DependSuffix) -MM controller.c

$(IntermediateDirectory)/controller.c$(PreprocessSuffix): controller.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/controller.c$(PreprocessSuffix) controller.c

$(IntermediateDirectory)/instrument.c$(ObjectSuffix): instrument.c $(IntermediateDirectory)/instrument.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/instrument.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/instrument.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/instrument.c$(DependSuffix): instrument.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/instrument.c$(ObjectSuffix) -MF$(IntermediateDirectory)/instrument.c$(DependSuffix) -MM instrument.c

$(IntermediateDirectory)/instrument.c$(PreprocessSuffix): instrument.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/instrument.c$(PreprocessSuffix) instrument.c

$(IntermediateDirectory)/performer.c$(ObjectSuffix): performer.c $(IntermediateDirectory)/performer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/performer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/performer.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/performer.c$(DependSuffix): performer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/performer.c$(ObjectSuffix) -MF$(IntermediateDirectory)/performer.c$(DependSuffix) -MM performer.c

$(IntermediateDirectory)/performer.c$(PreprocessSuffix): performer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/performer.c$(PreprocessSuffix) performer.c

$(IntermediateDirectory)/tonegen.c$(ObjectSuffix): tonegen.c $(IntermediateDirectory)/tonegen.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/tonegen.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tonegen.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tonegen.c$(DependSuffix): tonegen.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tonegen.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tonegen.c$(DependSuffix) -MM tonegen.c

$(IntermediateDirectory)/tonegen.c$(PreprocessSuffix): tonegen.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tonegen.c$(PreprocessSuffix) tonegen.c

$(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(ObjectSuffix): driver/src/stm32f4xx_dac.c $(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/driver/src/stm32f4xx_dac.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(DependSuffix): driver/src/stm32f4xx_dac.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(DependSuffix) -MM driver/src/stm32f4xx_dac.c

$(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(PreprocessSuffix): driver/src/stm32f4xx_dac.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/driver_src_stm32f4xx_dac.c$(PreprocessSuffix) driver/src/stm32f4xx_dac.c

$(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(ObjectSuffix): driver/src/stm32f4xx_gpio.c $(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/driver/src/stm32f4xx_gpio.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(DependSuffix): driver/src/stm32f4xx_gpio.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(DependSuffix) -MM driver/src/stm32f4xx_gpio.c

$(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(PreprocessSuffix): driver/src/stm32f4xx_gpio.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/driver_src_stm32f4xx_gpio.c$(PreprocessSuffix) driver/src/stm32f4xx_gpio.c

$(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(ObjectSuffix): driver/src/stm32f4xx_rcc.c $(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/driver/src/stm32f4xx_rcc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(DependSuffix): driver/src/stm32f4xx_rcc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(DependSuffix) -MM driver/src/stm32f4xx_rcc.c

$(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(PreprocessSuffix): driver/src/stm32f4xx_rcc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/driver_src_stm32f4xx_rcc.c$(PreprocessSuffix) driver/src/stm32f4xx_rcc.c

$(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(ObjectSuffix): driver/src/stm32f4xx_tim.c $(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/driver/src/stm32f4xx_tim.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(DependSuffix): driver/src/stm32f4xx_tim.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(DependSuffix) -MM driver/src/stm32f4xx_tim.c

$(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(PreprocessSuffix): driver/src/stm32f4xx_tim.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/driver_src_stm32f4xx_tim.c$(PreprocessSuffix) driver/src/stm32f4xx_tim.c

$(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(ObjectSuffix): driver/src/stm32f4xx_usart.c $(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/driver/src/stm32f4xx_usart.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(DependSuffix): driver/src/stm32f4xx_usart.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(DependSuffix) -MM driver/src/stm32f4xx_usart.c

$(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(PreprocessSuffix): driver/src/stm32f4xx_usart.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/driver_src_stm32f4xx_usart.c$(PreprocessSuffix) driver/src/stm32f4xx_usart.c

$(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(ObjectSuffix): driver/src/stm32f4xx_can.c $(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/sanoop/Documents/EDA223-Real-Time-Systems/orchestra-frederik/driver/src/stm32f4xx_can.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(DependSuffix): driver/src/stm32f4xx_can.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(ObjectSuffix) -MF$(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(DependSuffix) -MM driver/src/stm32f4xx_can.c

$(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(PreprocessSuffix): driver/src/stm32f4xx_can.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/driver_src_stm32f4xx_can.c$(PreprocessSuffix) driver/src/stm32f4xx_can.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


