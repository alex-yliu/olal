#include <gtest/gtest.h>
#include <lua.hpp>

// Simple Lua test
TEST(LuaTest, LuaRunsCorrectly)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    int result = luaL_dostring(L, "x = 5 + 3");
    EXPECT_EQ(result, LUA_OK);

    lua_getglobal(L, "x");
    int x = (int)lua_tointeger(L, -1);
    EXPECT_EQ(x, 8);

    lua_close(L);
}