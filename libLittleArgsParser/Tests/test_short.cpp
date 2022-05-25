#include <iostream>
#include <string>

#include <littleArgsParser/LittleArgsParser.hpp>

namespace
{

template<typename T>
std::ostream& operator<<(std::ostream& os,const std::vector<T>& vec){
    os << "{";
    for(size_t i{}; i < size(vec);++i)
    {
        os << vec[i];
        if(i != size(vec)-1)
            os << ',';
    }
    return os << "}";
}

// template<typename T>
std::ostream& operator<<(std::ostream& os,const lap::CmdList& vec){
    os << "{";
    // const lap::SharedCmd& lastElem{*cend(vec)};
    for(const auto& e : vec)
    {
        os << e;
        // if(e != lastElem)
            os << ',';
    }
    return os << "}";
}

} // namespace

int test_allGood(const lap::CmdList& cmds,const std::vector<lap::SharedCmd>& refs){
    std::vector<std::string> argsInput_allGood{"-bi","File.txt","-o","FirstPart.txt","SecondPart.txt","freearg","freearg2"};

    for(int i{}; i < size(argsInput_allGood);++i)
    {
        LOGEL("i="<<i<<":"<<argsInput_allGood[i]);
    }

    for(int i{}; i < size(refs);++i)
    {
        LOGEL("   i="<<i<<":"<<refs[i]);
    }

    auto argsGivenOpt{lap::parseArgs(argsInput_allGood,cmds)};
    
    if(!argsGivenOpt)
    {
        LOGEL("An error occurred when parsing command line arguments");
        return 1;
    }
    auto argsGiven{argsGivenOpt.value()};

    if(lap::matchedCmd(argsGiven,refs[0]))//test if a backup (-b) was asked, should be TRUE
    {
    }
    else
    {
        LOGEL("Backup not found in : <"<<argsInput_allGood<<">");
        LOGEL("Command list : <"<<cmds<<">");
        return 1;
    }

    auto inputFileMatch{lap::matchedCmd(argsGiven,refs[1])};
    if(inputFileMatch)
    {
        if(size(inputFileMatch.args) != 1 || inputFileMatch.args[0] != argsInput_allGood[1])
        {
            LOGEL("Incorrect cmd found 0 : cmd<"<<refs[1]<<">");
            return 1;
        }
    }
    else
    {
        LOGEL("Input file not found in : <"<<argsInput_allGood<<">");
        LOGEL("Command list : <"<<cmds<<">");
        return 1;
    }

    auto outputFileMatch{lap::matchedCmd(argsGiven,refs[2])};
    if(outputFileMatch)
    {
        if( size(outputFileMatch.args) != 2 || outputFileMatch.args[0] != argsInput_allGood[3]
            || outputFileMatch.args[1] != argsInput_allGood[4])
        {
            LOGEL("Incorrect cmd found 1 : cmd<"<<refs[2]<<">");
            return 1;
        }
    }
    else
    {
        LOGEL("Output list not found in : <"<<argsInput_allGood<<">");
        LOGEL("Command list 2 : <"<<cmds<<">");
        return 1;
    }

    if(size(argsGiven.freeArgs) != 2 || argsGiven.freeArgs[0] != argsInput_allGood[5] || argsGiven.freeArgs[1] != argsInput_allGood[6])
    {
        LOGEL("Wrong free args");
        return 1;
    }

    return 0;
}

int main(int argc,char* argv[]){
    lap::CmdList cmds{};
    std::vector<lap::SharedCmd> tmpCmds{};

    tmpCmds.emplace_back(lap::addCommand(cmds,lap::Command{.shortCmd='b',.longCmd="",.argCount=0}));
    tmpCmds.emplace_back(lap::addCommand(cmds,lap::Command{.shortCmd='i',.longCmd="input",.argCount=1}));
    tmpCmds.emplace_back(lap::addCommand(cmds,lap::Command{.shortCmd={'o'},.longCmd="output-f",.argCount=2}));

    if(test_allGood(cmds,tmpCmds))
    {
        return 1;
    }
    
    return 0;
}
