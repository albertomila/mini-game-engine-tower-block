#pragma once
#include <Engine\Serialization\ISerializable.h>
#include <Engine\Singleton.h>

struct SSaveDataRankingDescriptor : public CSerializableObject
{
	void OnLoad(pugi::xml_node& node) override;
	void OnSave(pugi::xml_node& node) override;

	int _points = 0;
	float _meters = 0.0f;
};

struct SSaveDataDescriptor : public CSerializableObject
{
	void OnLoad(pugi::xml_node& node) override;
	void OnSave(pugi::xml_node& node) override;
	void AddRanking(float meters, int points);

	std::vector<SSaveDataRankingDescriptor> _ranking;
};

class CSaveDataController
{
public:
	void Load(const std::string& fileName);
	void AddRanking(float meters, int points);
	void Save(const std::string& fileName);


	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> GetRankingSortedByMeters();
	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> GetRankingSortedByPoints();

private:
	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> GetRankingReference();

	SSaveDataDescriptor _saveDataDescriptor;
};