//
// Created by wcobalt on 10/25/19.
//

#include "DefaultZlibDecoder.h"
#include "../../../Exceptions/InvalidArgumentException.h"
#include "../../Streams/InputBitStream.h"
#include "../../Streams/DefaultInputBitStream.h"
#include "Exceptions/ZlibException.h"
#include "../Deflate/DefaultDeflateDecoder.h"
#include "../../HashSum/Adler32/DefaultAdler32.h"

using namespace dengine;

//@todo about deflatedecoder and zlibdecoder: if an exception was thrown then the decoders remain in undefined state so, call
// clear() before next use of them
const unsigned dengine::ZlibDecoder::CM;
const unsigned dengine::ZlibDecoder::CINFO;
const unsigned dengine::ZlibDecoder::FDICT;
const unsigned dengine::ZlibDecoder::FLEVEL;
const unsigned dengine::ZlibDecoder::DICTID;
const unsigned dengine::ZlibDecoder::ADLER32;
const unsigned dengine::ZlibDecoder::CM_DEFLATE;
const unsigned dengine::ZlibDecoder::CHECK_DIVIDER;

void DefaultZlibDecoder::decode(InputByteStream &inputStream) {
    clear();

    DefaultInputBitStream zlibStream(inputStream);
    DefaultInputBitStream correctnessCheckStream(inputStream);

    unsigned long check = correctnessCheckStream.readMultibyteNumber(CHECK_SIZE, true);
    size_t deflateOffset = CHECK_SIZE;

    if (check % CHECK_DIVIDER == 0) {
        unsigned cm = zlibStream.readNumber(CM_SIZE, true);

        if (cm == CM_DEFLATE) {
            unsigned cinfo = zlibStream.readNumber(CINFO_SIZE, true);
            zlibStream.skip(FCHECK_SIZE); //skip fcheck
            unsigned fdict = zlibStream.read();
            unsigned flevel = zlibStream.readNumber(FLEVEL_SIZE, true);
            unsigned long dictid = 0;

            if (fdict) {
                zlibStream.readMultibyteNumber(DICTID_SIZE, true);
                deflateOffset += DICTID_SIZE;
                metaData.insert(std::make_pair(DICTID, dictid));
            }

            metaData.insert(std::make_pair(CM, cm));
            metaData.insert(std::make_pair(CINFO, cinfo));
            metaData.insert(std::make_pair(FDICT, fdict));
            metaData.insert(std::make_pair(FLEVEL, flevel));

            //skip in byte stream bytes until deflate stream beginning
            inputStream.skip(deflateOffset);

            DefaultDeflateDecoder deflateDecoder;
            size_t deflateStreamBytesCount = deflateDecoder.decode(inputStream);

            decodedData = deflateDecoder.getDecodedData();

            zlibStream.skip(deflateStreamBytesCount * BITS_IN_CHAR);

            unsigned long formalAdler32 = zlibStream.readMultibyteNumber(ADLER_SIZE, true);

            metaData.insert(std::make_pair(ADLER32, formalAdler32));

            DefaultAdler32 adler32;
            unsigned long realAdler32 = adler32.calculateAdler32(decodedData);

            if (formalAdler32 != realAdler32)
                throw InvalidArgumentException(
                        "Adler32 of decoded data and formal in stream one are different (real and"
                        " formal): " + std::to_string(realAdler32) + " " + std::to_string(formalAdler32));
        } else
            throw ZlibException("Data is encoded by not supported compression method: " + std::to_string(cm));
    } else
        throw ZlibException("Zlib stream is corrupted. First two bytes are not a multiple of "
                             + std::to_string(CHECK_DIVIDER));
}

char DefaultZlibDecoder::operator[](size_t index) {
    return at(index);
}

char DefaultZlibDecoder::at(size_t index) const {
    if (index >= decodedData.size()) throw InvalidArgumentException("Index is out of bounds");

    return decodedData[index];
}

size_t DefaultZlibDecoder::getSize() const {
    return decodedData.size();
}

void DefaultZlibDecoder::clear() {
    decodedData.clear();
    metaData.clear();
}

unsigned long DefaultZlibDecoder::getProperty(unsigned property) const {
    auto iterator = metaData.find(property);

    if (iterator == metaData.end()) throw InvalidArgumentException("Property is missing");
    else return iterator->second;
}
