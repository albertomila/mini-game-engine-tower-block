#include "stdafx.h"
#include <Game/Settings/SaveData.h>

void SSaveDataRankingDescriptor::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "playTimeId", _playTimeId);
	SERIALIZE(node, "points", _points);
	SERIALIZE(node, "meters", _meters);
}

void SSaveDataRankingDescriptor::OnSave(pugi::xml_node& node)
{
	DESERIALIZE(node, "points", _points);
	DESERIALIZE(node, "meters", _meters);
}

void SSaveDataDescriptor::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "nextPlayTimeId", _nextPlayTimeId);
	SERIALIZE(node, "ranking", _ranking);
}

void SSaveDataDescriptor::OnSave(pugi::xml_node& node)
{
	DESERIALIZE(node, "nextPlayTimeId", _nextPlayTimeId);
	DESERIALIZE(node, "ranking", _ranking);
}

void SSaveDataDescriptor::AddRanking(float meters, int points)
{
	_ranking.emplace_back();
	SSaveDataRankingDescriptor& saveDataRankingDescriptor = _ranking.back();
	saveDataRankingDescriptor._playTimeId = _nextPlayTimeId;
	saveDataRankingDescriptor._meters = meters;
	saveDataRankingDescriptor._points = points;

	++_nextPlayTimeId;
}

void CSaveDataController::Load(const std::string& fileName)
{
	_saveDataDescriptor.Load(fileName);
}

void CSaveDataController::AddRanking(float meters, int points)
{
	_saveDataDescriptor.AddRanking(meters, points);
}

void CSaveDataController::Save(const std::string& fileName)
{
	_saveDataDescriptor.Save(fileName);
}

int CSaveDataController::GetNextPlayTimeId() const
{
	return _saveDataDescriptor._nextPlayTimeId;
}

std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> CSaveDataController::GetRankingSortedByMeters()
{
	using TRanking = std::reference_wrapper<SSaveDataRankingDescriptor>;

	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> sortedRank = GetRankingReference();
	std::sort(std::begin(sortedRank), std::end(sortedRank), [](const TRanking& element1, const TRanking& element2)
	{
		return element1.get()._meters < element2.get()._meters;
	});

	return sortedRank;
}

std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> CSaveDataController::GetRankingSortedByPoints()
{
	using TRanking = std::reference_wrapper<SSaveDataRankingDescriptor>;

	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> sortedRank = GetRankingReference();
	std::sort(std::begin(sortedRank), std::end(sortedRank), [](const TRanking& element1, const TRanking& element2)
	{
		return element1.get()._points < element2.get()._points;
	});

	return sortedRank;
}

std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> CSaveDataController::GetRankingReference()
{
	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> referenceRanking;
	for (SSaveDataRankingDescriptor& descriptor : _saveDataDescriptor._ranking)
	{
		referenceRanking.push_back(std::ref(descriptor));
	}

	return referenceRanking;
}

