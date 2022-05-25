#include "LittleArgsParser/LittleArgsParser"

#include "LAPParser.hpp"
#include "Log.hpp"

namespace lap
{

std::optional<ParseResult> parseArgs(const StringVector& inArgs,const CmdList& cmds){
    ParseResult out{};

    try
    {
        out = _parseArgs(inArgs,cmds);
    }
    catch(const std::exception& e)
    {
        LOGPL(e.what());
        RAWEL("Command line parsing error : "<<e.what()<<"\n");
        return {};
    }
    return out;
}

lap::CmdMatch matchedCmd(const ParseResult& cmds,const Command& cmd)
{
    for(const auto& e : cmds.cmdList)
    {
        if(*e.cmd == cmd)
        {
            return {true,e.args};
        }
    }
    return {.matched=false};
}

} // namespace lap
