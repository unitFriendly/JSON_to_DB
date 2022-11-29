#include "Product.h"

std::string ProductJSON::Product::GetGuid()
{
	return this->guid;
}

std::string ProductJSON::Product::GetId()
{
	return this->id;
}

std::string ProductJSON::Product::GetName()
{
	return this->name;
}

std::string ProductJSON::Product::GetParentId()
{
	return this->parentId.empty() ? "" : this->parentId;
}

std::string ProductJSON::Product::GetLoadStamp()
{
	return this->loadStamp;
}

bool ProductJSON::Product::GetIsFull()
{
	return this->isFull;
}

int ProductJSON::Product::GetRowVer()
{
	return this->rowVer;
}

void ProductJSON::Product::SetGuid(std::string _guid)
{
	this->guid = _guid;
}

void ProductJSON::Product::SetId(std::string _id)
{
	this->id = _id;
}

void ProductJSON::Product::SetName(std::string _name)
{
	this->name = _name;
}

void ProductJSON::Product::SetParentId(std::string _parentId)
{
	this->parentId = _parentId;
}

void ProductJSON::Product::SetLoadStamp(std::string _loadStamp)
{
	this->loadStamp = _loadStamp;
}

void ProductJSON::Product::SetIsFull(bool _isFull)
{
	this->isFull = _isFull;
}

void ProductJSON::Product::SetRowVer(int _rowVer)
{
	this->rowVer = _rowVer;
}

void ProductJSON::to_json(nlohmann::json& json, Product& product)
{
	json = nlohmann::json{ {"Guid", product.GetGuid()}, {"Id", product.GetId()}, {"IsFull", product.GetIsFull()}, {"Name", product.GetName()}, {"ParentId", product.GetParentId()}, {"RowVer", product.GetRowVer()}, {"loadStamp", product.GetLoadStamp()} };
}

void ProductJSON::from_json(const nlohmann::json& json, Product& product)
{
	product.SetGuid(json.at("Guid"));
	product.SetId(json.at("Id"));
	product.SetIsFull(json.at("IsFull"));
	product.SetName(json.at("Name"));
	product.SetParentId(json.at("ParentId"));
	product.SetRowVer(json.at("RowVer"));
	product.SetLoadStamp(json.at("loadStamp"));
}
