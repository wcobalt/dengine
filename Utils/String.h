//
// Created by wcobalt on 29.03.19.
//

#include <string>
#include <memory>

#ifndef DENGINE_STRING_H
#define DENGINE_STRING_H

#include "../DObject.h"

namespace dengine::utils {
    using std::shared_ptr;

    //@todo make non-virtual functions as virtual where it needed
    //With love from Java!
    class String : public DObject {
    private:
        shared_ptr<std::string> string;
    public:
        String();
        String(const String& str);
        String(const char* str);
        String(const std::string& str);

        String& operator=(const std::string& str);
        String& operator=(const char* str);
        String& operator=(const String& str);
        bool operator==(const String& str) const;
        shared_ptr<std::string> get() const;
    };
}

#endif //DENGINE_STRING_H
