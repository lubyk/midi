--[[------------------------------------------------------

  midi.In
  -------

  Create/open a midi port.

--]]------------------------------------------------------
local lib     = midi.In_core
midi.In       = lib
local private = {}

local new = lib.new
function lib.new(port_or_name, func)
  local self = new()
  self.receive = func or function() end
  if type(port_or_name) == 'string' then
    -- open a virtual port
    self:virtualPort(port_or_name)
  else
    self:openPort(port_or_name)
  end
  return self
end

local openPort = lib.openPort
function lib:openPort(...)
  openPort(self, ...)
  private.start(self)
end

local virtualPort = lib.virtualPort
function lib:virtualPort(...)
  virtualPort(self, ...)
  private.start(self)
end

function private:start()
  self.thread = lk.Thread(function()
    local thread  = self.thread
    local super   = self.super
    local read_fd = self:fd()
    local sched   = sched
    while thread.should_run do
      sched:waitRead(read_fd)
      self:receive(super:pop())
    end
  end)
end
