import cadquery as cq

cap_d = 39.5
holes_cc = 60
holes_d = 3.5
outer_d = cap_d + 12
ears_d = 15
th = 20

res = (cq.Workplane("XY")
       .tag("bot")
       .circle(outer_d/2)
       .extrude(th)
       .workplaneFromTagged("bot")
       .rarray(holes_cc, 1, 2, 1)
       .circle(ears_d/2)
       .extrude(th)
       .workplaneFromTagged("bot")
       .circle(cap_d/2)
       .cutThruAll()
       .workplaneFromTagged("bot")
       .transformed(offset=(0, cap_d/2, 0))
       .rect(0.1, cap_d)
       .cutThruAll()
       .edges("|Z or >Z")
       .fillet(2)
       .workplaneFromTagged("bot")
       .rarray(holes_cc, 1, 2, 1)
       .circle(holes_d/2)
       .cutThruAll()
       )
