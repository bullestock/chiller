import cadquery as cq

w = 20 # width
ho = 11.5/2 # hole offset from edge
gs = 20.5 # grid spacing
hd = 7.75 # hole diameter
th = 9 # thickness
sd = 2 # 
nh = 12 # number of holes

def make_hole(o, x):
    sphere_offset = 2
    return (o
            .workplaneFromTagged("bot")
            .transformed(offset=(x*gs, ho, 0))
            .tag("ref")
            .circle(hd/2)
            .cutThruAll()
            .workplaneFromTagged("ref")
            .transformed(offset=(0, -ho/2, 0))
            .rect(hd, ho)
            .cutThruAll()
            .workplaneFromTagged("ref")
            .transformed(offset=(0, -sphere_offset, 0))
            .rarray(hd+0.5, 1, 2, 1)
            .circle(0.5)
            .extrude(th)
            )

width = (nh+0.5)*gs
print(width)
res = (cq.Workplane("XY")
       .tag("bot")
       .box(width, w, th, centered=False)
      )

for x in range(1, 1+nh):
    res = make_hole(res, x-0.6+0.5)

res = (res
       .edges(">Z or <Z or |Z")
       .fillet(0.2)
       )

show_object(res)
