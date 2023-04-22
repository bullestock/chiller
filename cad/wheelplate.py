import cadquery as cq

w = 50
extra = 5
th = 8
screw_d = 5
ch_d = 12
cb_d = 7
cc = 25.4
ext = 2
offset = 4

res = (cq.Workplane("XY")
       .box(w, w, (1+ext)*th)
       .edges("|Z")
       .fillet(4)
       .faces(">Z")
       .faces(">Z")
       .workplane()
       .rarray(cc, cc, 2, 2)
       .cboreHole(screw_d, ch_d, cb_d + ext*th)
       .faces(">Z")
       .fillet(1)
       )

res = (res
       .faces("<Y")
       .workplane()
       .transformed(offset=(w/2 - cc/2 + offset, -ext/2*th, 0))
       .rect(w, ext*th)
       .cutThruAll()
       .faces(">Y")
       .workplane()
       .transformed(offset=(2*th, -1*th, 0))
       .rect(3*th, 2*th)
       .extrude(th)
       )
