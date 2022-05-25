#include <iostream>
#include <string>

#include <vector>

#define ENABLE_LOG

#include <LittleArgsParser/LittleArgsParser>

namespace
{


} // namespace


int main(int argc,char* argv[]){
    
    std::vector<std::string> argList{argv+1,argv+argc};
    
    // LOGPL("Arg list :");
    // for(const auto& e : argList)
    // {
    //     LOGL("\t" << e);
    // }
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

    // LOGL("------------");

    auto cmdsHelp=lap::helper::formatCmdHelp(cmds);
    lap::helper::FullHelp tmpHelp{.name="LittleArgsParser - Small lib to parse CLI arguments",
                                  .description="This lib allows to parse CLI arguments\n"
                                  "It takes care of matching options with the correct arg count, allows the programer to easily know if an option was given and generate an help command\n"
                                  "It also allows to check for errors when parsing CLI args",.cmdsHelp=cmdsHelp};
    

    lap::helper::ExampleList ex{
        lap::helper::Example{.cliInput="prog -bi MYFILE.md -o OUT.md",
        .description="First create a backup of <MYFILE.md> as <MYFILE.md.old>, then insert a table of content in it and saves it as <OUT.md>\nNote that MYFILE.md is never modified during the whole process"},
        lap::helper::Example{.cliInput="prog -i MYFILE.md -b SECONDFILE.md",
        .description="First create a backup of <MYFILE.md> as <MYFILE.md.old> and <SECONDFILE.md> as <SECONDFILE.md.old>\nThen insert a table of content in both original files <MYFILE.md> and <SECONDFILE.md>"}
    };
    std::string helpMsg{lap::helper::getHelp(
        "LittleArgsParser - Small lib to parse CLI arguments",
        "This lib allows to parse CLI arguments\n"
        "It takes care of matching options with the correct arg count, allows the programer to easily know if an option was given and generate an help command\n"
        "It also allows to check for errors when parsing CLI args",
        cmds,
        ex
    )};

    std::cout << helpMsg << "\n";

    return 0;
}
