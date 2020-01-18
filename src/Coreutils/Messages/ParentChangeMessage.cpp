//
// Created by wcobalt on 11/22/19.
//

#include "ParentChangeMessage.h"

using namespace dengine;

ParentChangeMessage::ParentChangeMessage(std::shared_ptr<GameObject> previousParent, std::shared_ptr<GameObject> newParent)
    : ParentChangeMessage(previousParent, newParent, std::chrono::system_clock::now()) {}

ParentChangeMessage::ParentChangeMessage(std::shared_ptr<GameObject> previousParent, std::shared_ptr<GameObject> newParent,
                                         time_type sendingTime)
    : ComponentMessage(sendingTime), previousParent(previousParent), newParent(newParent) {}
