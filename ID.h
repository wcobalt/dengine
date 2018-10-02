//
// Created by wcobalt on 30.09.18.
//

#include <string>

#ifndef DENGINE_ID_H
#define DENGINE_ID_H


class ID {
private:
    std::string name;
    std::string category;
public:
    ID(std::string name);
    ID(std::string name, std::string category);
    std::string getName();
    std::string getCategory();
};


#endif //DENGINE_ID_H
