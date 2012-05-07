/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for library midi
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "midi/In.h"
#include "midi/Out.h"

using namespace lk;
using namespace midi;

extern "C" {
int luaopen_midi_In(lua_State *L);
int luaopen_midi_Out(lua_State *L);
}

// --=============================================== FUNCTIONS
// Functions from namespace midi
static const struct luaL_Reg midi_functions[] = {
  { NULL, NULL},
};


extern "C" int luaopen_midi_core(lua_State *L) {
  luaopen_midi_In(L);
  luaopen_midi_Out(L);

  // Create the table which will contain all the constants
  lua_getfield(L, LUA_GLOBALSINDEX, "midi");
  if (lua_isnil(L, -1)) {
    // no global table called midi
    lua_pop(L, 1);
    lua_newtable(L);
    // <lib>
    lua_pushvalue(L, -1);
    // <lib> <lib>
    // _G.midi = <lib>
    lua_setglobal(L, "midi");
    // <lib>
  }
  // <lib>
  luaL_register(L, NULL, midi_functions);
  // <lib>
  lua_pop(L, 1);
  return 0;
}
