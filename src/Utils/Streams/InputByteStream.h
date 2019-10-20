//
// Created by wcobalt on 10/20/19.
//

#ifndef DENGINE_INPUTBYTESTREAM_H
#define DENGINE_INPUTBYTESTREAM_H

namespace dengine {
    class InputByteStream {
    public:
        virtual char read() = 0;

        //@todo should it exist?
        virtual const char * getDataPointer() const = 0;
    };
}

#endif //DENGINE_INPUTBYTESTREAM_H
