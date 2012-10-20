--[[------------------------------------------------------

  midi.Out
  --------

  Create/open a midi port.

--]]------------------------------------------------------
local lib = midi.Out_core
midi.Out  = lib
local private = {}

local new = lib.new
function lib.new(port_or_name)
  local self = new()
  if port_or_name then
    self:openPort(port_or_name)
  end
  return self
end

function lib:sendAt(time, msg)
  local prev = self
  local at_top
  -- Get current top event
  if prev.at_next then
    at_top = prev.at_next.at
  else
    at_top = 0
  end
  msg.at = time
  -- sorted insert (next event first)
  while true do
    local ne = prev.at_next
    if not ne then
      prev.at_next = msg
      msg.at_next = nil
      break
    elseif at < ne.at then
      prev.at_next = msg
      msg.at_next  = ne
      break
    else
      prev = ne
    end
  end
  if time < at_top then
    -- reschedule sender thread
    -- FIXME: code not finished
    assert(false)
    sched:scheduleAt(time, self.thread)
  end
end

local send = lib.send
local decode = midi.Message.decode
function lib:send(msg, ...)
  if type(msg) == 'table' then
    send(self, decode(msg))
  else
    send(self, msg, ...)
  end
end

