import cadquery as cq

res = (cq.Workplane("XY")
       .tag("o")
       # rail body
       .workplaneFromTagged("o")
       .transformed(offset=(0, 0, 0))
       .box(20, 20, 15, centered=(True, True, False))
       .edges("|Z")
       .fillet(2.49)
       # cut groove
       .workplaneFromTagged("o")
       .transformed(offset=(0, 0, 10), rotate=(0, 90, 0))
       .rect(10, 10)
       .cutThruAll()
       )

ss1 = (cq.Workplane("XY")
       .transformed(offset=(0, 7.5, -15))
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

res = res + ss1

show_object(res)
