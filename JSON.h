#ifndef __JSON_H__
#define __JSON_H__

struct json_object_t;
struct json_value_t;

typedef struct json_object_t JSON_Object;
typedef struct json_value_t  JSON_Value;

class Json
{
public:
	Json();
	Json(const char* data);
	~Json();

	const char* GetString(const char* field) const;

private:
	JSON_Value*	 json_value = nullptr;
	JSON_Object* json_object = nullptr;
};




#endif // !__JSON_H__

