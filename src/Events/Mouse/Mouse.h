//
// Created by wcobalt on 7/8/19.
//

#ifndef DENGINE_MOUSEBUTTON_H
#define DENGINE_MOUSEBUTTON_H

namespace dengine::events::mouse {
    typedef int DMouseButton;
    typedef int DWheelDirection;

    class Mouse {
    public:
        static const DMouseButton LEFT = 0,
                                  RIGHT = 1,
                                  MIDDLE = 2,
                                  MB_4 = 4,
                                  MB_5 = 5;

        static const DWheelDirection POSITIVE_DIRECTION = 1,
                                     NEGATIVE_DIRECTION = -1;
    };
}

#endif //DENGINE_MOUSEBUTTON_H
