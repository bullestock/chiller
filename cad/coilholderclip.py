import cadquery as cq

d = 6
eps = 0.2
hh = 2*20+0.7
hw = 9+eps
th = 8

res = (cq.Workplane("XY")
       .box(hh+2*th, hw+2*th, d)
       .workplane()
       .rect(hh, hw)
       .cutThruAll()
      )

show_object(res)
