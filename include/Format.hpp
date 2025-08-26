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
inline FormatSpec ParseFormat(const std::string& fmt) {
    FormatSpec spec;
    for (size_t i = 0; i + 1 < fmt.size(); ++i) {
        if (fmt[i] == '{' && fmt[i+1] == '}') spec.wrapK = {'{','}'};
        else if (fmt[i] == '(' && fmt[i+1] == ')') spec.wrapL = {'(',')'};
        else if (fmt[i] == '[' && fmt[i+1] == ']') spec.wrapP = {'[',']'};
    }
    spec.order.clear();
    for (char c : fmt) {
        if (c == 'K' || c == 'L' || c == 'P') spec.order += c;
    }

    if (spec.order.empty()) spec.order = "KLP";
    return spec;
}
