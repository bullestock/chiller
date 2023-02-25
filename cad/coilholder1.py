import cadquery as cq

w = 10
ho = 3
gs = 20.5 # grid spacing
hd = 7.5 # hole diameter
th = 3
sd = 2
nh = 1

extra = 0 # 1

def make_hole(o, x):
    sphere_offset = 2
    return (o
            .workplaneFromTagged("bot")
            .transformed(offset=((x - 0.5*(1-extra))*gs, ho, 0))
            .tag("ref")
            .circle(hd/2)
            .cutThruAll()
            .workplaneFromTagged("ref")
            .transformed(offset=(0, -ho/2, 0))
            .rect(hd, ho)
            .cutThruAll()
            .workplaneFromTagged("ref")
            .transformed(offset=(0, -sphere_offset, th/2))
            .rarray(hd, 1, 2, 1)
            .sphere(0.5)
            )

res = (cq.Workplane("XY")
       .tag("bot")
       .box((nh+extra)*gs, w, th, centered=False)
       .edges(">Z or |Z")
       .fillet(0.2)
      )

for x in range(1, 1+nh):
    res = make_hole(res, x)

if False:
    res = (res
       .workplaneFromTagged("bot")
       .transformed(offset=(w/2, w/2, 0))
       .circle(3)
       .cutThruAll())
show_object(res)
