import cadquery as cq

w = 14
ho = 11.5/2 # hole offset from edge
gs = 20.5 # grid spacing
hd = 7.7 # hole diameter
th = 6
sd = 2
nh = 12

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

width = (nh+2)*gs
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

# Outer screw holes
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

split_offset = (width+gs)/2 - 2
part1 = True
res = (res
       .faces(">X")
       .workplane(-split_offset)
       .split(keepBottom=part1, keepTop=not part1)
      )

peg_dia = 4
peg_th = 2
peg_offset = th*0.75
if part1:
    res = (res
          .faces(">X")
          .workplane()
          .transformed(offset=(0, 0, -peg_offset), rotate=(0, 90, 0))
          .tag("peg")
          .circle(peg_dia/2)
          #.extrude(20)
          .cutThruAll()
          .workplaneFromTagged("peg")
          .transformed(offset=(-peg_dia, 0, 0))
          .rect(2*peg_dia, peg_th)
          .cutThruAll()
          #.extrude(50)
          )
else:
    e = 0.05
    res = (res
          .faces("<X")
          .workplane()
          .transformed(offset=(-w/2, 0, peg_offset), rotate=(0, 90, 0))
          .tag("peg")
          .circle(peg_dia/2 - e)
          .extrude(w)
          .workplaneFromTagged("peg")
          .transformed(offset=(peg_dia, 0, 0))
          .rect(2*peg_dia, peg_th - e)
          .extrude(w)
          )

show_object(res)
