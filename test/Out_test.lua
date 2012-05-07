--[[------------------------------------------------------

  midi.Out test
  -------------

  ...

--]]------------------------------------------------------
require 'lubyk'

local should = test.Suite('midi.Out')
local withUser = should:testWithUser()

function should.autoLoad()
  assertTrue(midi.Out)
end

function should.raiseErrorOnBadPort()
  assertError("the 'portNumber' argument .88. is invalid", function()
    midi.Out(88)
  end)
end

function withUser.should.openPort(t)
  local mo = midi.Out('lubyk')
  local p_count = 4
  local base = {24, 12, 65, 24}
  local chan = {3,   2,  1, 4}
  local vol  = {60, 10, 50, 20}
  sleep(300) -- let DAW host find us
  local mi = midi.In('lubyk')
  assertTrue(mo)
  io.flush()
  t.players = {}
  t.players[p_count+1] = lk.Timer(125, function()
    mo:send(143+chan[1], 37, 0)
    mo:send(143+chan[1], 37, 60)
  end)
  t.players[p_count+1]:start()
  for i=1,p_count do
    local n1 = base[i]
    mo:send(143+chan[i], n1, vol[i] + vol[i]*math.random())
    t.players[i] = lk.Timer(10, function()
      mo:send(143+chan[i], n1, 0)
      n1 = base[i] + 24*math.random()
      mo:send(143+chan[i], n1, vol[i] + vol[i]*math.random())
      return 80 + 130*math.random()
    end)
    t.players[i]:start()
  end

  sleep(5000)
  for i=1,p_count+1 do
    t.players[i]:stop()
  end
  assertTrue(true)
end

--function should.createVirtualPort()
--  local mi = midi.In('foo')
--  assertTrue(mi)
--  print(mi:port())
--  io.flush()
--  local continue = false
--  local i= 0
--  function mi.receive(a, b, c)
--    print(a, b, c)
--    io.flush()
--    i = i + 1
--    if i > 4 then
--      continue = true
--    end
--  end
--  local start = elapsed()
--  while not continue and elapsed() < start + 2000 do
--    sleep(10)
--  end
--  assertTrue(continue)
--end
--
test.all()
