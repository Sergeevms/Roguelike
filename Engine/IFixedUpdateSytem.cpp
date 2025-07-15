#include "pch.h"

#include "IFixedUpdateSytem.h"

#include "GameWorld.h"

namespace MaxrEngine {
IFixedUpdateSytem::IFixedUpdateSytem() {
    GameWorld::Instance()->RegisterFixedUpdateSytem(this);
}

IFixedUpdateSytem::~IFixedUpdateSytem() {
    GameWorld::Instance()->UnRegisterFixedUpdateSytem(this);
}

float IFixedUpdateSytem::GetFixedUpdateTime() const { return fixedUpdateTime; }

void IFixedUpdateSytem::SetFixedUpdateTime(const float newFixedUpdateTime) {
    fixedUpdateTime = newFixedUpdateTime;
}
}  // namespace MaxrEngine