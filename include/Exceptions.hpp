#pragma once
#include <exception> 
#include <string>

struct TreeException : public std::exception {
    std::string message;
    TreeException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
