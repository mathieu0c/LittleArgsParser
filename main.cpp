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
    lap::addCommand(cmds,{.shortCmd='f',.longCmd="sec-ond",.argCount=1});
    lap::parseArgs(argc,argv,cmds,true);

    return 0;
}
