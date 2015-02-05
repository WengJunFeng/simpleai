#pragma once

#include "Steering.h"

namespace ai {
namespace movement {

/**
 * @brief Steering and weight as input for @c WeightedSteering
 */
struct WeightedData {
	SteeringPtr steering;
	const float weight;

	WeightedData(const SteeringPtr& _steering, float _weight = 1.0f) :
			steering(_steering), weight(_weight) {
		assert(weight > 0.0001f);
	}
};
typedef std::vector<WeightedData> WeightedSteerings;
typedef WeightedSteerings::const_iterator WeightedSteeringsIter;

/**
 * @brief This class allows you to weight several steering methods and get a blended @c MoveVector out of it.
 */
class WeightedSteering : public IPrintable {
private:
	WeightedSteerings _steerings;
public:
	WeightedSteering(const WeightedSteerings& steerings) :
			_steerings(steerings) {
	}

	MoveVector execute (const ICharacter& character, float speed) const {
		float totalWeight = 0.0f;
		Vector3f vecBlended;
		float angularBlended = 0.0f;
		for (const WeightedData& wd : _steerings) {
			const float weight = wd.weight;
			const MoveVector& mv = wd.steering->execute(character, speed);
			if (mv.getVector().isInfinite())
				continue;

			vecBlended += mv.getVector() * weight;
			angularBlended += mv.getRotation() * weight;
			totalWeight += weight;
		}

		if (totalWeight <= 0.0000001f)
			return MoveVector(Vector3f::INFINITE, 0.0f);

		const float scale = 1.0f / totalWeight;
		return MoveVector(vecBlended * scale, fmodf(angularBlended * scale, M_2PI));
	}

	virtual std::ostream& print(std::ostream& stream, int level) const override {
		for (const WeightedData& wd : _steerings) {
			wd.steering->print(stream, level + 1);
			stream << " weight: " << wd.weight << std::endl;
		}
		return stream;
	}
};

}
}
