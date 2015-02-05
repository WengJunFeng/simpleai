/**
 * @file
 * @brief Defines some basic movement algorithms like Wandering, Seeking and Fleeing.
 */
#pragma once

#include "AI.h"
#include "IAIFactory.h"
#include "common/Math.h"
#include "common/MoveVector.h"
#include "common/String.h"
#include "common/MemoryAllocator.h"
#include "ICharacter.h"
#include <cassert>

namespace ai {
namespace movement {

#define STEERING_FACTORY \
public: \
	class Factory: public ISteeringFactory { \
	public: \
		SteeringPtr create (const SteeringFactoryContext *ctx) const; \
	}; \
	static Factory FACTORY;

#define STEERING_FACTORY_SINGLETON \
public: \
	class Factory: public ISteeringFactory { \
		SteeringPtr create (const SteeringFactoryContext */*ctx*/) const { \
			return get(); \
		} \
	}; \
	static Factory FACTORY;

#define STEERING_FACTORY_IMPL(SteeringName) \
	SteeringPtr SteeringName::Factory::create(const SteeringFactoryContext *ctx) const { \
		SteeringName* c = new SteeringName(ctx->parameters); \
		return SteeringPtr(c); \
	} \
	SteeringName::Factory SteeringName::FACTORY;


/**
 * @brief Steering interface
 */
class ISteering : public MemObject, public IPrintable {
public:
	virtual ~ISteering() {}
	/**
	 * @brief Calculates the @c MoveVector
	 *
	 * @return If the @c MoveVector contains @c Vector3f::INFINITE as vector, the result should not be used
	 * because there was an error.
	 */
	virtual MoveVector execute (const ICharacter& character, float speed) const = 0;

	virtual std::ostream& print(std::ostream& output, int level) const = 0;
};

}
}
