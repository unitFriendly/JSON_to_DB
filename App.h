#pragma once

#include "DbConnection.h"
#include <string>
#include <iostream>
#include "libs/sqlite3/sqlite3.h"
#include "RequestDB.h"
#include <map>
#include <vector>
#include <memory>
#include "Product.h"
#include <fstream>

#define COUNT_RECORD_AT_TIME 50

class App
{
private:
	using vector_product_type = std::vector<std::unique_ptr<ProductJSON::Product>>;

	DbConnection connection;
	map<std::string, std::function<void()>> functionality;

	std::string _pathJSON;

	void readAllFromDB();
	void writeAllToDB();
	void clearDB();

	std::string makeInsertRequest(vector_product_type& vector);

	static int callback(void* data, int argc, char** argv, char** colName);

public:
	App(std::string pathDB = "test.db", std::string pathJSON = "././data.json");
	~App();

	void Start();

	

};

