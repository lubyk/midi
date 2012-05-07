--[[------------------------------------------------------

  midi.In test
  ------------

  ...

--]]------------------------------------------------------
require 'lubyk'

local should = test.Suite('midi.In')
local withUser = should:testWithUser()

function should.auto_load()
  assertTrue(midi.In)
end

function should.raiseErrorOnBadPort()
  assertError("the 'portNumber' argument .88. is invalid", function()
    midi.In(88)
  end)
end

function withUser.should.openPort(t)
  local mi = midi.In(1)
  assertTrue(mi)
  print('Found', mi:portName(), 'please produce midi events...')
  t.continue = false
  local i= 0
  function mi.receive(msg)
    print(yaml.dump(msg))
    i = i + 1
    if i > 4 then
      t.continue = true
    end
  end
  t:timeout(function()
    return t.continue
  end)
  assertTrue(i > 4)
end

function withUser.should.createVirtualPort(t)
  local mi = midi.In('foo')
  assertTrue(mi)
  print('Created virtual port', mi:portName(), 'please produce midi events...')
  t.continue = false
  local i= 0
  function mi.receive(a, b, c)
    print(a, b, c)
    i = i + 1
    if i > 4 then
      t.continue = true
    end
  end
  t:timeout(function()
    return t.continue
  end)
  assertTrue(i > 4)
end

test.all()
