//
// Created by wcobalt on 11/22/19.
//

#include "ParentChangeMessage.h"

using namespace dengine;

ParentChangeMessage::ParentChangeMessage(GameObject &previousParent, GameObject &newParent)
    : ParentChangeMessage(previousParent, newParent, std::chrono::system_clock::now()) {}

ParentChangeMessage::ParentChangeMessage(GameObject &previousParent, GameObject &newParent,
                                         time_type sendingTime) :
      ComponentMessage(Component::MessageType::PARENT_CHANGE, sendingTime),
      previousParent(previousParent), newParent(newParent) {}
