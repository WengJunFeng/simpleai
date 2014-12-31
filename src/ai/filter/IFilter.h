#pragma once

#include <list>
#include <vector>
#include <ICharacter.h>
#include <common/MemoryAllocator.h>

namespace ai {

/**
 * @brief Macro to simplify the condition creation. Just give the class name of the condition as parameter.
 */
#define FILTER_CLASS(FilterName) \
	FilterName(const std::string& parameters = "") : \
		IFilter(#FilterName, parameters) { \
	} \
public: \
	virtual ~FilterName() { \
	}

#define FILTER_FACTORY \
public: \
	class Factory: public IFilterFactory { \
	public: \
		FilterPtr create (const FilterFactoryContext *ctx) const; \
	}; \
	static Factory FACTORY;

#define FILTER_FACTORY_SINGLETON \
public: \
	class Factory: public IFilterFactory { \
		FilterPtr create (const FilterFactoryContext */*ctx*/) const { \
			return get(); \
		} \
	}; \
	static Factory FACTORY;

#define FILTER_FACTORY_IMPL(FilterName) \
	FilterPtr FilterName::Factory::create(const FilterFactoryContext *ctx) const { \
		FilterName* c = new FilterName(ctx->parameters); \
		return FilterPtr(c); \
	} \
	FilterName::Factory FilterName::FACTORY;

// TODO: singleton construction is not thread safe
/**
 * @brief Macro to create a singleton conditions for very easy conditions without a state.
 */
#define FILTER_CLASS_SINGLETON(FilterName) \
private: \
FILTER_CLASS(FilterName) \
public: \
	static FilterPtr& get() { \
		static FilterName* c = nullptr; \
		if (c == nullptr) { c = new FilterName; } \
		static FilterPtr _instance(c); \
		return _instance; \
	} \
	FILTER_FACTORY_SINGLETON

class IFilter : public MemObject {
protected:
	const std::string _name;
	const std::string _parameters;

	inline FilteredEntities& getFilteredEntities(const AI& ai) {
		return ai._filteredEntities;
	}
public:
	IFilter (const std::string& name, const std::string& parameters) :
			_name(name), _parameters(parameters) {
	}

	virtual ~IFilter () {
	}

	inline const std::string& getName() const {
		return _name;
	}

	virtual void filter (const AI& entity) = 0;
};

}