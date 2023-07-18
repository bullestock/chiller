import cadquery as cq

fan_w = 60
hole_cc2 = 10
hole_d = 3.5
fan_d = 58

res = (cq.Workplane("XY")
       .tag("o")
       .box(180, 20, 3)
       .edges("|Z")
       .fillet(3)
       .workplaneFromTagged("o")
       .transformed(offset=(-fan_w/2, 0, 0))
       .rarray(hole_cc2, hole_cc2, 2, 2)
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(fan_w/2, 0, 0))
       .rarray(hole_cc2, hole_cc2, 2, 2)
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(fan_w/2 + fan_w - hole_cc2/2, 0, 0))
       .rarray(hole_cc2, hole_cc2, 1, 2)
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(-(fan_w/2 + fan_w - hole_cc2/2), 0, 0))
       .rarray(hole_cc2, hole_cc2, 1, 2)
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       #.transformed(offset=(-(fan_w/2 + fan_w - hole_cc2/2), 0, 0))
       .rarray(1, fan_w, 1, 2)
       .circle(fan_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(-fan_w, 0, 0))
       .rarray(1, fan_w, 1, 2)
       .circle(fan_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(fan_w, 0, 0))
       .rarray(1, fan_w, 1, 2)
       .circle(fan_d/2)
       .cutThruAll()
       )

show_object(res)
