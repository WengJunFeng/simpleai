#pragma once

#include <vector>
#include <AI.h>

namespace ai {

/**
 * @brief The aggro entry for the @c AIStateAggro
 *
 * Holds a character id and the assigned aggro value
 */
struct AIStateAggroEntry {
	AIStateAggroEntry(ai::CharacterId _id, float _aggro) :
			id(_id), aggro(_aggro) {
	}
	ai::CharacterId id;
	float aggro;
};

/**
 * @brief The list of aggro entry for a character
 */
class AIStateAggro {
private:
	std::vector<AIStateAggroEntry> _aggro;
public:
	inline void reserve(std::size_t size) {
		if (size > 0)
			_aggro.reserve(size);
	}

	inline void addAggro(const AIStateAggroEntry& entry) {
		_aggro.push_back(entry);
	}

	inline const std::vector<AIStateAggroEntry>& getAggro() const {
		return _aggro;
	}
};

class AIStateNodeStatic {
private:
	int _id;
	std::string _name;
	std::string _type;
public:
	AIStateNodeStatic(const int id, const std::string& name, const std::string& type) :
			_id(id), _name(name), _type(type) {
	}

	AIStateNodeStatic() :
			_id(-1) {
	}

	inline int getId() const {
		return _id;
	}

	inline const std::string& getName() const {
		return _name;
	}

	inline const std::string& getType() const {
		return _type;
	}
};

/**
 * @brief This is a representation of a behaviour tree node for the serialization
 */
class AIStateNode {
private:
	std::string _name;
	std::string _condition;
	typedef std::vector<AIStateNode> NodeVector;
	NodeVector _children;
	int64_t _lastRun;
	TreeNodeStatus _status;
	bool _currentlyRunning;
public:
	AIStateNode(const std::string& name, const std::string& condition, int64_t lastRun, TreeNodeStatus status, bool currentlyRunning) :
			_name(name), _condition(condition), _lastRun(lastRun), _status(status), _currentlyRunning(currentlyRunning) {
	}

	AIStateNode() :
			_lastRun(-1L), _status(UNKNOWN), _currentlyRunning(false) {
	}

	void addChildren(const AIStateNode& child) {
		_children.push_back(child);
	}

	void addChildren(AIStateNode&& child) {
		_children.push_back(std::move(child));
	}

	inline const std::vector<AIStateNode>& getChildren() const {
		return _children;
	}

	inline std::vector<AIStateNode>& getChildren() {
		return _children;
	}

	inline const std::string& getName() const {
		return _name;
	}

	inline const std::string& getCondition() const {
		return _condition;
	}

	/**
	 * @return The milliseconds since the last execution of this particular node. or @c -1 if it wasn't executed yet
	 */
	inline int64_t getLastRun() const {
		return _lastRun;
	}

	/**
	 * @return The @c TreeNodeStatus of the last execution
	 */
	inline TreeNodeStatus getStatus() const {
		return _status;
	}

	/**
	 * @brief Some nodes have a state that holds which children is currently running
	 * @return Whether this particular node is currently running
	 */
	inline bool isRunning() const {
		return _currentlyRunning;
	}
};

/**
 * @brief This is a representation of a character state for the serialization
 */
class AIStateWorld {
private:
	ai::CharacterId _id;
	ai::Vector3f _position;
	float _orientation;
	CharacterAttributes _attributes;
public:
	AIStateWorld() : _id(-1), _position(0.0f, 0.0f, 0.0f), _orientation(0.0f) {}

	AIStateWorld(const ai::CharacterId& id, const ai::Vector3f& position, float orientation, const CharacterAttributes& attributes) :
			_id(id), _position(position), _orientation(orientation), _attributes(attributes) {
	}

	AIStateWorld(const ai::CharacterId& id, const ai::Vector3f& position, float orientation, CharacterAttributes&& attributes) :
			_id(id), _position(position), _orientation(orientation), _attributes(std::move(attributes)) {
	}

	AIStateWorld(const ai::CharacterId& id, const ai::Vector3f& position, float orientation) :
			_id(id), _position(position), _orientation(orientation) {
	}

	inline bool operator==(const AIStateWorld &other) const {
		return _id == other._id;
	}

	inline bool operator<(const AIStateWorld &other) const {
		return _id < other._id;
	}

	/**
	 * @return The unique id that can be used to identify the character in the world
	 */
	inline const ai::CharacterId& getId() const {
		return _id;
	}

	/**
	 * @return The orientation of the character [0, 2*PI]
	 *
	 * @note A negative value means, that the character does not have any orientation
	 */
	inline float getOrientation() const {
		return _orientation;
	}

	/**
	 * @return The position in the world
	 */
	inline const ai::Vector3f& getPosition() const {
		return _position;
	}

	/**
	 * @return Attributes for the entity
	 */
	inline const CharacterAttributes& getAttributes() const {
		return _attributes;
	}

	/**
	 * @return Attributes for the entity to fill
	 */
	inline CharacterAttributes& getAttributes() {
		return _attributes;
	}
};

}
