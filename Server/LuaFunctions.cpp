#include "stdafx.h"
#include "Universe.h"
#include "LuaFunctions.h"

void LuaFunctions::RegisterFunctions(lua_State* luaState)
{
	lua_register(luaState, "SayHello", SayHello);
	lua_register(luaState, "GetQuestState", GetQuestState);
	lua_register(luaState, "AddNPC", AddNPC);
	lua_register(luaState, "AddItem", AddItem);
	lua_register(luaState, "SendDialog", SendDialog);
}

int LuaFunctions::SayHello(lua_State* lua) //str
{
	int n = lua_gettop(lua);
	if (n < 1)
	{
		lua_pushstring(lua, "Incorrect arguments count");
		lua_error(lua);
		return 1;
	}
	if (!lua_isstring(lua, 1))
	{
		lua_pushstring(lua, "Incorrect argument");
		lua_error(lua);
		return 2;
	}
	printf("Character saying: '%s'\n", lua_tostring(lua, 1));
	return 0;
}

int LuaFunctions::GetQuestState(lua_State* lua) //currentCharacterId, questId
{
	int currentCharacterId, questId;
	CurrentCharacter* currentCharacter;
	CurrentQuest* currentQuest;

	currentCharacterId = lua_tointeger(lua, 1);
	questId = lua_tointeger(lua, 2);
	//TODO: data->GetCharacter
	for (int i = 0; i < Universe::instance->game->data->locationsCount; i++)
		if (currentCharacter = Universe::instance->game->data->locations[i]->GetCharacter(currentCharacterId))
		{
			currentQuest = currentCharacter->GetQuest(questId); //TODO: method for baseId
			if (currentQuest)
				return currentQuest->state;
			else
				return 0; //No current quest
		}
	return -1; //No current character
}

int LuaFunctions::AddNPC(lua_State* lua) //baseId, x, y, locationId, ...
{
	int baseId, x, y, locationId;
	CurrentNPC* currentNPC;
	char outPacket[256];
	Location* currentLocation;

	baseId = lua_tointeger(lua, 1);
	x = lua_tointeger(lua, 2);
	y = lua_tointeger(lua, 3);
	locationId = lua_tointeger(lua, 4);

	currentLocation = Universe::instance->game->data->GetLocation(locationId);
	currentNPC = currentLocation->AddNPC(Universe::instance->game->resources->GetNPC(baseId), x, y);
	CreatePacket(outPacket, NPCSpawned, "%i%i%i%i",
		currentNPC->id,
		currentNPC->base->id,
		currentNPC->x,
		currentNPC->y
		);
	for (int i = 0; i < currentLocation->currentCharactersCount; i++)
		currentLocation->currentCharacters[i]->connectSocket->Send(outPacket);

	return currentNPC->id;
}

int LuaFunctions::AddItem(lua_State* lua) //baseId, spawnType, [x, y, locationId | characterId], count, ...
{
	int baseId;
	int count;
	CurrentItem* currentItem;
	char outPacket[256];
	SpawnType spawnType;

	baseId = lua_tointeger(lua, 1);
	spawnType = (SpawnType)lua_tointeger(lua, 2);

	switch (spawnType)
	{
		case Ground:
		{
			int x, y, locationId;
			Location* currentLocation;

			x = lua_tointeger(lua, 3);
			y = lua_tointeger(lua, 4);
			locationId = lua_tointeger(lua, 5);
			count = lua_tointeger(lua, 6);

			currentLocation = Universe::instance->game->data->GetLocation(locationId);
			currentItem = currentLocation->AddItem(Universe::instance->game->resources->GetItem(baseId), x, y, count);
			CreatePacket(outPacket, ItemSpawned, "%i%i%i%i%b%i",
				currentItem->id,
				currentItem->base->id,
				currentItem->x,
				currentItem->y,
				Ground,
				currentItem->count
				);
			for (int i = 0; i < currentLocation->currentCharactersCount; i++)
				currentLocation->currentCharacters[i]->connectSocket->Send(outPacket);
			break;
		}
		case Inventory:
		{
			int characterId;
			CurrentCharacter* currentCharacter;

			characterId = lua_tointeger(lua, 3);
			count = lua_tointeger(lua, 4);

			//TODO: data->GetCharacter
			currentCharacter = NULL;
			for (int i = 0; i < Universe::instance->game->data->locationsCount; i++)
				if (currentCharacter = Universe::instance->game->data->locations[i]->GetCharacter(characterId))
					break;
			currentItem = currentCharacter->AddItem(Universe::instance->game->resources->GetItem(baseId), count);
			CreatePacket(outPacket, ItemSpawned, "%i%i%i%i%b%i",
				currentItem->id,
				currentItem->base->id,
				0,
				0,
				Inventory,
				currentItem->count
				);
			currentCharacter->connectSocket->Send(outPacket);
			break;
		}
	}

	return currentItem->id;
}

int LuaFunctions::SendDialog(lua_State* lua) //currentNPCId, title, text, currentCharacterId
{
	int currentNPCId;
	char title[256];
	char text[512];
	int currentCharacterId;
	CurrentCharacter* currentCharacter;
	
	currentNPCId = lua_tointeger(lua, 1);
	strcpy(title, lua_tostring(lua, 2));
	strcpy(text, lua_tostring(lua, 3));
	currentCharacterId = lua_tointeger(lua, 4);

	//TODO: data->GetCharacter
	currentCharacter = NULL;
	for (int i = 0; i < Universe::instance->game->data->locationsCount; i++)
		if (currentCharacter = Universe::instance->game->data->locations[i]->GetCharacter(currentCharacterId))
			break;

	if (currentCharacter)
	{
		char outPacket[256];

		CreatePacket(outPacket, DialogOpened, "%i%s%s", currentNPCId, title, text);
		currentCharacter->connectSocket->Send(outPacket);
	}

	return 0;
}
