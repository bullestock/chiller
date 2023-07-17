import cadquery as cq

fan_w = 60
hole_cc1 = 50
hole_cc2 = 10
hole_d = 3.5
fan_d = 58
hook_y_pos = 199

res = (cq.Workplane("XY")
       .tag("o")
       .box(fan_w, 20, 5, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       # screw holes
       .workplaneFromTagged("o")
       .transformed(offset=(0, hole_cc2/2, 0))
       .rarray(hole_cc1, 1, 2, 1)
       .circle(hole_d/2)
       .cutThruAll()
       # fan cutout
       .workplaneFromTagged("o")
       .transformed(offset=(0, fan_d/2, 0))
       .circle(fan_d/2)
       .cutThruAll()
       # hook body
       .workplaneFromTagged("o")
       .transformed(offset=(0, -(hook_y_pos - hole_cc2/2), 0))
       .box(20, 20, 15, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       # flat part
       .workplaneFromTagged("o")
       .transformed(offset=(0, -hook_y_pos/2, 0))
       .box(20, hook_y_pos, 5, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       # hook cutout
       .workplaneFromTagged("o")
       .transformed(offset=(0, -(hook_y_pos - hole_cc2/2), 10), rotate=(0, 90, 0))
       .rect(10, 10)
       .cutThruAll()
       # reinforcement
       .workplaneFromTagged("o")
       .transformed(offset=(0, -(hook_y_pos - hole_cc2/2)/2, 0))
       .box(5, hook_y_pos-10 - hole_cc2/2, 15, centered=(True, True, False))
       )



show_object(res)
