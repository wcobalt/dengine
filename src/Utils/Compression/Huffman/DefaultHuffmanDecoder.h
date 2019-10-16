//
// Created by wcobalt on 10/14/19.
//

#ifndef DENGINE_DEFAULTHUFFMAN_H
#define DENGINE_DEFAULTHUFFMAN_H

#include "HuffmanDecoder.h"

namespace dengine {
    class DefaultHuffmanDecoder : public HuffmanDecoder {
    private:
        unsigned layer, offset;
        unsigned* tree;
        unsigned size, height;

        static const unsigned NO_VALUE = ~0u;

        unsigned getCurrentIndex() const;
    public:
        DefaultHuffmanDecoder();

        void loadCodesByCodesLengths(const std::vector<char> &codesLengths);

        void navigate(bool value);

        void reset();

        bool isResult() const;

        unsigned int getResult() const;

        virtual ~DefaultHuffmanDecoder();
    };
}

#endif //DENGINE_DEFAULTHUFFMAN_H
