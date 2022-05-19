#pragma once

#include <string>
#include <string_view>
#include <cstdint>
#include <memory>
#include <vector>

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
using SharedCmd=std::shared_ptr<Command>;
using SharedCmdVector=std::vector<SharedCmd>;

struct CommandResult{
    const SharedCmd cmd{};
    StringVector args{};
};

using CmdList = SharedCmdVector;
inline
void addCommand(SharedCmdVector& cmds,Command cmd){
    cmds.emplace_back(std::make_shared<Command>(std::move(cmd)));
}

} // namespace lap
