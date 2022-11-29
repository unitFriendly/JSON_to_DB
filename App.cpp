#include "App.h"

void App::readAllFromDB()
{
    try
    {
        connection.ExecuteQuery(RequestDB::getSelectTable().c_str(), this->callback);

        std::cout << "\tSelect end" << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "\nError: " << ex.what() << std::endl;
        return;
    }
}

void App::writeAllToDB()
{
    std::ifstream srcFile(_pathJSON);

    if (!srcFile.is_open())
    {
        std::cout << "Error: JSON file not found" << std::endl;
        return;
    }

    nlohmann::json json = nlohmann::json::parse(srcFile);
    srcFile.close();

    vector_product_type vectorProduct;

    int counter = 0;

    for (auto& element : json)
    {
        counter++;

        vectorProduct.push_back(std::make_unique<ProductJSON::Product>(element.at("Guid"), element.at("Id"), element.at("Name"), element.at("ParentId"), element.at("loadStamp"), element.at("IsFull"), element.at("RowVer")));

        if (counter >= COUNT_RECORD_AT_TIME)
        {
            try
            {
                connection.ExecuteQuery(makeInsertRequest(vectorProduct).c_str());
            }
            catch (const std::exception& ex)
            {
                std::cout << "\nError: " << ex.what() << std::endl;
                return;
            }            

            vectorProduct.clear();
            counter = 0;
        }
    }

    if (vectorProduct.size() > 0)
    {
        try
        {
            connection.ExecuteQuery(makeInsertRequest(vectorProduct).c_str());
        }
        catch (const std::exception& ex)
        {
            std::cout << "\nError: " << ex.what() << std::endl;
            return;
        }
    }

    std::cout << "\t" << json.size() << " line added" << std::endl;
}

void App::clearDB()
{
    try
    {
        connection.ExecuteQuery(RequestDB::getDeleteTable().c_str());

        std::cout << "\tAll line delete from table" << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "\nError: " << ex.what() << std::endl;
        return;
    }
}

std::string App::makeInsertRequest(vector_product_type& vector)
{
    std::string result = RequestDB::getInsertHead();

    for (vector_product_type::iterator it = vector.begin(); it != vector.end(); it++)
    {
        result += RequestDB::getInsertBode((*it)->GetGuid(), (*it)->GetId(), (*it)->GetName(), (*it)->GetParentId(), (*it)->GetLoadStamp(), (*it)->GetIsFull(), (*it)->GetRowVer()) + ", ";
    }

    *(result.end() - 2) = ';';

    return result;
}

int App::callback(void* data, int argc, char** argv, char** colName)
{
    if (data != nullptr)
    {
        std::cout << data << std::endl;
    }    

    for (int i = 0; i < argc; i++) 
    {
        std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }

    std::cout << std::endl;

    return 0;
}

App::App(std::string pathDB, std::string pathJSON)
{
    DbConnection::SetDefaultFileName("test.db");

    if (!connection.Open())
    {
        std::cout << "Test app start error\n";
    }

    std::cout << "Hello from test app!\n";

    try
    {
        connection.ExecuteQuery(RequestDB::getCreateTable().c_str());
    }
    catch (const std::exception& ex)
    {
        std::cout << "\nError: " << ex.what() << std::endl;
        return;
    }    

    functionality["read"] = [this]() {this->readAllFromDB(); };
    functionality["write"] = [this]() {this->writeAllToDB(); };
    functionality["clear"] = [this]() {this->clearDB(); };
    functionality["close"] = []() {};

    _pathJSON = pathJSON;
}

App::~App()
{
    connection.Close();
}

void App::Start()
{
    auto itMap = functionality.end();

    std::string cmd = "";

    while (cmd.compare("close"))
    {
        std::cout << "\nSelect action:\n\t\"read\" - read from the database\n\t\"write\" - write to the database\n\t\"clear\" - clear the database\n\t\"close\" - close test app\nYour choice: ";
        std::cin >> cmd;

        itMap = functionality.find(cmd);
        if (itMap != functionality.end())
        {
            functionality[cmd]();
        }
        else
        {
            std::cout << "Error: unidentified command, try again" << std::endl;
        }
    }
}
