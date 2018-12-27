#include "stdafx.h"
#include <Game/AppConfig.h>

void CAppConfig::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "pathGameConfig", _pathGameConfig);
}
