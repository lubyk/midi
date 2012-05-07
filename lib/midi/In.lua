--[[------------------------------------------------------

  midi.In
  -------

  Create/open a midi port.

--]]------------------------------------------------------
local lib = midi.In_core
midi.In   = lib

local new = lib.new
function lib.new(port_or_name, func)
  local self = new()
  if type(port_or_name) == 'string' then
    -- open a virtual port
    self:virtualPort(port_or_name)
  else
    self:openPort(port_or_name)
  end
  self.receive = func or function() end
  self.thread = lk.Thread(function()
    self:loop()
  end)
  return self
end

function lib:loop()
  local thread  = self.thread
  local super   = self.super
  local read_fd = self:fd()
  local sched   = sched
  while thread.should_run do
    sched:waitRead(read_fd)
    self.receive(super:pop())
  end
end
