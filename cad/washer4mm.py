import cadquery as cq

res = (cq.Workplane("XY")
       .circle(10/2)
       .extrude(1)
       .circle(4/2)
       .cutThruAll()
       )
