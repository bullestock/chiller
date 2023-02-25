import cadquery as cq

extra = 0 # 1

w = 14
ho = 11.5/2 if extra else 5 # hole offset from edge
gs = 20.5 # grid spacing
hd = 7.7 # hole diameter
th = 6 if extra else 3
sd = 2
nh = 12 if extra else 1

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
            .transformed(offset=(0, -sphere_offset, 0))
            .rarray(hd, 1, 2, 1)
            .circle(0.5)
            .extrude(th)
            )

width = (nh+extra)*gs
res = (cq.Workplane("XY")
       .tag("bot")
       .box(width, w, th, centered=False)
      )

for x in range(1, 1+nh):
    res = make_hole(res, x)

res = (res
       .edges(">Z or <Z or |Z")
       .fillet(0.2)
       )

if extra:
    res = (res
       .workplaneFromTagged("bot")
       .transformed(offset=(w/2, w/2, th/2), rotate=(90, 0, 0))
       .circle(3.5/2)
       .cutThruAll()
       .workplaneFromTagged("bot")
       .transformed(offset=(width - w/2, w/2, th/2), rotate=(90, 0, 0))
       .circle(3.5/2)
       .cutThruAll()
       )
show_object(res)
