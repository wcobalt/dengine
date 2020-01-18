//
// Created by wcobalt on 11/22/19.
//

#include "ComponentMessage.h"

using namespace dengine;

ComponentMessage::ComponentMessage() : ComponentMessage(std::chrono::system_clock::now()) {}

ComponentMessage::ComponentMessage(ComponentMessage::time_type sendingTime) : sendingTime(sendingTime) {}
