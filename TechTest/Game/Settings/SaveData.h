#pragma once
#include <Engine/Serialization/ISerializable.h>
#include <Engine/Core/Singleton.h>

struct SSaveDataRankingDescriptor : public CSerializableObject
{
	void OnLoad(pugi::xml_node& node) override;
	void OnSave(pugi::xml_node& node) override;

	int _playTimeId = 0;
	int _points = 0;
	double _meters = 0.0f;
};

struct SSaveDataDescriptor : public CSerializableObject
{
	void OnLoad(pugi::xml_node& node) override;
	void OnSave(pugi::xml_node& node) override;
	void AddRanking(double meters, int points);

	int _nextPlayTimeId = 0;
	std::vector<SSaveDataRankingDescriptor> _ranking;
};

class CSaveDataController
{
public:
	void Load(const std::string& fileName);
	void AddRanking(double meters, int points);
	void Save();
	int GetNextPlayTimeId() const;

	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> GetRankingSortedByMeters();
	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> GetRankingSortedByPoints();

private:
	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> GetRankingReference();

	SSaveDataDescriptor _saveDataDescriptor;
	std::string _fileName;
};