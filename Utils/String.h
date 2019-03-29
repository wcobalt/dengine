//
// Created by wcobalt on 29.03.19.
//

#include <string>
#include <memory>

#ifndef DENGINE_STRING_H
#define DENGINE_STRING_H

namespace dengine::utils {
    using std::shared_ptr;

    //@todo make non-virtual functions as virtual where it needed
    class String {
    private:
        shared_ptr<std::string> string;
    public:
        String();
        String(String& str);
        String(const std::string& str);

        String& operator=(const std::string& str);
        String& operator=(String str);
        shared_ptr<std::string> get();
    };
}

#endif //DENGINE_STRING_H
