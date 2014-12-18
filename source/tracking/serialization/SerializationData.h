#pragma once

#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

#include "source/tracking/algorithm/algorithms.h"
#include "TrackedObject.h"
#include "types.hpp"

namespace Serialization {
class Data {
public:
	// default ctor required for serialization
	Data() {}

	Data(const std::string& type,
		 const std::string& fileSha1Hash,
		 const std::vector<std::string>& filenames,
		 const std::vector<TrackedObject>& trackedObjects)
		: _trackerType(type)
		, _fileSha1Hash(fileSha1Hash)
		, _filenames(filenames)
		, _trackedObjects(trackedObjects)
	{}

	Data(const std::string& type,
		 const std::string& fileSha1Hash,
		 const std::vector<std::string>&& filenames,
		 const std::vector<TrackedObject>&& trackedObjects)
		: _trackerType(type)
		, _fileSha1Hash(fileSha1Hash)
		, _filenames(std::move(filenames))
		, _trackedObjects(std::move(trackedObjects))
	{}

	std::string const& getType() const { return _trackerType; }
	std::string const& getFileSha1Hash() const { return _fileSha1Hash; }
	std::vector<std::string> const& getFilenames() const { return _filenames; }
	std::vector<TrackedObject> const& getTrackedObjects() const { return _trackedObjects; }

private:
	const std::string _trackerType;
	const std::string _fileSha1Hash;
	const std::vector<std::string> _filenames;
	const std::vector<TrackedObject> _trackedObjects;

	friend class cereal::access;
	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(CEREAL_NVP(_trackerType),
		   CEREAL_NVP(_fileSha1Hash),
		   CEREAL_NVP(_filenames),
		   CEREAL_NVP(_trackedObjects));
	}
};
}
