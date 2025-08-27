#pragma once
#include "Exceptions.hpp"
#include "Format.hpp"
#include <string>

FormatSpec ParseFormat(const std::string& fmt) {
    FormatSpec spec;
    for (size_t i = 0; i + 1 < fmt.size(); ++i) {
        if (fmt[i] == '{' && fmt[i+1] == '}') {
            spec.wrapK = {'{','}'};
        } else if (fmt[i] == '(' && fmt[i+1] == ')') {
            spec.wrapL = {'(',')'};
        } else if (fmt[i] == '[' && fmt[i+1] == ']') {
            spec.wrapP = {'[',']'};
        }
    }

    spec.order.clear();
    for (char c : fmt) {
        if (c == 'K' || c == 'L' || c == 'P') {
            spec.order += c;
        }
    }

    if (spec.order.empty()) {
        spec.order = "KLP";
    }

    return spec;
}
