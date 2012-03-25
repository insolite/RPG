#include "StdAfx.h"
#include "CurrentNPC.h"
#include "Game.h"

CurrentNPC::CurrentNPC(std::map<std::string, std::string> strings, std::map<std::string, int> integers) : CurrentMapObject<NPC>::CurrentMapObject(strings, integers)
{
	
	//integers["hp"] = sqlite3_column_int(Game::instance->db, id);
	
}

CurrentNPC::~CurrentNPC(void)
{

}
