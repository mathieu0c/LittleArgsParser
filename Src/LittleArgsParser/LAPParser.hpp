#pragma once

#include "LAPTypes.hpp"

#include <algorithm>
#include <unordered_set>

namespace lap
{

namespace
{

struct IntermediateParseResult{
    lap::CmdList list{};
    SharedCmd expectingArg{nullptr};
    lap::StringVector freeArgs{};
};


//merge r in l
//if both l and r have a pending "waiting for arg" it will throw an error as only one command at a time can be waiting for an arg
inline
IntermediateParseResult merge(const IntermediateParseResult& l, const IntermediateParseResult& r){
    if(l.expectingArg && r.expectingArg)
    {
        LOGPL("Both commands <"<<l.expectingArg<<"> and <"<<r.expectingArg<<"> were expecting an argument. This is forbidden");
        throw std::runtime_error{"Both commands <"+to_human(l.expectingArg)+"> and <"+to_human(r.expectingArg)+"> were expecting an argument. This is forbidden"};
    }
    IntermediateParseResult out{.list = l.list,
                                .expectingArg=(l.expectingArg)?l.expectingArg:r.expectingArg,
                                .freeArgs = l.freeArgs};
    out.list.insert(cbegin(r.list),cend(r.list));
    out.freeArgs.reserve(size(r.freeArgs));
    out.freeArgs.insert(end(out.freeArgs),cbegin(r.freeArgs),cend(r.freeArgs));
    return out;
}
} // namespace


template<typename UnaryPredicate,typename T> 
int32_t firstIndexOf(const T& cmds,UnaryPredicate p){
    auto foundIter{std::find_if(cbegin(cmds),cend(cmds),p)};
    if(foundIter == cend(cmds))
        return -1;
    return std::distance(cbegin(cmds),foundIter); 
}
template<typename UnaryPredicate,typename T> 
auto find(const T& cmds,UnaryPredicate p){
    auto foundIter{std::find_if(cbegin(cmds),cend(cmds),p)};
    return foundIter; 
}

inline
auto find(const decltype(Command::shortCmd)& cmd,const CmdList& cmds){
    return find(cmds,[&](const auto& l){
        return l->shortCmd == cmd;
    });
}
inline
auto find(const decltype(Command::longCmd)& cmd,const CmdList& cmds){
    return find(cmds,[&](const auto& l){
        return l->longCmd == cmd;
    });
}

// inline
// auto firstIndexOfShort(const Command& cmd,const CmdList& cmds){
//     return firstIndexOf(cmds,[&](const auto& l){
//         return l->shortCmd == cmd.shortCmd;
//     });
// }
// inline
// auto firstIndexOfShort(char cmd,const CmdList& cmds){
//     return firstIndexOf(cmds,[&](const auto& l){
//         return l->shortCmd == cmd;
//     });
// }
// inline
// auto firstIndexOfLong(const Command& cmd,const CmdList& cmds){
//     return firstIndexOf(cmds,[&](const auto& l){
//         return l->longCmd == cmd.longCmd;
//     });
// }

IntermediateParseResult parseShortCmd(const std::string_view input,const CmdList& cmds);
IntermediateParseResult parseLongCmd(const std::string& input,const CmdList& cmds);

std::optional<ParseResult> parseArgs(int argc,char* argv[],const CmdList& cmds,bool skipFirstArg = true);

std::pair<bool,const StringVector&> gotCmd(const ParseResult& cmds,const Command& cmd); 

} // namespace lap

namespace std
{



} // namespace std