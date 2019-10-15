//
// Created by wcobalt on 10/14/19.
//
#include <vector>
#include <iostream>

#include "DefaultHuffmanDecoder.h"

using std::vector;
using namespace dengine;

DefaultHuffmanDecoder::DefaultHuffmanDecoder():layer(0), offset(0), size(0), tree(nullptr) {}

void DefaultHuffmanDecoder::loadCodesByCodesLengths(const vector<unsigned char> &codesLengths) {
    if (!tree) delete[] tree;

    unsigned maxCodeLength = 0;
    unsigned valuesCount = (unsigned)codesLengths.size(); //max is 2^16 - 1

    //find max code length
    for (unsigned char length : codesLengths)
        if (length > maxCodeLength) maxCodeLength = length;

    vector<unsigned> codesCount(maxCodeLength + 1, 0); //plus zero length

    //count count of code lengths
    for (unsigned char length : codesLengths) codesCount[length]++;

    //root is not a layer, so we need to increase layers count by one
    size = (1u << (maxCodeLength + 1)) - 1;

    //make empty tree
    tree = new unsigned[size];
    std::fill(tree, tree + size, NO_VALUE);

    //get smallest codes
    unsigned* codes = new unsigned[maxCodeLength + 1];
    codes[0] = 0;

    for (unsigned i = 1; i <= maxCodeLength; i++)
        codes[i] = (codes[i - 1] + codesCount[i - 1]) << 1u;

    //construct tree
    for (unsigned i = 0; i < valuesCount; i++) {
        reset();

        unsigned length = codesLengths[i];
        unsigned code = codes[length]++;

        for (unsigned b = length; b > 0; b--) navigate(((code >> (b - 1)) & 1) == 1);

        tree[getCurrentIndex()] = i;
    }

    reset();
}

void DefaultHuffmanDecoder::navigate(bool value) {
    offset = offset * 2u + (unsigned)value;
    layer++;
}

void DefaultHuffmanDecoder::reset() {
    offset = 0;
    layer = 0;
}

bool DefaultHuffmanDecoder::isResult() const {
    if (tree) return tree[getCurrentIndex()] != NO_VALUE;
    else return false;
}

unsigned int DefaultHuffmanDecoder::getResult() const {
    return tree[getCurrentIndex()];
}

unsigned DefaultHuffmanDecoder::getCurrentIndex() const {
    return (1u << layer) - 1 + offset;
}

DefaultHuffmanDecoder::~DefaultHuffmanDecoder() {
    delete[] tree;
}
