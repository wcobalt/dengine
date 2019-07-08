//
// Created by wcobalt on 6/10/19.
//

#ifndef DENGINE_TRAYSPECIFICATIONISNOTSUPPORTEDEXCEPTION_H
#define DENGINE_TRAYSPECIFICATIONISNOTSUPPORTEDEXCEPTION_H

#include "../../../../Exceptions/DengineException.h"

namespace dengine::platform::window::x::exceptions {
class TraySpecificationIsNotSupportedException : public dengine::exceptions::DengineException {
        const char* what() const noexcept;
    };
}

#endif //DENGINE_TRAYSPECIFICATIONISNOTSUPPORTEDEXCEPTION_H
