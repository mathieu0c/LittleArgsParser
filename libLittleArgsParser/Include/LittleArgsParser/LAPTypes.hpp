#pragma once

#include <string>
#include <string_view>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_set>
#include <iostream>


namespace lap
{

/*!
 * @brief A simple std::vector of string
 */
using StringVector=std::vector<std::string>;

/*!
 * @brief The type used to create a command line option
 */
struct Command{
    char shortCmd{};
    std::string longCmd{};
    int32_t argCount{0};
    std::string description{};
};

using SharedCmd=std::shared_ptr<Command>;

using SharedCmdSet=std::unordered_set<SharedCmd>;

struct CommandResult{
    const SharedCmd cmd{};
    StringVector args{};
};

using ResultList=std::vector<CommandResult>;

/*!
 * @brief Used to store results of the command line parameters parsing
 */
struct ParseResult{
    ResultList cmdList{};
    StringVector freeArgs{};
};

/*!
 * @brief Used to store a list of available commands for the program
 */
using CmdList = SharedCmdSet;

/*!
 * @brief Add a command to a commandList
 * 
 * @param cmds : The command list to which to add a new command
 * @param cmd : The new command to add
 * @return SharedCmd : A shared pointer to the command added into the list
 */
inline
SharedCmd addCommand(CmdList& cmds,Command cmd){
    // cmds.emplace_back(std::make_shared<Command>(std::move(cmd)));
    return *(get<0>(cmds.insert(std::make_shared<Command>(std::move(cmd)))));
}

//used to know if a cmd was matched after parsing input args
struct CmdMatch{
    bool matched{false};
    const StringVector& args{};

    operator bool()const{
        return matched;
    }
};

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

//-------------------------- FUNCTIONS

// -- -- -- -- Command
inline
bool operator==(const Command& l, const Command& r){
    return l.shortCmd == r.shortCmd && l.longCmd == r.longCmd && l.argCount == r.argCount;
}
std::string to_string(const Command& cmd);
std::string to_human(const Command& cmd);//human readable string
std::ostream& operator<<(std::ostream& os,const Command& cmd);

// -- -- -- -- Shared Command
inline
auto to_human(const SharedCmd& cmd){return to_human(*cmd);};
inline
std::ostream& operator<<(std::ostream& os,const SharedCmd& cmd){return os << *cmd;};

// -- -- -- -- Command Result

inline
std::ostream& operator<<(std::ostream& os,const CommandResult& cmd){
    return os << "{.cmd=" <<*cmd.cmd<<",.args="<<cmd.args<<"}";
};

// -- -- -- -- Parse Result
inline
std::ostream& operator<<(std::ostream& os,const ParseResult& cmd){
    return os << "{.cmdList=" <<cmd.cmdList<<",.freeArgs="<<cmd.freeArgs<<"}";
};
inline
bool operator==(const CommandResult& l, const CommandResult& r){
    return l.cmd == r.cmd && l.args == r.args;
}
inline
auto to_human(const CommandResult& cmd){return to_human(*cmd.cmd);};

} // namespace lap





namespace
{

template <typename T, typename... Rest>
inline void hashCombine(std::size_t &seed, T const &v, Rest &&... rest) {
    std::hash<T> hasher;
    seed ^= (hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
    int i[] = { 0, (hashCombine(seed, std::forward<Rest>(rest)), 0)... };
    (void)(i);
}

} // namespace

namespace std
{

template<>
struct hash<lap::Command>
{
    size_t operator()(const lap::Command& key){
        size_t out{};
        ::hashCombine(out,key.longCmd,key.shortCmd,key.argCount);
        return out;
    }
    size_t operator()(const lap::Command* key){
        size_t out{};
        ::hashCombine(out,key->longCmd,key->shortCmd,key->argCount);
        return out;
    }
};

template<>
struct hash<lap::CommandResult>
{
    size_t operator()(const lap::CommandResult& r){
        return std::hash<lap::SharedCmd>()(r.cmd);
    }
};

} // namespace std