#include "JSON.h"
#include "parson.h"

Json::Json()
{
	json_value = json_value_init_object();
	json_object = json_value_get_object(json_value);
}

Json::Json(const char* data)
{
	this->json_value = json_parse_string(data);
	if (this->json_value != nullptr)
	{
		this->json_object = json_value_get_object(this->json_value);
	}
}

Json::Json(JSON_Object * object)
{
	this->json_object = object;
}

Json::~Json()
{
	json_value_free(json_value);
}

Json Json::GetJSON_object(const char * field) const
{
	return (Json)json_object_get_object(this->json_object, field);
}

const char * Json::GetString(const char * field) const
{
	return json_object_get_string(this->json_object,field);
}

int Json::GetInt(const char * field) const
{
	return (int)json_object_get_number(this->json_object,field);
}



