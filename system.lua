i = arx.LoadOps( "sdl2d" )
print( i )
function arx.test()
i = {}
i.a = "test"
i.b = "yes"
i.waka = { mim = 4321 }
i.sepe = "philippines"
i.arr = { "tesy", 2, 3, 5, 4321 }
return i
end

t = arx.test()
print ( t.b, t.a )