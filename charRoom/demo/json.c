#include <json-c/json_object.h>
#include <json-c/json.h>
#include <stdio.h>

int main()
{
    json_object *friend = json_object_new_object();
    
    json_object_object_add(friend, "张三", json_object_new_string("在线"));
    json_object_object_add(friend, "李四", json_object_new_string("离线"));
    #if 0
    printf("friends:%s\n", json_object_to_json_string(friend));
    #endif
    
    json_object *name = json_object_object_get(friend, "张三");
    const char * state = json_object_get_string(name);

    printf("张三的状态：%s\n", state);

}