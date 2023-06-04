import cadquery as cq
import math

tube_r = 11/2 # tube inner radius
d1 = 25 # length of tube
wth = 1.5 # tube wall thickness
plate_w = 28
plate_th = 3
screw_cc = 20
screw_r = 3.2/2

# create path
path = cq.Workplane("XZ" ).vLine(d1)

# create tube by sweeping along path
tube = cq.Workplane("XY").circle(tube_r).sweep(path).faces(">Z or <Z").shell(wth)

plate = (cq.Workplane("XY")
         .tag("pbot")
         .rect(plate_w, plate_w)
         .extrude(plate_th)
         .edges("|Z")
         .fillet(2)
         .workplaneFromTagged("pbot")
         .circle(tube_r)
         .cutBlind(plate_th)
         .workplaneFromTagged("pbot")
         .rarray(screw_cc, screw_cc, 2, 2)
         .circle(screw_r)
         .cutThruAll()
         )

# ribs on tube
ring = cq.Workplane("YZ").moveTo(tube_r+wth*0.7).circle(1).revolve()

res = (plate
       .union(tube)
       .union(ring.translate((0, 0, d1-5)), clean=False)
       .union(ring.translate((0, 0, d1-10)), clean=False)
       .union(ring.translate((0, 0, d1-15)), clean=False)
       .faces(">Z")
       .chamfer(0.5)
       )
show_object(res)
