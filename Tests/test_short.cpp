#include <iostream>
#include <string>

#include "../Src/LittleArgsParser/Log.hpp"
#include "../Src/LittleArgsParser/LittleArgsParser.hpp"

int main(int argc,char* argv[]){
    std::vector<std::string> argsInput_allGood{"-bi","File.txt","-o","FirstPart.txt","SecondPart.txt"};


    lap::CmdList cmds{};

    auto cmd_inputFile{lap::addCommand(cmds,lap::Command{.shortCmd='i',.longCmd="input",.argCount=1})};
    auto cmd_backupFile{lap::addCommand(cmds,lap::Command{.shortCmd='b',.longCmd="",.argCount=0})};
    auto cmd_outputFile{lap::addCommand(cmds,lap::Command{.shortCmd={'o'},.longCmd="output-f",.argCount=2})};

    auto argsGivenOpt{lap::parseArgs(argc,argv,cmds,true)};
    
    if(!argsGivenOpt)
    {
        LOGEL("An error occurred when parsing command line arguments");
        return 1;
    }
    
    return 0;
}
