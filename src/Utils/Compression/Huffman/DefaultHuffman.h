//
// Created by wcobalt on 10/14/19.
//

#ifndef DENGINE_DEFAULTHUFFMAN_H
#define DENGINE_DEFAULTHUFFMAN_H

#include "Huffman.h"

namespace dengine {
    class DefaultHuffman : public Huffman {
    private:
        unsigned layer, offset;
        unsigned* tree;
        unsigned size;

        const unsigned NO_VALUE = ~0u;

        unsigned getCurrentIndex() const;
    public:
        DefaultHuffman();

        void loadCodesByCodesLengths(const std::vector<unsigned char> &codesLengths);

        void navigate(bool value);

        void reset();

        bool isResult() const;

        unsigned int getResult() const;
    };
}

#endif //DENGINE_DEFAULTHUFFMAN_H
