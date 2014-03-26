#pragma once

#include <AI.h>
#include <conditions/ICondition.h>

namespace ai {
namespace example {

class IsMoving: public ICondition {
public:
	CONDITION_CLASS(IsMoving)
	CONDITION_FACTORY

	bool evaluate(AI& entity) override {
		GameEntity& chr = static_cast<GameEntity&>(entity.getCharacter());
		return !chr.getRoute().empty();
	}
};

CONDITION_FACTORY_IMPL(IsMoving)

}
}
