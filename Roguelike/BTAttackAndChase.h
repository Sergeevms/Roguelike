#pragma once
#include <memory>

#include "BTComposite.h"
namespace Roguelike {
class BTAttackAndChase : public BTSelector {
   public:
    static std::unique_ptr<BTAttackAndChase> Create();
};
}  // namespace Roguelike
