#include "Log.hpp"

#include "LittleArgsParser/LAPHelper.hpp"

#include <regex>

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
std::string formatCmdHelp(const lap::Command& cmd){
    std::string out{""};
    std::string argCountStr{" expect "+std::to_string(cmd.argCount)+" arg  "};
    out.reserve(size(cmd.description)+size(argCountStr)+20);
    out += (cmd.shortCmd)?std::string{"-"}+cmd.shortCmd:"";
    if(cmd.shortCmd && !empty(cmd.longCmd))
        out += ",  ";
    out += (!empty(cmd.longCmd))?"--"+cmd.longCmd:"";
    if(cmd.argCount)
    {
        out += " : ";
        out += argCountStr;
    }
    out += "\n";
    out += "\t"+cmd.description;
    return out;
}

std::string formatExample(const lap::helper::Example& ex){
    std::string out{"Input : < "};
    out += ex.cliInput;
    out += " >\n\t";
    out += std::regex_replace(ex.description,std::regex{"\\n"},"\n\t");
    return out;
}

void addSectionToString(std::string& target,const std::string& sectionName,const std::string sectionContent,bool beginWithNewline = true){
    target.reserve(size(target)+size(sectionName)+size(sectionContent)+30);
    if(beginWithNewline)
        target += "\n";
    
    target += sectionName+"\n\t";
    target += std::regex_replace(sectionContent,std::regex{"\\n"},"\n\t");
}

} // namespace


namespace lap{
namespace helper{

std::string formatCmdHelp(const CmdList& cmds_){
    using CmdRealType = typename std::iterator_traits<CmdList::iterator>::value_type;
    std::vector<CmdRealType> cmds{cbegin(cmds_),cend(cmds_)};//copy cmds to a vector to sort it

    std::sort(begin(cmds),end(cmds),[&](const auto& l,const auto& r){
        return ((l->shortCmd)?std::string{l->shortCmd}:l->longCmd)<((r->shortCmd)?std::string{r->shortCmd}:r->longCmd);
    });


    std::string out{};
    size_t curCount{};
    for(size_t i{}; i < size(cmds);++i)
    {
        const auto& e{cmds[i]};
        out += ::formatCmdHelp(*e);

        if(i < size(cmds)-1)
        {
            out += "\n\n";
        }
    }
    return out;
}

std::string formatExamples(const ExampleList& ex){
    std::string out{};
    size_t curCount{};
    for(size_t i{}; i < size(ex);++i)
    {
        const auto& e{ex[i]};
        out += ::formatExample(e);

        if(i < size(ex)-1)
        {
            out += "\n\n";
        }
    }
    return out;
}

std::string formatFullHelp(const FullHelp& fullhelp){
    std::string out{};
    addSectionToString(out,"NAME",fullhelp.name,false);
    out += "\n\n";
    addSectionToString(out,"DESCRIPTION",fullhelp.description);
    out += "\n\n";
    addSectionToString(out,"OPTIONS",fullhelp.cmdsHelp);
    out += "\n\n";
    addSectionToString(out,"EXAMPLES",fullhelp.examples);
    return out;
}

std::string getHelp(const std::string& name,
                    const std::string& description,
                    const CmdList& cmds,
                    const ExampleList& ex){
    FullHelp tmp{
        .name = name,
        .description = description,
        .cmdsHelp = formatCmdHelp(cmds),
        .examples = formatExamples(ex)
    };
    return formatFullHelp(tmp);
}

} // namespace helper
} // namespace lap
