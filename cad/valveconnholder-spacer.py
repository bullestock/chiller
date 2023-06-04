import cadquery as cq

d1 = 16
d2 = 5
w1 = 12.5
w2 = 20
squeeze = 4
w3 = 40
th1 = 2
h1 = 25.5
h2 = 40

# Outer shape
res = (cq.Workplane("XY")
       .tag("bot")
       .rect(2*w3-squeeze, h2)
       .extrude(d2)
       .edges("|Z")
       .fillet(5)
       )

# Screw holes

msox = w1*0.6 + (w3-squeeze)/2
msoy = w1*0.6
msd = 4.5
mcsd = 10

res = (res
       # mounting holes
       .workplaneFromTagged("bot")
       .transformed(offset=(msox, msoy, 0))
       .circle(msd/2).cutThruAll()
       .workplaneFromTagged("bot")
       .transformed(offset=(msox - w1*2*0.6, -msoy, 0))
       .circle(msd/2).cutThruAll()
       .workplaneFromTagged("bot")
       .transformed(offset=(-msox, -msoy, 0))
       .circle(msd/2).cutThruAll()
       .workplaneFromTagged("bot")
       .transformed(offset=(-msox + w1*2*0.6, msoy, 0))
       .circle(msd/2).cutThruAll()
       )

show_object(res)

