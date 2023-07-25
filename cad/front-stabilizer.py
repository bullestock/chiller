import cadquery as cq

hole_r = 4.2/2
hole_z = 6.5
d = 10

res = (cq.Workplane("XY")
       .box(d, d, d)
       .edges("|Z or > Z")
       .fillet(1)
       .faces("<Z")
       .transformed(offset=(0, 0, -d/2 + hole_z),
                    rotate=(90, 0, 0))
       .circle(hole_r)
       .cutThruAll()
       )

show_object(res)

