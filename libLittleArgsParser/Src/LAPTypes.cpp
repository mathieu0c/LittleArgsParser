#include "LittleArgsParser/LAPTypes.hpp"

#include <ostream>
#include <iostream>

namespace lap
{

std::string to_string(const Command& cmd){
    std::string out{"lap::Command{.shortCmd=\'"};
    out += cmd.shortCmd;
    out += "\',.longCmd=\"";
    out += cmd.longCmd;
    out += "\",.argCount=";
    out += std::to_string(cmd.argCount)+"}";
    return out;
}


std::string to_human(const Command& cmd)
{
    std::string out{"Command \"--"};
    out += cmd.longCmd;
    out += "\" (\'-";
    if(cmd.shortCmd)
        out += cmd.shortCmd;
    out += "\')";
    return out;
}

std::ostream& operator<<(std::ostream& os,const Command& cmd){
    return os << to_string(cmd);
}

} // namespace lap
