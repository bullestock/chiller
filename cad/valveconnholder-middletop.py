import cadquery as cq

d1 = 16
d2 = 25
d3 = 5
w1 = 12.5
w2 = 20
w3 = 40
th1 = 2
h1 = 25.5
h2 = 40

# Outer shape
res = (cq.Workplane("XY")
       .tag("bot")
       .transformed(offset=(-w3, 0, 0))
       .rect(2*w3, h2)
       .extrude(d3)
       .edges("|Z")
       .fillet(5)
       .edges(">Z")
       .fillet(1)
       )

cutout = (cq.Workplane("XY")
          .tag("cbot")
          # Main cavity
          .rect(h1, h1)
          .extrude(d3)
          .edges("|Z")
          .fillet(2)
          .workplaneFromTagged("cbot")
          .rect(12, h2)
          .workplane(d3)
          .rect(11, h2)
          .loft()
          )

res = (res
       - cutout.translate((0, 0, 0))
       - cutout.translate((-(h1+4), 0, 0))
       )

# Screw holes

csd = 3.2

res = (res
       .workplaneFromTagged("bot")
       .rarray((w2+w3)/2, (h1+h2)/2, 2, 2)
       .circle(csd/2)
       .cutThruAll()
       )

res = (res
       .faces(">X").workplane(-h1)
       .split(keepTop=True)
       )
show_object(res)
#show_object(cutout)
