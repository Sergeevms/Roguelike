#include "BTAttackAndChase.h"

#include <memory>
#include <utility>

#include "BTAttackTarget.h"
#include "BTChaseTarget.h"
#include "BTComposite.h"
#include "BTDecorator.h"
#include "BTMoveAlongPath.h"
#include "BTSelectPlayerAsTarget.h"

namespace Roguelike {
std::unique_ptr<BTAttackAndChase> BTAttackAndChase::Create() {
    auto root = std::unique_ptr<BTAttackAndChase>(new BTAttackAndChase);

    auto selectAttackChase = std::make_unique<BTSequence>();
    selectAttackChase->AddChild(std::make_unique<BTSelectPlayerAsTarget>());
    auto chaseAttack = std::make_unique<BTParallel>(1);
    chaseAttack->AddChild(BTChaseTarget::Create());
    chaseAttack->AddChild(std::make_unique<BTAttackTarget>());
    selectAttackChase->AddChild(
        std::make_unique<BTRepeatUntilFailure>(std::move(chaseAttack)));
    root->AddChild(std::move(selectAttackChase));

    root->AddChild(
        std::make_unique<BTInverter>(std::make_unique<BTClearPath>()));

    return root;
}
}  // namespace Roguelike