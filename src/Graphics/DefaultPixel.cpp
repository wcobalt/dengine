//
// Created by wcobalt on 13.09.19.
//

#include "DefaultPixel.h"

using namespace dengine;

DefaultPixel::DefaultPixel() {
    red = green = blue = alpha = 0.0;
}

DefaultPixel::DefaultPixel(unsigned red, unsigned green, unsigned blue, unsigned alpha) {
    this->red = (double)red / 256.0;
    this->green = (double)green / 256.0;
    this->blue = (double)blue / 256.0;
    this->alpha = (double)alpha / 256.0;
}

DefaultPixel::DefaultPixel(double red, double green, double blue, double alpha) {
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

double DefaultPixel::getRed() {
    return red;
}

double DefaultPixel::getGreen() {
    return green;
}

double DefaultPixel::getBlue() {
    return blue;
}

double DefaultPixel::getAlpha() {
    return alpha;
}
