//
// Created by wcobalt on 11/22/19.
//

#include "MoveMessage.h"

using namespace dengine;

dengine::MoveMessage::MoveMessage(std::shared_ptr<GameObject> previousParent)
    : MoveMessage(previousParent, std::chrono::system_clock::now()) {}

dengine::MoveMessage::MoveMessage(std::shared_ptr<GameObject> previousParent, time_type sendingTime)
    : Message(sendingTime), previousParent(previousParent) {}
