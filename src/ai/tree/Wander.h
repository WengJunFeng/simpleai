#pragma once

#include "tree/ITask.h"
#include "common/String.h"
#include "common/Math.h"

namespace ai {

/**
 * Wander forward in the current direction
 */
class Wander: public ITask {
protected:
	float _rotation;
public:
	TASK_CLASS_CTOR(Wander) {
		if (_parameters.empty()) {
			_rotation = 8.0f * static_cast<float>(M_PI);
		} else {
			_rotation = Str::toFloat(_parameters);
		}
	}
	NODE_FACTORY

	TreeNodeStatus doAction(AI& entity, long deltaMillis) override;
};

}