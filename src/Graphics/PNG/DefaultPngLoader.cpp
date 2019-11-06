//
// Created by wcobalt on 10/27/19.
//

#include <fstream>
#include <iostream>
#include "DefaultPngLoader.h"
#include "../Image.h"
#include "../../Exceptions/IOException.h"
#include "Exceptions/PngException.h"
#include "../ImageBuilder.h"
#include "../DefaultImageBuilder.h"
#include "png.h"

using namespace dengine;

std::shared_ptr<Image> DefaultPngLoader::load(const std::string &fileName) const {

}