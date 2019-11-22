//
// Created by wcobalt on 11/22/19.
//

#include "Message.h"

using namespace dengine;

Message::Message() : Message(std::chrono::system_clock::now()) {}

Message::Message(Message::time_type sendingTime) : sendingTime(sendingTime) {}
