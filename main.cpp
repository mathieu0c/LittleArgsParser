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
    lap::addCommand(cmds,{.shortCmd='i',.longCmd="input",.argCount=1});
    lap::addCommand(cmds,{.shortCmd='o',.longCmd="output",.argCount=1});
    lap::addCommand(cmds,{.shortCmd={},.longCmd="title",.argCount=1});
    lap::addCommand(cmds,{.shortCmd='s',.longCmd="",.argCount=0});//save
    lap::addCommand(cmds,{.shortCmd={},.longCmd="Unknown",.argCount=0});
    lap::parseArgs(argc,argv,cmds,true);

    LOGL(_FILE_);
    return 0;
}
