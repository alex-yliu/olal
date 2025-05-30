//
//  main.cpp
//  yunfeng
//
//  Created by Yunfeng Liu on 2022-06-23.
//

#include <iostream>
#include <sodium.h>
#include <sqlite3.h>
#include <lua.hpp>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include "lib/account.hpp"
#include "lib/key_pair.hpp"

using namespace olal;

// auto mainKey = std::make_shared<Ed25519KeyPair>();
// auto account = Account(mainKey);

// auto delegate1 = std::make_shared<Ed25519KeyPair>();
// auto delegate2 = std::make_shared<Ed25519KeyPair>();

// account.addDelegateKey(delegate1);
// account.addDelegateKey(delegate2);

// if (account.hasDelegateKey(delegate1->getPublicKeyBase58())) {
//     std::cout << "Delegate recognized." << std::endl;
// }

int main(int argc, const char *argv[])
{
    spdlog::info("Starting olal core");
    // insert code here...
    if (sodium_init() < 0)
    {
        return -1;
    }
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "../lua/smart_contract.lua") != LUA_OK)
    {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
    }

    lua_close(L);
    return 0;
    // sqlite3 *db;
    // char *zErrMsg = 0;
    // int rc;
    // char *sql;
    // /* Open database */
    // rc = sqlite3_open("test.db", &db);

    // //    auto ppp = test_ext();
    // //    std::cout << "type: " << static_cast<int>(ppp.tx.header.type) << static_cast<int>(ppp.tx.header.state) << "Hello, World!\n";
    // return 0;
}
