#include <iostream>
#include <string>

#include <vector>

#define ENABLE_LOG

#include "Src/LittleArgsParser/LittleArgsParser.hpp"

namespace
{


} // namespace


int main(int argc,char* argv[]){
    
    std::vector<std::string> argList{argv+1,argv+argc};
    
    LOGPL("Arg list :");
    for(const auto& e : argList)
    {
        LOGL("\t" << e);
    }
    lap::CmdList cmds{};

    auto cmd_backup = lap::addCommand(cmds,lap::Command{.shortCmd='b',.longCmd="backup",.argCount=0,.description=
                        "Backup each input file as <INPUT.old>"});
    auto cmd_input = lap::addCommand(cmds,lap::Command{.shortCmd='i',.longCmd="",.argCount=1,.description=
                        "Specify explicitly an input file"});
    auto cmd_output = lap::addCommand(cmds,lap::Command{.shortCmd={},.longCmd="output",.argCount=1,.description=
                        "Specify explicitly an output file. Note that this option can not be used if more than 1 input file is specified."});
    auto cmd_title = lap::addCommand(cmds,lap::Command{.shortCmd='t',.longCmd="title",.argCount=1,.description=
                        "Specify a title for the table of content. If not set, the default title will be used"});
    auto cmd_help = lap::addCommand(cmds,lap::Command{.shortCmd='h',.longCmd="help",.argCount=0,.description="Display this help"});

    LOGL("------------");

    auto baseHelp=lap::getCmdHelp(cmds);
    LOGL(baseHelp);

    return 0;
}
