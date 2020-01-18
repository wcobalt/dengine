//
// Created by wcobalt on 11/22/19.
//

#include "ComponentMessage.h"

using namespace dengine;

ComponentMessage::ComponentMessage(Component::MessageType messageType) : ComponentMessage(messageType,
                                                                                          std::chrono::system_clock::now()) {}

ComponentMessage::ComponentMessage(Component::MessageType messageType, time_type sendingTime) :
    sendingTime(sendingTime), messageType(messageType) {}
