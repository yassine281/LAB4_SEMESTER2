#pragma once
#include <string>
#include <utility>

struct FormatSpec {
    std::pair<char,char> wrapK{'{','}'};
    std::pair<char,char> wrapL{'(',')'};
    std::pair<char,char> wrapP{'[',']'};
    std::string order = "KLP";
};

enum class Traversal {
    KLP, KPL, LKP, LPK, PLK, PKL
};
FormatSpec ParseFormat(const std::string& fmt);

