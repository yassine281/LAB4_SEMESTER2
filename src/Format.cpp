#pragma once
#include "Format.hpp"
#include "Exceptions.hpp"
#include <string>
std::pair<char,char> extractWrapSimple(const std::string& fmt, char token) {
    size_t pos = fmt.find(token);
    if (pos == std::string::npos || pos == 0 || pos + 1 >= fmt.size()) {
        throw TreeException("Invalid format: cannot find wrappers for token");
    }
    return { fmt[pos - 1], fmt[pos + 1] };
}
FormatSpec ParseFormat(const std::string& fmt) {
    if (fmt.find('K') == std::string::npos ||
        fmt.find('L') == std::string::npos ||
        fmt.find('P') == std::string::npos) {
        throw TreeException("Format must contain K, L, and P");
    }

    FormatSpec spec;
    spec.wrapK = extractWrapSimple(fmt, 'K');
    spec.wrapL = extractWrapSimple(fmt, 'L');
    spec.wrapP = extractWrapSimple(fmt, 'P');
    std::string order;
    for (char c : fmt) {
        if (c == 'K' || c == 'L' || c == 'P') {
            order.push_back(c);
        }
    }
    if (order.size() != 3) {
        throw TreeException("Format must contain exactly one K, one L, and one P");
    }
    spec.order = order;

    return spec;
}
