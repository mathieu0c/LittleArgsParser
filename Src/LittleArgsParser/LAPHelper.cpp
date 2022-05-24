#include "Log.hpp"

#include "LAPHelper.hpp"

namespace
{

size_t getHelpBaseLineSize(const lap::Command& cmd){
    return 7+size(cmd.longCmd);
}

void fillLine(std::string& toFill,size_t finalSize,char fillWith=' '){
    toFill.reserve(finalSize);
    while(size(toFill) <= finalSize+1)
    {
        toFill += fillWith;
    }
}

//the finalSize is the total str length before the description
std::string getHelpLine(const lap::Command& cmd,size_t sizeBeforeArgs){
    std::string out{"\t"};
    std::string argCountStr{" expect "+std::to_string(cmd.argCount)+" arg  "};
    out.reserve(sizeBeforeArgs+size(argCountStr)+1);
    out += (cmd.shortCmd)?std::string{"-"}+cmd.shortCmd:"  ";
    out += "  ";
    out += (!empty(cmd.longCmd))?"--"+cmd.longCmd:"";
    fillLine(out,sizeBeforeArgs);
    if(cmd.argCount)
    {
        out.back() = ':';
        out += argCountStr;
    }
    else
    {
        fillLine(out,sizeBeforeArgs+size(argCountStr),'.');
    }
    out.back() = ':';
    return out+" "+cmd.description;
}

} // namespace


namespace lap
{

std::string getCmdHelp(const CmdList& cmds_){
    //line format : "\t-X  --YYYY                  : DESCRIPTION"
    //or
    //line format : "\t-X  --YYYY : expect <Z> arg : DESCRIPTION"
    //base size before "YYYY" : 7
    size_t maxLineSize{};
    using CmdRealType = typename std::iterator_traits<CmdList::iterator>::value_type;
    std::vector<CmdRealType> cmds{cbegin(cmds_),cend(cmds_)};//copy cmds to a vector to sort it

    std::sort(begin(cmds),end(cmds),[&](const auto& l,const auto& r){
        return ((l->shortCmd)?std::string{l->shortCmd}:l->longCmd)<((r->shortCmd)?std::string{r->shortCmd}:r->longCmd);
    });

    for(const auto& e : cmds)
    {
        maxLineSize = std::max(maxLineSize,getHelpBaseLineSize(*e));
    }

    std::string out{};
    size_t curCount{};
    for(size_t i{}; i < size(cmds);++i)
    {
        const auto& e{cmds[i]};
        out += getHelpLine(*e,maxLineSize);

        if(i < size(cmds)-1)
        {
            out += "\n";
        }
    }
    return out;
}

} // namespace lap
