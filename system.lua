i = arx.LoadOps( "sdl2d" )
print( i )
function arx.test()
i = {}
i.a = "test"
i.b = "yes"
return i
end

t = arx.test()
print ( t.b, t.a )