namespace LuaFunctions
{

void RegisterFunctions(lua_State* luaState);

int SayHello(lua_State* lua);
int GetQuestState(lua_State* lua);
int AddItem(lua_State* lua);
int AddNPC(lua_State* lua);
int SendDialog(lua_State* lua);
int PlayEffect(lua_State* lua);
int ChangeHp(lua_State *lua);
}
