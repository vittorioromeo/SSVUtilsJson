##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SSVUtilsJson
ConfigurationName      :=Release
WorkspacePath          := "D:\Vee\Software\GitHub\OHWorkspace"
ProjectPath            := "D:\Vee\Software\GitHub\OHWorkspace\SSVUtilsJson"
IntermediateDirectory  :=./_INTERMEDIATE/
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=vittorio.romeo
Date                   :=21/03/2013
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=./_RELEASE/$(ProjectName).dll
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="SSVUtilsJson.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./include/ $(IncludeSwitch)../jsoncpp/include/ $(IncludeSwitch)../SSVUtils/include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)json_mingw_libmt $(LibrarySwitch)SSVUtils 
ArLibs                 :=  "json_mingw_libmt" "SSVUtils" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../jsoncpp/libs/mingw/ $(LibraryPathSwitch)../SSVUtils/_RELEASE/ 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O3 -Wextra -pedantic -W -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=   $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
WXWIN:=C:\wxWidgets-2.9.4
WXCFG:=gcc_dll\mswu
Objects0=$(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix) 

Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "D:\Vee\Software\GitHub\OHWorkspace/.build-release"
	@echo rebuilt > "D:\Vee\Software\GitHub\OHWorkspace/.build-release/SSVUtilsJson"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./_INTERMEDIATE/"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix): src/SSVUtilsJson/Utils/UtilsJson.cpp $(IntermediateDirectory)/Utils_UtilsJson$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVUtilsJson/src/SSVUtilsJson/Utils/UtilsJson.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Utils_UtilsJson$(DependSuffix): src/SSVUtilsJson/Utils/UtilsJson.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix) -MF$(IntermediateDirectory)/Utils_UtilsJson$(DependSuffix) -MM "src/SSVUtilsJson/Utils/UtilsJson.cpp"

$(IntermediateDirectory)/Utils_UtilsJson$(PreprocessSuffix): src/SSVUtilsJson/Utils/UtilsJson.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Utils_UtilsJson$(PreprocessSuffix) "src/SSVUtilsJson/Utils/UtilsJson.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Utils_UtilsJson$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Utils_UtilsJson$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)
	$(RM) "../.build-release/SSVUtilsJson"


