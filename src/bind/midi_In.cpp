/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class In
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "midi/In.h"

using namespace midi;

/** midi::In::In()
 * include/midi/In.h:68
 */
static int In_In(lua_State *L) {
  try {
    In *retval__ = new In();
    retval__->pushobject(L, retval__, "midi.In", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "In: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "In: Unknown exception");
  }
  return dub_error(L);
}

/** midi::In::~In()
 * include/midi/In.h:76
 */
static int In__In(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub_checksdata_d(L, 1, "midi.In"));
    if (userdata->gc) {
      In *self = (In *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "~In: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "~In: Unknown exception");
  }
  return dub_error(L);
}

/** int midi::In::port() const
 * include/midi/In.h:78
 */
static int In_port(lua_State *L) {
  try {
    In *self = *((In **)dub_checksdata(L, 1, "midi.In"));
    lua_pushnumber(L, self->port());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "port: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "port: Unknown exception");
  }
  return dub_error(L);
}

/** const char* midi::In::portName() const
 * include/midi/In.h:82
 */
static int In_portName(lua_State *L) {
  try {
    In *self = *((In **)dub_checksdata(L, 1, "midi.In"));
    lua_pushstring(L, self->portName());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "portName: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "portName: Unknown exception");
  }
  return dub_error(L);
}

/** void midi::In::openPort(int port, lua_State *L)
 * include/midi/In.h:86
 */
static int In_openPort(lua_State *L) {
  try {
    In *self = *((In **)dub_checksdata(L, 1, "midi.In"));
    int type__ = lua_type(L, 2);
    if (type__ == LUA_TNUMBER) {
      int port = dub_checkint(L, 2);
      self->openPort(port, L);
      return 0;
    } else {
      const char *port_name = dub_checkstring(L, 2);
      self->openPort(port_name, L);
      return 0;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "openPort: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "openPort: Unknown exception");
  }
  return dub_error(L);
}

/** void midi::In::virtualPort(const char *port_name, lua_State *L)
 * include/midi/In.h:119
 */
static int In_virtualPort(lua_State *L) {
  try {
    In *self = *((In **)dub_checksdata(L, 1, "midi.In"));
    const char *port_name = dub_checkstring(L, 2);
    self->virtualPort(port_name, L);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "virtualPort: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "virtualPort: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int In___tostring(lua_State *L) {
  In *self = *((In **)dub_checksdata_n(L, 1, "midi.In"));
  lua_pushfstring(L, "midi.In: %p (%s (%f))", self, self-> portName() , self-> port() );
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg In_member_methods[] = {
  { "new"          , In_In                },
  { "__gc"         , In__In               },
  { "port"         , In_port              },
  { "portName"     , In_portName          },
  { "openPort"     , In_openPort          },
  { "virtualPort"  , In_virtualPort       },
  { "__tostring"   , In___tostring        },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_midi_In(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "midi.In");
  // <mt>

  // register member methods
  luaL_register(L, NULL, In_member_methods);
  // save meta-table in midi
  dub_register(L, "midi", "In_core", "In");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
