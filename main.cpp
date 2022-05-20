#include <iostream>
#include <string>

#include <vector>

#define ENABLE_LOG

#include "Src/LittleArgsParser/LittleArgsParser.hpp"

namespace
{

template<typename T>
std::ostream& operator<<(std::ostream& os,const std::vector<T>& vec){
    os << "{";
    for(size_t i{}; i < size(vec);++i)
    {
        os << vec[i];
        if(i != size(vec)-1)
            os << ',';
    }
    return os << "}";
}

} // namespace


void addToMd(const lap::StringVector& i,const std::string& o, bool doBackup, const std::string& tocTitle){
    LOGL("Running markdown TOC on <"<<i<<"> to the ouput : <"<<o<<"> Backup ? <"<<doBackup<<"> TOC title ? <"<<tocTitle<<">");
}

int main(int argc,char* argv[]){
    
    std::vector<std::string> argList{argv+1,argv+argc};
    
    LOGPL("Arg list :");
    for(const auto& e : argList)
    {
        LOGL("\t" << e);
    }
    lap::CmdList cmds{};

    lap::Command cmd_inputFile{.shortCmd='i',.longCmd="input",.argCount=1};
    lap::addCommand(cmds,cmd_inputFile);

    lap::Command cmd_outputFile{.shortCmd='o',.longCmd="output",.argCount=1};
    lap::addCommand(cmds,cmd_outputFile);

    lap::Command cmd_backup{.shortCmd='b',.longCmd="backup",.argCount=0};
    lap::addCommand(cmds,cmd_backup);

    lap::Command cmd_title{.shortCmd='t',.longCmd="toc-title",.argCount=1};
    lap::addCommand(cmds,cmd_title);

    auto argsGivenOpt{lap::parseArgs(argc,argv,cmds,true)};

    if(!argsGivenOpt)
    {
        LOGEL("An error occurred when parsing command line arguments");
        return 1;
    }
    auto progArgs{argsGivenOpt.value()};

    lap::StringVector inputFiles{progArgs.freeArgs};
    std::string outputFile{};
    bool doBackup{true};
    std::string tocTitle{};

    doBackup = std::get<0>(lap::gotCmd(progArgs,cmd_outputFile));

    auto [foundTitle,title]{lap::gotCmd(progArgs,cmd_title)};
    if(foundTitle)
    {
        tocTitle = title[0];
    }
    
    auto [foundInput,tmpInputFiles]{lap::gotCmd(progArgs,cmd_inputFile)};
    if(foundInput)//if we have found an input file
        inputFiles.emplace(cbegin(inputFiles),tmpInputFiles[0]);//insert it at the beginning
    
    auto [foundOutput,tmpOutputFiles]{lap::gotCmd(progArgs,cmd_outputFile)};
    if(foundOutput)
    {
        outputFile = tmpOutputFiles[0];
        std::vector<std::string> rlyRunningWith{inputFiles[0]};
        addToMd(rlyRunningWith,outputFile,doBackup,tocTitle);
        inputFiles[0] = inputFiles[size(inputFiles)-1];
        inputFiles.resize(size(inputFiles)-1);
    }
    
    addToMd(inputFiles,outputFile,doBackup,tocTitle);

    return 0;
}
