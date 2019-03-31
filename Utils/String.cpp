//
// Created by wcobalt on 29.03.19.
//

#include "String.h"

using namespace dengine::utils;

String::String() {
    string = std::make_shared<std::string>(new std::string());
}

String::String(const String &str) {
    *this = str;
}

String::String(const char *str) {
    *this = str;
}

String::String(const std::string &str) {
    *this = str;
}

String& String::operator=(const std::string &str) {
    string = std::make_shared<std::string>(new std::string(str));

    return *this;
}

String& String::operator=(const char *str) {
    string = std::make_shared<std::string>(new std::string(str));

    return *this;
}

String& String::operator=(const String& str) {
    string = std::make_shared<std::string>(new std::string(*(str.get())));

    return *this;
}

bool String::operator==(const String &str) const {
    return *string == *(str.get());
}

shared_ptr<std::string> String::get() const {
    return string;
}