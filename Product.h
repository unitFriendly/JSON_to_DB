#pragma once

#include <string>
#include "nlohmann/json.hpp"

namespace ProductJSON {

	class Product
	{
	private:
		std::string guid;
		std::string id;
		std::string name;
		std::string parentId;
		std::string loadStamp;
		bool isFull;
		int rowVer;

	public:
		Product(std::string _guid, std::string _id, std::string _name, std::string _parentId, std::string _loadStamp, bool _isFull, int _rowVer) : guid(_guid), id(_id), name(_name), parentId(_parentId), loadStamp(_loadStamp), isFull(_isFull), rowVer(_rowVer) {}
		Product() {};

		std::string GetGuid();
		std::string GetId();
		std::string GetName();
		std::string GetParentId();
		std::string GetLoadStamp();
		bool GetIsFull();
		int GetRowVer();

		void SetGuid(std::string _guid);
		void SetId(std::string _id);
		void SetName(std::string _name);
		void SetParentId(std::string _parentId);
		void SetLoadStamp(std::string _loadStamp);
		void SetIsFull(bool _isFull);
		void SetRowVer(int _rowVer);
	};

	void to_json(nlohmann::json& json, Product& product);

	void from_json(const nlohmann::json& json, Product& product);
}

