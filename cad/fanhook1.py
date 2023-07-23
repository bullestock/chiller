import cadquery as cq

fan_w = 60
hole_cc2 = 10
hole_d = 3.5
fan_d = 58
extra = 182.5 - 180 + 20

res = (cq.Workplane("XY")
       .tag("o")
       # Main plate
       .box(180, 20, 5, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       .workplaneFromTagged("o")
       # screw holes
       .transformed(offset=(-fan_w/2, hole_cc2/2, 0))
       .rarray(hole_cc2, hole_cc2, 2, 1)
       .circle(hole_d/2)
       .cutThruAll()
       # more screw holes
       .workplaneFromTagged("o")
       .transformed(offset=(fan_w/2, hole_cc2/2, 0))
       .rarray(hole_cc2, hole_cc2, 2, 1)
       .circle(hole_d/2)
       .cutThruAll()
       # screw hole
       .workplaneFromTagged("o")
       .transformed(offset=(fan_w/2 + fan_w - hole_cc2/2, hole_cc2/2, 0))
       .circle(hole_d/2)
       .cutThruAll()
       # screw hole
       .workplaneFromTagged("o")
       .transformed(offset=(-(fan_w/2 + fan_w - hole_cc2/2), hole_cc2/2, 0))
       .circle(hole_d/2)
       .cutThruAll()
       # fan cutouts
       .workplaneFromTagged("o")
       .transformed(offset=(0, fan_d/2, 0))
       .rarray(fan_w, 1, 3, 1)
       .circle(fan_d/2)
       .cutThruAll()
       # rail body
       .workplaneFromTagged("o")
       .transformed(offset=(-extra/2, -15, 0))
       .box(180 + extra, 20, 15, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       # cut groove
       .workplaneFromTagged("o")
       .transformed(offset=(0, -15, 10), rotate=(0, 90, 0))
       .rect(10, 10)
       .cutThruAll()
       )

ss1 = (cq.Workplane("XY")
       .transformed(offset=(80, -22.5, -15))
       .box(20, 5, 20, centered=(True, True, False))
       .edges("|Z")
       .fillet(2.49)
       .edges("<Z")
       .fillet(2)
       .faces(">Z")
       .workplane()
       .transformed(offset=(0, 0, -20 + 8), rotate=(90, 0, 0))
       .circle(4.7/2)
       .cutThruAll()
       )

res = res + ss1 + ss1.translate([-182.5, 0, 0])

show_object(res)
