//
// Created by wcobalt on 13.09.19.
//

#ifndef DENGINE_DEFAULTPIXEL_H
#define DENGINE_DEFAULTPIXEL_H

#include "Pixel.h"

namespace dengine {
    class DefaultPixel : public virtual Pixel {
        double red, green, blue, alpha;
    public:
        DefaultPixel();

        DefaultPixel(unsigned red, unsigned green, unsigned blue, unsigned alpha);
        
        DefaultPixel(double red, double green, double blue, double alpha);
        
        double getRed();

        double getGreen();

        double getBlue();

        double getAlpha();
    };
}

#endif //DENGINE_DEFAULTPIXEL_H
