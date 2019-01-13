#pragma once

#include <libs/pugixml/pugixml.hpp>

#include <vector>

class ISerializable
{
public:
	virtual void Load(const std::string& fileName) = 0;
	virtual void LoadXmlNode(pugi::xml_node& node) = 0;
	virtual void OnLoad(pugi::xml_node& node) = 0;

	virtual void Save(const std::string& fileName) = 0;
	virtual void SaveXmlNode(pugi::xml_node& node) = 0;
	virtual void OnSave(pugi::xml_node& node) = 0;
};

class CSerializableObject : public ISerializable
{
public:
	void Load(const std::string& fileName) override;
	void LoadXmlNode(pugi::xml_node& node) override;
	void Save(const std::string& fileName) override;
	void SaveXmlNode(pugi::xml_node& node) override;
	void OnSave(pugi::xml_node& node) override {}

private:
	pugi::xml_node _rootNode;
};


template<class TEnumType>
struct SSerializatorEnum
{
	static void Serialize(const pugi::xml_node& node, const char* key, TEnumType& member)
	{
		member = static_cast<TEnumType>(node.attribute(key).as_int(static_cast<int>(member)));
	}
};

template<class T>
struct SSerializatorTraits
{
	static void Serialize(const pugi::xml_node& node, const char* key, T& member)
	{
		pugi::xml_node childNode = node.child(key);
		member.LoadXmlNode(childNode);
	}
};

template<class T>
struct SSerializatorTraits<std::vector<T>>
{
	static void Serialize(const pugi::xml_node& node, const char* key, std::vector<T>& member)
	{
		const pugi::xml_node groupNode = node.child(key);

		for (pugi::xml_node_iterator it = groupNode.begin(); it != groupNode.end(); ++it)
		{
			member.emplace_back();
			T& newValue = member.back();
			pugi::xml_node childNode = *it;
			newValue.LoadXmlNode(childNode);
		}
	}
};

template<>
struct SSerializatorTraits<int>
{
	static void Serialize(const pugi::xml_node& node, const char* key, int& member)
	{
		member = node.attribute(key).as_int(member);
	}
};

template<>
struct SSerializatorTraits<bool>
{
	static void Serialize(const pugi::xml_node& node, const char* key, bool& member)
	{
		member = node.attribute(key).as_bool(member);
	}
};

template<>
struct SSerializatorTraits<float>
{
	static void Serialize(const pugi::xml_node& node, const char* key, float& member)
	{
		member = node.attribute(key).as_float(member);
	}
};

template<>
struct SSerializatorTraits<double>
{
	static void Serialize(const pugi::xml_node& node, const char* key, double& member)
	{
		member = node.attribute(key).as_double(member);
	}
};

template<>
struct SSerializatorTraits<long long>
{
	static void Serialize(const pugi::xml_node& node, const char* key, long long& member)
	{
		member = node.attribute(key).as_llong(member);
	}
};

template<>
struct SSerializatorTraits<std::string>
{
	static void Serialize(const pugi::xml_node& node, const char* key, std::string& member)
	{
		member = node.attribute(key).as_string(member.c_str());
	}
};

template<class TXmlNode, class TMember>
void SERIALIZE(TXmlNode& xmlNode, const char* keyId, TMember& memberRef)
{
	SSerializatorTraits<TMember>::Serialize(xmlNode, keyId, memberRef);
}

template<class TXmlNode, class TMember>
void SERIALIZE_ENUM(TXmlNode& xmlNode, const char* keyId, TMember& memberRef)
{
	SSerializatorEnum<TMember>::Serialize(xmlNode, keyId, memberRef);
}


template<class T>
struct SDeserializatorTraits
{
	static void Deserialize(pugi::xml_node& node, const char* key, T& member)
	{
		node.append_attribute(key).set_value(member);
	}
};

template<class T>
struct SDeserializatorTraits<std::vector<T>>
{
	static void Deserialize(pugi::xml_node& node, const char* key, std::vector<T>& member)
	{
		pugi::xml_node newNode = node.append_child(key);

		for (ISerializable& serializableObject : member)
		{
			pugi::xml_node newElementNode = newNode.append_child("element");
			serializableObject.SaveXmlNode(newElementNode);
		}
	}
};

template<class TXmlNode, class TMember>
void DESERIALIZE(TXmlNode& xmlNode, const char* keyId, TMember& memberRef)
{
	SDeserializatorTraits<TMember>::Deserialize(xmlNode, keyId, memberRef);
}