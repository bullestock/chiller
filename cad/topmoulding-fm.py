import cadquery as cq

# front/back
# length = 310/2
# sides
length = 177.5
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
          .vLine(w - ch)
          .lineTo(-(th -ch), w)
          .hLine(th - ch)
          .close()
          .extrude(length)
          # male
          .faces(">Z")
          .workplane()
          .hLine(-st)
          .vLine(w-1.2)
          .hLine(st)
          .close()
          .extrude(sd)
          .faces("<Z")
          .workplane()
          # female
          .hLine(-st)
          .vLine(-w+0.9)
          .hLine(st)
          .close()
          .cutBlind(-sd-1)
          )

chamfer1 = (cq.Workplane("XY")
           .transformed(rotate=(0, 45, 0), offset=(-1.2*th, w/2, 0))
           .box(th, 2*w, th)
           )
chamfer2 = (cq.Workplane("XY")
           .transformed(rotate=(0, 45, 0), offset=(-1.2*th, w/2, length))
           .box(th, 2*w, th)
           )

result = result - chamfer1 - chamfer2

show_object(result)
#show_object(slot)

