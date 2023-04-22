import cadquery as cq

length = 258
width = 55
foot_w = 6
foot_h = 40
cc_x = 21
cc_y = 42
screw_d = 3.5
th = 10

res = (cq.Workplane("XY")
       .tag("bot")
       .rect(length, width)
       .extrude(th)
       .workplaneFromTagged("bot")
       .rarray(length - foot_w, 1, 2, 1)
       .rect(foot_w, width)
       .extrude(-foot_h)
       .edges("|Z")
       .fillet(2.99)
       .edges(">Z or <Z")
       .fillet(2)
       .workplaneFromTagged("bot")
       .rarray(cc_x, cc_y, 2, 2)
       .circle(screw_d/2)
       .cutThruAll()
       )
