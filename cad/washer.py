import cadquery as cq

res = (cq.Workplane("XY")
       .circle(8/2)
       .extrude(1.5)
       .circle(3.5/2)
       .cutThruAll()
       )
