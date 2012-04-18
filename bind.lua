--[[------------------------------------------------------

  midi bindings generator
  -----------------------

  This uses the 'dub' tool and Doxygen to generate the
  bindings for lk.

  Input:  headers in 'include/midi'
  Output: cpp files in 'src/bind'

--]]------------------------------------------------------
require 'lubyk'

local base = lk.dir()

local ins = dub.Inspector {
  INPUT    = {
    base .. '/include/midi',
    base .. '/include/bind',
  }
}

local binder = dub.LuaBinder()

binder:bind(ins, {
  output_directory = base .. '/src/bind',
  -- Remove this part in included headers
  header_base = base .. '/include',
  -- Execute all lua_open in a single go
  -- with lua_openmdns (creates midi_core.cpp).
  single_lib = 'midi',
  -- Other name so that we can first load midi.lua
  luaopen = 'midi_core',
  only = {
    'In',
    'Out',
  }
})


