#ifndef __JSON_H__
#define __JSON_H__

#include "MathGeoLib\include\MathGeoLib.h"

struct json_object_t;
struct json_value_t;
struct json_array_t;

typedef struct json_object_t JSON_Object;
typedef struct json_value_t  JSON_Value;
typedef struct json_array_t  JSON_Array;

class Json
{
public:
	Json();
	Json(const char* data);
	Json(JSON_Object* object);
	~Json();

	size_t Save(char** buff) const;

	bool AddString(const char* name, const char* string);
	bool AddInt(const char* name, int value);
	bool AddFloat(const char* name, float value);
	bool AddFloatArray(const char * name, const float * value);
	bool AddBool(const char* name, bool value);
	bool AddArray(const char* name);
	bool AddArrayData(const Json& data);


	Json GetJSON_object(const char* field) const;
	const char* GetString(const char* field) const;
	int GetInt(const char* field) const;
	bool GetBool(const char* field) const;
	float GetFloat(const char* field) const;
	float3 GetFloat3(const char* field) const;

	Json GetArray(const char* filed, int id)const;
	size_t GetArraySize(const char* field)const;

private:
	JSON_Value*	 json_value = nullptr;
	JSON_Object* json_object = nullptr;
	JSON_Array*  json_array = nullptr;
};




#endif // !__JSON_H__

