//
// Created by wcobalt on 7/8/19.
//

#ifndef DENGINE_MOUSEBUTTON_H
#define DENGINE_MOUSEBUTTON_H

namespace dengine {
    using DMouseButton = unsigned;
    using DWheelDirection = int;

    class Mouse {
    public:
        static const DMouseButton LEFT = 0,
                                  RIGHT = 1,
                                  MIDDLE = 2;

        static const DWheelDirection POSITIVE_DIRECTION = 1,
                                     NEGATIVE_DIRECTION = -1;
    };
}

#endif //DENGINE_MOUSEBUTTON_H
