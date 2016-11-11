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

size_t Json::Save(char ** buff) const
{
	size_t size = json_serialization_size_pretty(this->json_value);
	*buff = new char[size];
	json_serialize_to_buffer_pretty(this->json_value, *buff, size);

	return size;
}

bool Json::AddString(const char * name, const char * string)
{
	return json_object_set_string(this->json_object, name,string) == JSONSuccess;
}

bool Json::AddInt(const char * name, int value)
{
	return json_object_set_number(this->json_object,name,value) == JSONSuccess;
}

bool Json::AddFloat(const char * name, float value)
{
	return json_object_set_number(this->json_object, name, value) == JSONSuccess;
}

bool Json::AddFloatArray(const char * name, const float* value)
{
	if (value != nullptr)
	{
		JSON_Value* tmp_value = json_value_init_array();
		JSON_Array* tmp_array = json_value_get_array(tmp_value);

		for (unsigned int i = 0; i < 3; i++)
		{
			json_array_append_number(tmp_array, (double)value[i]);
		}
		return json_object_set_value(this->json_object,name,tmp_value) == JSONSuccess;
	}

	return false;
}

bool Json::AddBool(const char * name, bool value)
{
	return json_object_set_boolean(this->json_object,name,value) == JSONSuccess;
}

bool Json::AddArray(const char * name)
{
	JSON_Value* value = json_value_init_array();
	this->json_array = json_value_get_array(value);

	return json_object_set_value(this->json_object, name, value) == JSONSuccess;
}

bool Json::AddArrayData(const Json & data)
{
	if (this->json_array != nullptr)
	{
		return json_array_append_value(this->json_array, json_value_deep_copy(data.json_value)) == JSONSuccess;
	}
	return false;
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

bool Json::GetBool(const char * field) const
{
	return json_object_get_boolean(this->json_object, field);
}

float Json::GetFloat(const char * field) const
{
	return (float) json_object_get_number(this->json_object,field);
}

float3 Json::GetFloat3(const char * field) const
{
	float3 ret = float3::zero;
	JSON_Array* tmp_array = json_object_get_array(this->json_object, field);
	
	if (tmp_array != nullptr)
	{
		ret = float3((float)json_array_get_number(tmp_array, 0), (float)json_array_get_number(tmp_array, 1), (float)json_array_get_number(tmp_array, 2));
	}

	return ret;
}

Json Json::GetArray(const char * field, int id) const
{
	Json ret;
	JSON_Array* tmp_array = json_object_get_array(this->json_object, field);
	if (tmp_array != nullptr)
	{
		ret = Json(json_array_get_object(tmp_array, id));
	}

	return ret;
}

size_t Json::GetArraySize(const char * field) const
{
	size_t ret = -1;
	JSON_Array* tmp_array = json_object_get_array(this->json_object, field);
	if (tmp_array != nullptr)
	{
		ret = json_array_get_count(tmp_array);
	}

	return ret;
}





