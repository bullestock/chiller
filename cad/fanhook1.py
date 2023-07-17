import cadquery as cq

fan_w = 60
hole_cc2 = 10
hole_d = 3.5
fan_d = 58

res = (cq.Workplane("XY")
       .tag("o")
       .box(180, 20, 5, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       .workplaneFromTagged("o")
       .transformed(offset=(-fan_w/2, hole_cc2/2, 0))
       .rarray(hole_cc2, hole_cc2, 2, 1)
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(fan_w/2, hole_cc2/2, 0))
       .rarray(hole_cc2, hole_cc2, 2, 1)
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(fan_w/2 + fan_w - hole_cc2/2, hole_cc2/2, 0))
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(-(fan_w/2 + fan_w - hole_cc2/2), hole_cc2/2, 0))
       .circle(hole_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(0, fan_d/2, 0))
       .rarray(fan_w, 1, 3, 1)
       .circle(fan_d/2)
       .cutThruAll()
       .workplaneFromTagged("o")
       .transformed(offset=(0, -15, 0))
       .box(180, 20, 15, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       .workplaneFromTagged("o")
       .transformed(offset=(0, -15, 10), rotate=(0, 90, 0))
       .rect(10, 10)
       .cutThruAll()
       )



show_object(res)
