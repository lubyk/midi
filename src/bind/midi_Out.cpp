/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class Out
 *
 * This file has been generated by dub 2.1.~.
 */
#include "dub/dub.h"
#include "midi/Out.h"

using namespace midi;

/** midi::Out::Out()
 * include/midi/Out.h:49
 */
static int Out_Out(lua_State *L) {
  try {
    Out *retval__ = new Out();
    retval__->pushobject(L, retval__, "midi.Out", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Out: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Out: Unknown exception");
  }
  return dub_error(L);
}

/** midi::Out::~Out()
 * include/midi/Out.h:53
 */
static int Out__Out(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub_checksdata_d(L, 1, "midi.Out"));
    if (userdata->gc) {
      Out *self = (Out *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "~Out: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "~Out: Unknown exception");
  }
  return dub_error(L);
}

/** int midi::Out::port() const
 * include/midi/Out.h:59
 */
static int Out_port(lua_State *L) {
  try {
    Out *self = *((Out **)dub_checksdata(L, 1, "midi.Out"));
    lua_pushnumber(L, self->port());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "port: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "port: Unknown exception");
  }
  return dub_error(L);
}

/** const char* midi::Out::portName() const
 * include/midi/Out.h:63
 */
static int Out_portName(lua_State *L) {
  try {
    Out *self = *((Out **)dub_checksdata(L, 1, "midi.Out"));
    lua_pushstring(L, self->portName());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "portName: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "portName: Unknown exception");
  }
  return dub_error(L);
}

/** void midi::Out::openPort(int port, lua_State *L)
 * include/midi/Out.h:67
 */
static int Out_openPort(lua_State *L) {
  try {
    Out *self = *((Out **)dub_checksdata(L, 1, "midi.Out"));
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

/** void midi::Out::virtualPort(const char *port_name, lua_State *L)
 * include/midi/Out.h:100
 */
static int Out_virtualPort(lua_State *L) {
  try {
    Out *self = *((Out **)dub_checksdata(L, 1, "midi.Out"));
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

/** void midi::Out::send(int a, int b, int c)
 * include/midi/Out.h:105
 */
static int Out_send(lua_State *L) {
  try {
    Out *self = *((Out **)dub_checksdata(L, 1, "midi.Out"));
    int a = dub_checkint(L, 2);
    int b = dub_checkint(L, 3);
    int c = dub_checkint(L, 4);
    self->send(a, b, c);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "send: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "send: Unknown exception");
  }
  return dub_error(L);
}

/** static LuaStackSize midi::Out::ports(lua_State *L)
 * include/midi/Out.h:115
 */
static int Out_ports(lua_State *L) {
  try {
    return Out::ports(L);
  } catch (std::exception &e) {
    lua_pushfstring(L, "ports: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ports: Unknown exception");
  }
  return dub_error(L);
}



// --=============================================== __tostring
static int Out___tostring(lua_State *L) {
  Out *self = *((Out **)dub_checksdata_n(L, 1, "midi.Out"));
  lua_pushfstring(L, "midi.Out: %p (%s (%f))", self, self-> portName() , self-> port() );
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg Out_member_methods[] = {
  { "new"          , Out_Out              },
  { "__gc"         , Out__Out             },
  { "port"         , Out_port             },
  { "portName"     , Out_portName         },
  { "openPort"     , Out_openPort         },
  { "virtualPort"  , Out_virtualPort      },
  { "send"         , Out_send             },
  { "ports"        , Out_ports            },
  { "__tostring"   , Out___tostring       },
  { "deleted"      , dub_isDeleted        },
  { NULL, NULL},
};


extern "C" int luaopen_midi_Out(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "midi.Out");
  // <mt>

  // register member methods
  luaL_register(L, NULL, Out_member_methods);
  // save meta-table in midi
  dub_register(L, "midi", "Out_core", "Out");
  // <mt>
  lua_pop(L, 1);
  return 0;
}
