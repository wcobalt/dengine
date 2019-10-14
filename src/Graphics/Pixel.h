//
// Created by wcobalt on 13.09.19.
//

#ifndef DENGINE_PIXEL_H
#define DENGINE_PIXEL_H

namespace dengine {
    class Pixel {
    public:
        virtual double getRed() = 0;

        virtual double getGreen() = 0;

        virtual double getBlue() = 0;

        virtual double getAlpha() = 0;
    };
}

#endif //DENGINE_PIXEL_H
