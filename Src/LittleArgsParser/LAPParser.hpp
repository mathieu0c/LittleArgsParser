#pragma once

#include "LAPTypes.hpp"

#include <algorithm>
#include <unordered_set>

namespace lap
{

namespace
{

struct IntermediateParseResult{
    std::unordered_set<SharedCmd> list{};
    SharedCmd expectingArg{nullptr};
};

} // namespace


template<typename UnaryPredicate,typename T> 
int32_t firstIndexOf(const T& cmds,UnaryPredicate p){
    auto foundIter{std::find_if(cbegin(cmds),cend(cmds),p)};
    if(foundIter == cend(cmds))
        return -1;
    return std::distance(cbegin(cmds),foundIter); 
}

inline
auto firstIndexOfShort(const Command& cmd,const CmdList& cmds){
    return firstIndexOf(cmds,[&](const auto& l){
        return l->shortCmd == cmd.shortCmd;
    });
}
inline
auto firstIndexOfShort(char cmd,const CmdList& cmds){
    return firstIndexOf(cmds,[&](const auto& l){
        return l->shortCmd == cmd;
    });
}
inline
auto firstIndexOfLong(const Command& cmd,const CmdList& cmds){
    return firstIndexOf(cmds,[&](const auto& l){
        return l->longCmd == cmd.longCmd;
    });
}

IntermediateParseResult parseShortCmd(const std::string_view input,const CmdList& cmds);
IntermediateParseResult parseLongCmd(const std::string_view input,const CmdList& cmds);

std::vector<CommandResult> parseArgs(int argc,char* argv[],const CmdList& cmds,bool skipFirstArg = true);

} // namespace lap
