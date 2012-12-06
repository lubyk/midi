--[[------------------------------------------------------

  midi.In
  -------

  Create/open a midi port.

--]]------------------------------------------------------
local lib     = midi.In_core
midi.In       = lib
lib.mode      = 'thread'
local private = {}

local new = lib.new
function lib.new(port_or_name, func)
  local self = new()
  if port_or_name then
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
  -- midi.In.mode == 'pull' is used when we do not have a scheduler and
  -- we pull messages from the queue by hand.
  if lib.mode == 'thread' then
    self.thread = lk.Thread(function()
      -- Copy Node's error function (or global) into self
      local thread  = self.thread
      local super   = self.super
      local read_fd = self:fd()
      local sched   = sched
      while thread.should_run do
        sched:waitRead(read_fd)
        self:rawReceive(super:pop())
      end
    end)
    -- Also use dub's error handler for errors in Lua during
    -- 'rawReceive'.
    self.thread.error = self._errfunc
    -- Restart on error.
    self.thread.restart = true
  end
end

-- This is used when we run without a scheduler.
function lib:pull()
  local super = self.super
  while super:hasMessage() do
    self:rawReceive(super:pop())
  end
end

-- Default dummy function
function lib:receive(msg)
end

-- Default dummy function
function lib:rawReceive(a, b, c)
  self:receive(midi.Message(a, b, c))
end
