//
// Created by wcobalt on 10/14/19.
//
#include <vector>

#ifndef DENGINE_HUFFMAN_H
#define DENGINE_HUFFMAN_H

namespace dengine {
    class Huffman {
    public:
        virtual void loadCodesByCodesLengths(const std::vector<unsigned char> &codesLengths) = 0;

        virtual void navigate(bool value) = 0;

        virtual void reset() = 0;

        virtual bool isResult() const = 0;

        virtual unsigned int getResult() const = 0;
    };
}

#endif //DENGINE_HUFFMAN_H
