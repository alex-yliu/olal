#include <gtest/gtest.h>
#include <sqlite3.h>
#include <lua.hpp>

TEST(SQLiteTest, BasicDatabaseOps)
{
    sqlite3 *db = nullptr;
    ASSERT_EQ(sqlite3_open(":memory:", &db), SQLITE_OK);

    const char *create_stmt = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    ASSERT_EQ(sqlite3_exec(db, create_stmt, 0, 0, nullptr), SQLITE_OK);

    const char *insert_stmt = "INSERT INTO test (value) VALUES ('Hello, Lua!');";
    ASSERT_EQ(sqlite3_exec(db, insert_stmt, 0, 0, nullptr), SQLITE_OK);

    sqlite3_stmt *stmt;
    ASSERT_EQ(sqlite3_prepare_v2(db, "SELECT value FROM test WHERE id = 1;", -1, &stmt, nullptr), SQLITE_OK);
    ASSERT_EQ(sqlite3_step(stmt), SQLITE_ROW);

    std::string value = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    EXPECT_EQ(value, "Hello, Lua!");

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
