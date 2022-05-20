#include <iostream>
#include <string>

#include <vector>

#define ENABLE_LOG

#include "Src/LittleArgsParser/LittleArgsParser.hpp"

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

    lap::Command title{.shortCmd='t',.longCmd="toc-title",.argCount=1};
    lap::addCommand(cmds,title);

    auto argsGivenOpt{lap::parseArgs(argc,argv,cmds,true)};

    if(!argsGivenOpt)
    {
        LOGEL("An error occurred when parsing command line arguments");
        return 1;
    }

    auto progArgs{argsGivenOpt.value()};
    auto doBackup{std::get<0>(lap::gotCmd(progArgs,cmd_outputFile))};
    if(doBackup)
    {
        LOGPL("You requested a Backup !");
    }

    return 0;
}
