#include "Log.hpp"
#include "LAPParser.hpp"

namespace
{
using namespace lap;
std::vector<CommandResult> _parseArgs(int argc,char* argv[],const CmdList& cmds,bool skipFirstArg){
    StringVector inArgs{argv+static_cast<int>(skipFirstArg),argv+argc};

    std::vector<CommandResult> out{};

    IntermediateParseResult tmpResults{};

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
                if(tmpResults.expectingArg){
                    
                }
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
                auto tmp{parseShortCmd({cbegin(arg)+1,cend(arg)},cmds)};
                LOGPL("GOT KEYS -- ");
                for(const auto& key : tmp.list)
                {
                    LOGPL("key.short="<<key->shortCmd);
                }
                if(tmp.expectingArg != nullptr)
                {
                    LOGPL("Waiting for an arg :"<<*tmp.expectingArg);
                }
                tmpResults = merge(tmpResults,tmp);
                LOGPL("GOT KEYS after merge-- ");
                for(const auto& key : tmpResults.list)
                {
                    LOGPL("key.short="<<key->shortCmd);
                }
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
                tmpResults = merge(tmpResults,parseLongCmd({cbegin(arg)+2,cend(arg)},cmds));
                LOGPL("GOT KEYS after LONG-- ");
                for(const auto& key : tmpResults.list)
                {
                    LOGPL("key.short="<<key->shortCmd);
                }
                break;
            }

            LOGEL("You are not supposed to be here -- Err when parsing arg <"<<arg<<"> at letter <"<<c<<">");
        }
    }

    LOGPL("Got commands summary :");
    for(const auto& e : tmpResults.list)
    {
        LOGPL("\t" << e);
    }

    return out;
}

} // namespace


namespace lap
{

IntermediateParseResult parseShortCmd(const std::string_view input,const CmdList& cmds)
{
    LOGPL("\tFound a short command : <"<<input<<">\n");

    IntermediateParseResult out{};

    for(const auto& c : input)
    {
        auto targetCmdIter{find(c,cmds)};
        if(targetCmdIter == cend(cmds))
        {
            LOGPL("Unknown command : <"<<c<<">");
            throw std::runtime_error{std::string{"Following command is not recognized : -"}+c};
        }
        const SharedCmd& targetCmd = *targetCmdIter;
        if(out.list.contains(targetCmd))
        {
            LOGPL("This command was already used <"<<c<<">");
            throw std::runtime_error{std::string{"Following command was already used : -"}+c};
        }
        if(targetCmd->argCount > 0)
        {
            if(!out.expectingArg)
                out.expectingArg = targetCmd;
            else
            {
                LOGPL(std::string{"Arguments conflicts : commands <"}+out.expectingArg->shortCmd+std::string{"> and <"}+c+std::string{"> were both expecting an argument"});
                throw std::runtime_error{std::string{"Arguments conflicts : commands <"}+out.expectingArg->shortCmd+std::string{"> and <"}+c+std::string{"> were both expecting an argument"}};
            }
        }
        out.list.insert(targetCmd);
    }

    return out;
}

IntermediateParseResult parseLongCmd(const std::string& input,const CmdList& cmds)
{
    LOGPL("\t\tFound a long command : <"<<input<<">\n");

    IntermediateParseResult out{};
    auto targetCmdIter{find(input,cmds)};
    if(targetCmdIter == cend(cmds))
    {
        LOGPL("Unknown command : <"<<input<<">");
        throw std::runtime_error{std::string{"Following command is not recognized : --"}+input};
    }
    const SharedCmd& targetCmd = *targetCmdIter;
    if(targetCmd->argCount > 0)
    {
        out.expectingArg = targetCmd;
    }
    out.list.insert(targetCmd);

    return out;
}

std::vector<CommandResult> parseArgs(int argc,char* argv[],const CmdList& cmds,bool skipFirstArg){
    std::vector<CommandResult> out{};

    try
    {
        out = _parseArgs(argc,argv,cmds,skipFirstArg);
    }
    catch(const std::exception& e)
    {
        RAWEL("Command line parsing error : "<<e.what()<<"\n");
    }
    return out;
}


} // namespace lap
