#pragma once

#include <string>

using namespace std;

namespace RequestDB {
	inline string getCreateTable()
	{
		return string("CREATE TABLE IF NOT EXISTS product\n\
            (\n\
            Id TEXT PRIMARY KEY NOT NULL,\n\
            Guid TEXT NOT NULL,\n\
            Name TEXT NOT NULL,\n\
            ParentId TEXT NOT NULL,\n\
            RowVer INTEGER NOT NULL,\n\
            loadStamp TEXT NOT NULL,\n\
            IsFull BOOLEAN NOT NULL\n\
            );");
	}

    inline string getInsertHead()
    {
        return string("INSERT INTO product (Id, Guid, Name, ParentId, RowVer, loadStamp, IsFull) VALUES ");
    }

    inline string getInsertBode(std::string guid, std::string id, std::string name, std::string parentId, std::string loadStamp, bool isFull, int rowVer)
    {
        return string("('" + id + "', '" + guid + "', '" + name + "', '" + parentId + "', " + std::to_string(rowVer) + ", '" + loadStamp + "', " + std::to_string(isFull) + ")");
    }

    inline string getDeleteTable()
    {
        return string("DELETE FROM product;");
    }

    inline string getSelectTable()
    {
        return string("SELECT * FROM product;");
    }    
}


