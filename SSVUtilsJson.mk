##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SSVUtilsJson
ConfigurationName      :=Release
WorkspacePath          := "D:\Vee\Software\GitHub\OHWorkspace"
ProjectPath            := "D:\Vee\Software\GitHub\OHWorkspace\SSVUtilsJson"
IntermediateDirectory  :=./INTERMEDIATE
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=vittorio.romeo
Date                   :=18/03/2013
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
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../SSVUtils $(IncludeSwitch)D:/Vee/Software/GitHub/OHWorkspace/jsoncpp/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SSVUtils $(LibrarySwitch)json_mingw_libmt 
ArLibs                 :=  "SSVUtils" "json_mingw_libmt" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../SSVUtils/_RELEASE $(LibraryPathSwitch)D:/Vee/Software/GitHub/OHWorkspace/jsoncpp/libs/mingw 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -W -s -pedantic -O3 -Wextra -std=c++11 -Wall $(Preprocessors)
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
	@$(MakeDirCommand) "./INTERMEDIATE"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix): Utils/UtilsJson.cpp $(IntermediateDirectory)/Utils_UtilsJson$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Vee/Software/GitHub/OHWorkspace/SSVUtilsJson/Utils/UtilsJson.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Utils_UtilsJson$(DependSuffix): Utils/UtilsJson.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Utils_UtilsJson$(ObjectSuffix) -MF$(IntermediateDirectory)/Utils_UtilsJson$(DependSuffix) -MM "Utils/UtilsJson.cpp"

$(IntermediateDirectory)/Utils_UtilsJson$(PreprocessSuffix): Utils/UtilsJson.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Utils_UtilsJson$(PreprocessSuffix) "Utils/UtilsJson.cpp"


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


