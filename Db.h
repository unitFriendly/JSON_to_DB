#pragma once

#include "libs/sqlite3/sqlite3.h"
#include <string>

namespace Db
{
	bool SetTimeout(sqlite3* db, int timeoutSec = 10, bool throwEx = false);
	bool ExecuteQuery(const char* sql, sqlite3* db = 0, bool throwEx = false, int timeoutSec = 10);
	bool ExecuteQueryA(std::string sql, int timeoutSec = 10);

	bool ExecuteQuery(const char* sql, int (*callback)(void*, int, char**, char**), sqlite3* db = 0, bool throwEx = false, int timeoutSec = 10);
};

