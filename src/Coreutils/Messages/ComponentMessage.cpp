//
// Created by wcobalt on 11/22/19.
//

#include "ComponentMessage.h"

using namespace dengine;

ComponentMessage::ComponentMessage(Type messageType) : ComponentMessage(messageType,
                                                                        std::chrono::system_clock::now()) {}

ComponentMessage::ComponentMessage(Type messageType, time_type sendingTime) :
    sendingTime(sendingTime), messageType(messageType) {}
