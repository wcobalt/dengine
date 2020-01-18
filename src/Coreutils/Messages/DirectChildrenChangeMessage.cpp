//
// Created by wcobalt on 11/22/19.
//

#include "DirectChildrenChangeMessage.h"

using namespace dengine;

DirectChildrenChangeMessage::DirectChildrenChangeMessage(ChildChangeType childChangeType,
                                                         std::shared_ptr<GameObject> changedChild)
    : DirectChildrenChangeMessage(childChangeType, changedChild, std::chrono::system_clock::now()) {}

DirectChildrenChangeMessage::DirectChildrenChangeMessage(ChildChangeType childChangeType,
                                                         std::shared_ptr<GameObject> changedChild,
                                                         time_type sendingTime) :
    ComponentMessage(Component::MessageType::DIRECT_CHILDREN_CHANGE, sendingTime),
    childChangeType(childChangeType), changedChild(changedChild) {}