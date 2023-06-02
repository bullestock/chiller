import cadquery as cq
import math

tube_r = 11/2 # tube inner radius
d1 = 20 # height of vertical tube
r1 = 25 # radius of first bend
a1 = 89 # angle of first bend in degrees
d2 = 3 # length of horizontal tube
wth = 1.5 # tube wall thickness
plate_w = 28
plate_th = 3
screw_cc = 20
screw_r = 3.2/2

# Bend points
ap1 = (r1 - math.cos(math.radians(a1/2))*r1, d1 + math.sin(math.radians(a1/2))*r1)
ap2 = (r1 - math.cos(math.radians(a1))*r1, d1 + math.sin(math.radians(a1))*r1)

# create path
path = cq.Workplane("XZ" ).vLine(d1).threePointArc(ap1, ap2).polarLine(d2, 90 - a1)

# create tube by sweeping along path
tube = cq.Workplane("XY").circle(tube_r).sweep(path).faces(">Z or <Z").shell(wth)

plate = (tube
         .center(0, 0)
         .workplane()
         .transformed(rotate=(0, 270, 0), offset=(r1+d2, 0, r1+d1))
         .tag("pbot")
         .rect(plate_w, plate_w)
         .extrude(plate_th)
         .edges("|X")
         .fillet(2)
         .workplaneFromTagged("pbot")
         .transformed(offset=(-9, 0, 0))
         .rect(plate_w/2-tube_r, 2*tube_r)
         .extrude("next")
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
       .union(ring.translate((0, 0, 5)), clean=False)
       .union(ring.translate((0, 0, 10)), clean=False)
       .union(ring.translate((0, 0, 15)), clean=False)
       )
show_object(res)
