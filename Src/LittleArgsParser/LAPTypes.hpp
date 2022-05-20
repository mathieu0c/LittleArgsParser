#pragma once

#include <string>
#include <string_view>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_set>

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


namespace lap
{
using StringVector=std::vector<std::string>;

enum CmdType{
    TYPE_UNKNOWN=0,
    TYPE_SHORT=1u<<0,
    TYPE_LONG=1u<<1,
    TYPE_TEXT=1u<<2
};

struct Command{
    char shortCmd{};
    std::string longCmd{};
    int32_t argCount{0};
};
inline
bool operator==(const Command& l, const Command& r){
    return l.shortCmd == r.shortCmd && l.longCmd == r.longCmd && l.argCount == r.argCount;
}
std::string to_string(const Command& cmd);
std::string to_human(const Command& cmd);//human readable string
std::ostream& operator<<(std::ostream& os,const Command& cmd);

using SharedCmd=std::shared_ptr<Command>;
inline
auto to_human(const SharedCmd& cmd){return to_human(*cmd);};
inline
std::ostream& operator<<(std::ostream& os,const SharedCmd& cmd){return os << *cmd;};
// using SharedCmdVector=std::vector<SharedCmd>;
using SharedCmdSet=std::unordered_set<SharedCmd>;

struct CommandResult{
    const SharedCmd cmd{};
    StringVector args{};
};
inline
bool operator==(const CommandResult& l, const CommandResult& r){
    return l.cmd == r.cmd && l.args == r.args;
}
inline
auto to_human(const CommandResult& cmd){return to_human(*cmd.cmd);};
inline
std::ostream& operator<<(std::ostream& os,const CommandResult& cmd){return os << *cmd.cmd;};

using CmdList = SharedCmdSet;
inline
void addCommand(CmdList& cmds,Command cmd){
    // cmds.emplace_back(std::make_shared<Command>(std::move(cmd)));
    cmds.insert(std::make_shared<Command>(std::move(cmd)));
}

} // namespace lap

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

} // namespace std