/*
 *c 调用lua模板引擎
 *作者:liweijian
 *日期:20140503
 */
#include <stdio.h>
#include "luasrc/lua.h"
#include "luasrc/lualib.h"
#include "luasrc/lauxlib.h"

struct _user_table_item
{
  const  char  *key;
  const  char  *value;
}user[2]={
    { "name","<world>"},
    {"id","18888888"}
};

typedef struct _user_table_item user_table_item;

#define user_table user_table_item[1]


void
loadfile(lua_State *L, const char* filename)
{
    if(luaL_loadfile(L,filename)||lua_pcall(L,0,0,0))
    {
        printf("Error Msg is %s\n",lua_tostring(L,-1));
        return;
    }

    /*
     * 用全局变量来传递table
    lua_newtable(L);
    lua_pushstring(L,user.key);
    lua_pushstring(L,user.value);
    lua_settable(L,-3);
    lua_setglobal(L,"u");
    */

    lua_getglobal(L,"htmlrender");
    //压入第一个参数
    lua_pushstring(L,"/home/lwj/code/lua/luc/chelloworld/lualib/tmp.tmpl");
    //压入第二个参数
    //通过函数参数来传递table
    lua_newtable(L);
    lua_pushstring(L,user[0].key);
    lua_pushstring(L,user[0].value);
    lua_settable(L,-3);
    lua_pushstring(L,user[1].key);
    lua_pushstring(L,user[1].value);
    lua_settable(L,-3);


    if(lua_pcall(L,2,1,0) != 0)
    {
        printf("Error Msg is %s\n",lua_tostring(L,-1));
        return;
    }

    //取结果
    const char *r = lua_tostring(L,-1);
    lua_pop(L,1);
    printf("reslut is:\n %s",r);
}

int
main (void)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    loadfile(L,"lualib/test.lua");
    lua_close(L);
    return 0;
}
