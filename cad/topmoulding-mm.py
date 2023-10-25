import cadquery as cq

length = 310/2
w = 20
th = 3
ch = 1.5
sd = 3
st = 1.5
cr = 3

# basic profile
result = (cq.Workplane("XY")
          .tag("o")
          # profile
          .hLine(-th)
          .vLine(w + th)
          .hLine(2*th)
          .vLine(-th)
          .hLine(-th)
          .close()
          .extrude(length)
          .faces(">Y")
          .fillet(1)
          .faces(">Z")
          .workplane()
          .hLine(-st)
          .vLine(w)
          .hLine(st)
          .close()
          .extrude(sd)
          .faces("<Z")
          .workplane()
          .hLine(-st)
          .vLine(-w)
          .hLine(st)
          .close()
          .extrude(sd)
          )

chamfer1 = (cq.Workplane("XY")
           .transformed(rotate=(0, 45, 0), offset=(-1.2*th, w/2, 0))
           .box(th, 2*w, th)
           )
chamfer2 = (cq.Workplane("XY")
           .transformed(rotate=(0, 45, 0), offset=(-1.2*th, w/2, length))
           .box(th, 2*w, th)
           )

slot_w = 20
slot_offset = length - 120/2
slot = (cq.Workplane("XY")
        .transformed(offset=(5, w/2, length - slot_offset))
        .box(10, 2*w, slot_w)
        )

result = result - chamfer1 - chamfer2 - slot

show_object(result)
#show_object(chamfer2)

