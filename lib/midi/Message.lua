--[[------------------------------------------------------

  midi.Message
  ------------

  MIDI message abstraction.

--]]------------------------------------------------------
local lib    = {type = 'midi.Message'}
lib.__index  = lib
midi.Message = lib
local private = {}

local CLOCK_NB_TO_OP = {
  [0xFA] = 'Start',
  [0xFC] = 'Stop',
  [0xF8] = 'Tick',
  [0xFB] = 'Continue',
}
local CLOCK_OP_TO_NB = {}
for k,v in pairs(CLOCK_NB_TO_OP) do
  CLOCK_OP_TO_NB[v] = k
end

setmetatable(lib, {
  __call = function(lib, ...)
    return lib.new(...)
  end
})

function lib.new(a, b, c)
  if a >= 0xF0 then
    return {
      type = 'Clock',
      op   = CLOCK_NB_TO_OP[a],
    }
  elseif a >= 0xB0 then
    return {
      type    = 'Ctrl',
      channel = a - 0xB0 + 1,
      ctrl    = b,
      value   = c
    }
  elseif a >= 0x90 then
    return {
      type     = c == 0 and 'NoteOff' or 'NoteOn',
      channel  = a - 0x90 + 1,
      note     = b,
      velocity = c
    }
  elseif a >= 0x80 then
    return {
      type     = 'NoteOff',
      channel  = a - 0x80 + 1,
      note     = b,
      velocity = c
    }
  else
    return {
      type = 'Raw',
      a    = a,
      b    = b,
      c    = c,
    }
  end
end

function lib.decode(msg)
  if a >= 0xF0 then
    return {
      type = 'Clock',
      op   = CLOCK_OPERATION[a],
    }
  elseif a >= 0xB0 then
    return {
      type    = 'Ctrl',
      channel = a - 0xB0 + 1,
      ctrl    = b,
      value   = c
    }
  elseif a >= 0x90 then
    return {
      type     = c == 0 and 'NoteOff' or 'NoteOn',
      channel  = a - 0x90 + 1,
      note     = b,
      velocity = c
    }
  elseif a >= 0x80 then
    return {
      type     = 'NoteOff',
      channel  = a - 0x80 + 1,
      note     = b,
      velocity = c
    }
  else
    return {
      type = 'Raw',
      a    = a,
      b    = b,
      c    = c,
    }
  end
end

function private.Clock(msg)
  return CLOCK_OP_TO_NB[msg.op], 0, 0
end

function private.Ctrl(msg)
  return 0xB0 + msg.channel - 1, msg.ctrl, msg.value
end

function private.NoteOn(msg)
  return 0x90 + msg.channel - 1, msg.note, msg.velocity
end

function private.NoteOff(msg)
  return 0x80 + msg.channel - 1, msg.note, msg.velocity
end

function private.Raw(msg)
  return msg.a, msg.b, msg.c
end
