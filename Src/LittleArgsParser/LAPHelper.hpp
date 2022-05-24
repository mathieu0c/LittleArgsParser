#pragma once

#include "LAPTypes.hpp"

namespace lap{
namespace helper{

struct FullHelp{
    std::string name;
    std::string description;
    std::string cmdsHelp;
    std::string examples;
};

struct Example{
    std::string cliInput;
    std::string description;
};
using ExampleList=std::vector<Example>;

std::string formatCmdHelp(const CmdList& cmds_);
std::string formatExamples(const ExampleList& ex);
std::string formatFullHelp(const FullHelp& fullhelp);

std::string getHelp(const std::string& name,
                    const std::string& description,
                    const CmdList& cmds,
                    const ExampleList& ex);

} // namespace helper
} // namespace lap
