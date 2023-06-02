import cadquery as cq

length = 258
width = 55
foot_w = 6
foot_h = 40
cc_screw = 30
screw_d = 4
th = 10

res = (cq.Workplane("XY")
       .tag("bot")
       .rect(foot_w, width)
       .extrude(-foot_h)
       .edges("|Z")
       .fillet(2.99)
       .edges(">Z or <Z")
       .fillet(2)
       .workplaneFromTagged("bot")
       .rarray(cc_screw, 1, 2, 1)
       .circle(screw_d/2)
       .cutThruAll()
       )
