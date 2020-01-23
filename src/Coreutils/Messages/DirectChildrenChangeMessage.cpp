//
// Created by wcobalt on 11/22/19.
//

#include "DirectChildrenChangeMessage.h"

using namespace dengine;

DirectChildrenChangeMessage::DirectChildrenChangeMessage(ChildChangeType childChangeType,
                                                         GameObject &changedChild)
    : DirectChildrenChangeMessage(childChangeType, changedChild, std::chrono::system_clock::now()) {}

DirectChildrenChangeMessage::DirectChildrenChangeMessage(ChildChangeType childChangeType,
                                                         GameObject &changedChild,
                                                         time_type sendingTime) :
    ComponentMessage(ComponentMessage::Type::DIRECT_CHILDREN_CHANGE, sendingTime),
    childChangeType(childChangeType), changedChild(changedChild) {}

void DirectChildrenChangeMessage::handle(Component &component) const {
    component.onDirectChildrenChange(*this);
}
