import cadquery as cq

d1 = 16
d2 = 25
w1 = 12.5
w2 = 20
w3 = 40
th1 = 2
h1 = 25.5
h2 = 40

# Outer shape
res = (cq.Workplane("XY")
       .tag("bot")
       .rect(w3, h2)
       .extrude(d2)
       #.workplaneFromTagged("bot")
       .edges("|Z")
       .fillet(5)
       )

extra = 5
cutout = (cq.Workplane("XY")
          .tag("cbot")
          # Main cavity
          .transformed(offset=(0, 0, d2-d1))
          .rect(h1 + 2, h1)
          .extrude(d2)
          .edges("|Z")
          .fillet(2)
          # Round cutout for pipes
          .workplaneFromTagged("cbot")
          .transformed(offset=(0, h2/2, d2-extra),
                       rotate=(90, 0, 0))
          .circle(w1/2)
          .extrude(h2)
          # Extension of round cutout
          .workplaneFromTagged("cbot")
          .transformed(offset=(0, 0, d2-extra))
          .rect(w1, h2)
          .extrude(d1)
          # Cutout for flanges
          .workplaneFromTagged("cbot")
          .transformed(offset=(0, 0, d2-th1))
          .rect(w2, h2)
          .extrude(th1)
          )

res = res - cutout

# TODO: Screw holes

show_object(res)
#show_object(cutout)
