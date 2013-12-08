#include "city.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <string.h>
}

#define LUA_CITYHASH_VERSION "1.0-1"

const char kHexDigits[] = "0123456789abcdef";

static char * create_hex_result(char *src, size_t len, char *result) {
  char *p = result;
  for (size_t i = 0; i < len; i++) {
    *p++ = kHexDigits[((src[i] >> 4) & 0xf)];
    *p++ = kHexDigits[(src[i] & 0xf)];
  }
  return result;
}

static int l_hash64(lua_State *L) {
  char buf[32] = { 0 };
  size_t len;
  const char *key = luaL_checklstring(L, 1, &len);
  uint64 result = CityHash64WithSeed(key, luaL_optinteger(L, 2, len), (uint64) luaL_optnumber(L, 4, 0));
  if (lua_toboolean(L, 3)) {
    lua_pushlstring(L, create_hex_result((char *) &result, sizeof(result), buf), sizeof(uint64) * 2);
  } else {
    lua_pushlstring(L, (const char *) &result, sizeof(uint64));
  }
  return 1;
}

static int l_hash128(lua_State *L) {
  char buf[64] = { 0 };
  size_t len;
  const char *key = luaL_checklstring(L, 1, &len);
  uint128 seed = uint128(luaL_optnumber(L, 4, 0), luaL_optnumber(L, 5, 0));
  uint128 result = CityHash128WithSeed(key, luaL_optinteger(L, 2, len), seed);
  if (lua_toboolean(L, 3)) {
    uint64 part = Uint128High64(result);
    create_hex_result((char *) &part, sizeof(part), buf);
    part = Uint128Low64(result);
    create_hex_result((char *) &part, sizeof(part), buf + 16);
    lua_pushlstring(L, buf, sizeof(uint64) * 4);
  } else {
    uint64 part = Uint128High64(result);
    memcpy(buf, (char *) &part, 8);
    part = Uint128Low64(result);
    memcpy(buf+8, (char *) &part, 8);
    lua_pushlstring(L, buf, sizeof(uint64) * 2);
  }
  return 1;
}

static const struct luaL_Reg cityhash_lib[] = {
  { "hash64", l_hash64 },
  { "hash128", l_hash128 },
  { NULL, NULL }
};

extern "C" int luaopen_cityhash(lua_State *L) {
  lua_newtable(L);
#if LUA_VERSION_NUM >= 502
  luaL_setfuncs(L, cityhash_lib, 0);
#else
  luaL_register(L, NULL, cityhash_lib);
#endif
  lua_pushliteral(L, "version");
  lua_pushliteral(L, LUA_CITYHASH_VERSION);
  lua_settable(L, -3);

  return 1;
}
