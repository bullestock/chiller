import cadquery as cq
import math

tube_r = 11/2 # tube inner radius
d1 = 3 # height of vertical tube
r1 = 25 # radius of first bend
a1 = 60 # angle of first bend in degrees
d2 = 20 # length of horizontal tube
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

# rotation vectors
sv = (0, 0, 0)
ev = (0, 1, 0)

# calculate point rotation for rings
def get_point(dist):
    return (r1*math.cos(math.radians(a1)) + dist*math.cos(math.radians(90-a1)),
            0,
            plate_th+r1*math.sin(math.radians(a1)) + dist*math.sin(math.radians(90-a1)))

res = (plate
       .union(tube, clean=False)
       .union(ring.rotate(sv, ev, a1).translate(get_point(d2-5)), clean=False)
       .union(ring.rotate(sv, ev, a1).translate(get_point(d2-10)), clean=False)
       .union(ring.rotate(sv, ev, a1).translate(get_point(d2-15)), clean=False)
       )
show_object(res)
