//
// Created by wcobalt on 29.03.19.
//

#include "String.h"

using namespace dengine::utils;

String::String() {
    string = std::make_shared<std::string>(new std::string());
}

String::String(String &str) {
    *this = str;
}

String::String(const std::string &str) {
    *this = str;
}

String& String::operator=(const std::string &str) {
    string = std::make_shared<std::string>(new std::string(str));

    return *this;
}

String& String::operator=(String str) {
    string = std::make_shared<std::string>(new std::string(*(str.get())));

    return *this;
}

shared_ptr<std::string> String::get() {
    return string;
}