#include <stdio.h>
#include <json-c/json.h>
#include <json-c/json_object.h>

/*Json对象的类型
json_type_object, "名称/值"对的集合

json对象的值的类型
json_type_boolean,
json_type_double,
json_type_int,
json_type_array, “值”的集合
json_type_string
*/
/*     json是外来库，编译时要+ -ljson-c */

int main()
{
    //创建json对象
    struct json_object *jsonObj = json_object_new_object();
    
    //创建json_type_int值类型int对象
    struct json_object * jsonVal = json_object_new_int(12);

    //添加对象域到json对象中
    #if 1
    json_object_object_add(jsonObj, "陈", jsonVal);
    json_object_object_add(jsonObj, "李", json_object_new_string("cheng"));
    json_object_object_add(jsonObj, "王", json_object_new_string("adder"));

    /* 从json中按名字取一个对象 */
    /* 取出整型 */
    struct json_object * json11 = json_object_object_get(jsonObj,"陈");
    int val1 = json_object_get_int(json11);
    printf("val:%d\n", val1);
    //取出字符串
    struct json_object * json12 = json_object_object_get(jsonObj,"李");
    const char *str1 = json_object_get_string(json12);
    printf("str1:%s\n", str1);

    /* 将json_object内容转换json格式字符串，其中可能含有转义符。 */
    const char *obj = json_object_to_json_string(jsonObj);
    printf("obj:%s\n", obj);

    /* 删除key值对应json对象 */
    json_object_object_del(jsonObj, "王");
    const char *objAfterDel = json_object_to_json_string(jsonObj);
    printf("objAfterDel:%s\n", objAfterDel);
    
    /* 获取json的长度 */
    int len = json_object_object_length(jsonObj);
    printf("len:%d\n", len);

    printf("\n遍历:\n");
    json_object_object_foreach(jsonObj, key, val)
    {
        printf("%s:%s\t", key, json_object_to_json_string(val));
    }
    printf("\n\n");
    #endif

    /* 由str里的JSON字符串生成JSON对象，str是json_object_to_json_string() 生成的。
   参数：str – json字符串 */
    struct json_object * josntok = json_tokener_parse(objAfterDel); 
    struct json_object * josntok1 = json_object_object_get(josntok, "陈"); 
    struct json_object * josntok2 = json_object_object_get(josntok, "李"); 

    /* 由str里的JSON字符串生成JSON对象 */
    char * strPre = "{\"张三\":3, \"李四\": \"lisi\"}";
    struct json_object * jsonObj2 = json_tokener_parse(strPre); 
    printf("strPre:%s\n", strPre);

    //创建json数组
    #if 1

    /* 创建空的json_type_array 类型JSON数组值类型对象 */
    struct json_object * my_array = json_object_new_array();

    /* 添加一元素在json对象数组末端  */
    json_object_array_add(my_array, jsonObj);
    json_object_array_add(my_array, jsonObj2);

    /* 在指定的json对象数组下标插入或替代一个json */
    // int n = json_object_array_put_idx(my_array, 2, );
    json_object_array_put_idx(my_array, 2, json_object_new_string("yeliange"));


    /* 从数组中，按下标取JSON值对象 */
    /* 遍历json对象集合 */
    len = json_object_array_length(my_array);
    printf("len:%d\n",len);
    for(int i = 0; i < len; i++)
    {
        json_object *jitem = json_object_array_get_idx(my_array, i);
        const char * str = json_object_get_string(jitem);
        printf("my_array[%d]:%s\n", i, str);
    }
    //从数组取出单个值
    json_object *jitem = json_object_array_get_idx(my_array, 1);
    /* 从object取出对象 */
    json_object *jVal = json_object_object_get(jitem, "张三");
    int jitemVal = json_object_get_int(jVal);
    printf("jitemVal:%d\n", jitemVal);
   
    /* 销毁json对象 */ 
    // jobj&jobj2变成了jsonObj的子节点不需要释放，释放jarr即可
    json_object_put(jsonObj);

    #if 0
    /* 创建空json对象值数组类型 */
    struct json_object * my_Arr = json_object_new_array();
    /* 添加json值类型到数组中 */
    json_object_array_add(my_Arr, json_object_new_int(1));
    json_object_array_add(my_Arr, json_object_new_int(2));
    json_object_array_add(my_Arr, json_object_new_int(3));
    json_object_array_put_idx(my_Arr, 3, json_object_new_string("yeliange"));
    printf("my_Arr:\n");
    for(int i = 0; i < json_object_array_length(my_Arr); i++)
    {
        struct json_object * obj1 = json_object_array_get_idx(my_Arr, i);
        const char * ptr = json_object_to_json_string(obj1);
        printf("ptr:%s\n", ptr);
    }
    json_object_put(my_Arr);
    #endif

    #endif

    // 添加json名称和值到json对象
    #if 0
    struct json_object * my_object = json_object_new_object();

    json_object_object_add(my_object, "一", json_object_new_int(1));
    json_object_object_add(my_object, "二", json_object_new_int(2));
    json_object_object_add(my_object, "三", json_object_new_int(3));

    int my_len = json_object_object_length(my_object);
    printf("my_len:%d\n", my_len);
   
    // struct josn_object *item = json_object_(my_array, i);
    const char * ptr2 = json_object_to_json_string(my_object);
    printf("my_array:%s\n", ptr2);

    json_object_put(my_object);
    #endif
    return 0;
} 