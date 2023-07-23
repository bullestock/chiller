import cadquery as cq

insert_r = 4.7/2
msd = 4.5
mcsd = 10

ss = (cq.Workplane("XY")
      .box(20, 5, 10, centered=(True, True, False))
      .edges("|Z")
      .fillet(2.49)
      .edges("<Z")
      .fillet(2)
      # insert hole
      .faces(">Z")
      .workplane()
      .transformed(offset=(0, 0, -20 + 8 + 4 + 5), rotate=(90, 0, 0))
      .circle(4.7/2)
      .cutThruAll()
      )

bar = (cq.Workplane("XY")
       .transformed(offset=(-15, 5, 0))
       .box(30, 20, 4, centered=(True, True, False))
       .edges("|Z")
       .fillet(2.49)
       # screw hole
       .faces("<Z")
       .workplane()
       .transformed(offset=(5, 0, 0))
       .cskHole(msd, mcsd, 82)
)

res = bar + ss.translate([-20, -2.5, -10])

show_object(res)
