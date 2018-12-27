#include "stdafx.h"
#include <Engine/Serialization/ISerializable.h>

void CSerializableObject::Load(const std::string& fileName)
{
	pugi::xml_document rootDocument;
	pugi::xml_parse_result result = rootDocument.load_file(fileName.c_str());
	if (result)
	{
		pugi::xml_node node = rootDocument.child("dbObject");
		LoadXmlNode(node);
	}
}

void CSerializableObject::LoadXmlNode(pugi::xml_node& node)
{
	_rootNode = node;
	OnLoad(_rootNode);
}

void CSerializableObject::Save(const std::string& fileName)
{
	pugi::xml_document rootDocument;
	pugi::xml_node newNode = rootDocument.append_child("dbObject");
	SaveXmlNode(newNode);
	rootDocument.save_file(fileName.c_str());
}

void CSerializableObject::SaveXmlNode(pugi::xml_node& node)
{
	OnSave(node);
}
