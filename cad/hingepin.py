import cadquery as cq

w = 20
pinhole_dia = 3.7+0.1

res = (cq.Workplane("XY")
       .circle(pinhole_dia/2).extrude(w)
       )

show_object(res)
