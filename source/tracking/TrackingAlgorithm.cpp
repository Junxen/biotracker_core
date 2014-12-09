#include "TrackingAlgorithm.h"

#include <fstream>

#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

TrackingAlgorithm::TrackingAlgorithm(Settings &settings, std::string &serializationPath, QWidget *parent)
    : QObject(parent)
    , _settings(settings)
    , _serializationPathName(serializationPath)
{}

TrackingAlgorithm::~TrackingAlgorithm()
{
 	std::cout << "Storing in " << _serializationPathName << std::endl;
	std::ofstream ostream(_serializationPathName, std::ios::binary);
	cereal::JSONOutputArchive archive(ostream);
	prepareSave();
	archive(_trackedObjects);
}

void TrackingAlgorithm::loadObjects(std::vector<TrackedObject>&& objects)
{
	_trackedObjects = std::move(objects);
}

const std::vector<TrackedObject> &TrackingAlgorithm::getObjects() const
{
	return _trackedObjects;
}

std::shared_ptr<QWidget> TrackingAlgorithm::getToolsWidget()
{
	return std::make_shared<QWidget>();
}

std::shared_ptr<QWidget> TrackingAlgorithm::getParamsWidget()
{
	return std::make_shared<QWidget>();
}

bool TrackingAlgorithm::prepareSave()
{
	return true;
}
