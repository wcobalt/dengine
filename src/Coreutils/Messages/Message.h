//
// Created by wcobalt on 11/22/19.
//
#include <chrono>

#ifndef DENGINE_MESSAGE_H
#define DENGINE_MESSAGE_H

namespace dengine {
    class Message {
    protected:
        using time_type = std::chrono::system_clock::time_point;
    private:
        time_type sendingTime;
    public:
        Message();

        Message(time_type sendingTime);

        virtual time_type getSendingTime() const {
            return sendingTime;
        }
    };
}

#endif //DENGINE_MESSAGE_H
