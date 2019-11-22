//
// Created by wcobalt on 11/22/19.
//

#include "ParentChangeMessage.h"

using namespace dengine;

ParentChangeMessage::ParentChangeMessage(std::shared_ptr<GameObject> previousParent)
    : ParentChangeMessage(previousParent, std::chrono::system_clock::now()) {}

ParentChangeMessage::ParentChangeMessage(std::shared_ptr<GameObject> previousParent, time_type sendingTime)
    : Message(sendingTime), previousParent(previousParent) {}
