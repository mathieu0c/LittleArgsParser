#include "Log.hpp"
#include "LAPParser.hpp"

namespace
{
using namespace lap;
std::vector<CommandResult> _parseArgs(int argc,char* argv[],const CmdList& cmds,bool skipFirstArg){
    StringVector inArgs{argv+static_cast<int>(skipFirstArg),argv+argc};

    std::vector<CommandResult> out{};

    for(const auto& arg : inArgs)
    {
        LOGPL("Parsing arg <"<<arg<<">");
        
        CmdType tmpArgType{CmdType::TYPE_UNKNOWN};
        for(const auto& c : arg)//this must not do more than 2 iterations to ensure proper operation
        {
            if(tmpArgType==CmdType::TYPE_UNKNOWN && c != '-')
            {
                tmpArgType = CmdType::TYPE_TEXT;
                LOGPL("Found a simple text\n");
                break;
            }
            //else

            //TYPE_UNKNOWN should be matched only on the first char
            //and the current char is "-"
            if(tmpArgType == CmdType::TYPE_UNKNOWN)
            {
                tmpArgType = CmdType::TYPE_SHORT;
                continue;
            }

            if(tmpArgType == CmdType::TYPE_SHORT && c != '-')
            {
                //short command
                //INTERPRET SHORT COMMAND---------------------------
                parseShortCmd({cbegin(arg)+1,cend(arg)},cmds);
                break;
            }

            if(tmpArgType == CmdType::TYPE_SHORT)
            {
                tmpArgType = CmdType::TYPE_LONG;
                continue;
            }

            if(tmpArgType == CmdType::TYPE_LONG)
            {
                //long command
                //INTERPRET LONG COMMAND----------------------------
                parseLongCmd({cbegin(arg)+2,cend(arg)},cmds);
                break;
            }

            LOGEL("You are not supposed to be here -- Err when parsing arg <"<<arg<<"> at letter <"<<c<<">");
        }
    }
    return out;
}

} // namespace


namespace lap
{

std::unordered_set<CommandResult> parseShortCmd(const std::string_view input,const CmdList& cmds)
{
    LOGPL("\tFound a short command : <"<<input<<">\n");

    std::vector<CommandResult> out{};

    for(const auto& c : input)
    {
        if(firstIndexOfShort(c,cmds) == -1)
        {
            LOGPL("Unknown command : <"<<c<<">");
            throw std::runtime_error{std::string{"Following option is not recognized : -"}+c};
        }
    }

    return {};
}

std::unordered_set<CommandResult> parseLongCmd(const std::string_view input,const CmdList& cmds)
{
    LOGPL("\t\tFound a long command : <"<<input<<">\n");

    return {};
}

std::vector<CommandResult> parseArgs(int argc,char* argv[],const CmdList& cmds,bool skipFirstArg){
    std::vector<CommandResult> out{};

    try
    {
        out = _parseArgs(argc,argv,cmds,skipFirstArg);
    }
    catch(const std::exception& e)
    {
        RAWEL("Command parsing error : "<<e.what()<<"\n");
    }
    return out;
}


} // namespace lap
