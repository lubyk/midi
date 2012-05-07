--[[------------------------------------------------------

  midi bindings generator
  -----------------------

  This uses the 'dub' tool and Doxygen to generate the
  bindings for lk.

  Input:  headers in 'include/midi'
  Output: cpp files in 'src/bind'

--]]------------------------------------------------------
require 'lubyk'

local base = lk.scriptDir()

local ins = dub.Inspector {
  INPUT    = {
    base .. '/include/midi',
    base .. '/bind',
  }
}

local binder = dub.LuaBinder()

binder:bind(ins, {
  output_directory = base .. '/src/bind',
  -- Remove this part in included headers
  header_base = base .. '/include',
  single_lib = 'midi',
  -- Other name so that we can first load midi.lua
  luaopen = 'midi_core',
  only = {
    'midi::In',
    'midi::Out',
  }
})


