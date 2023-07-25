import cadquery as cq

length = 105
hole_cc = 79.5
hole_dia = 4.5
hole_offset = -2.5
w = 20
th = 4
eps = 0.1
pinhole_dia = th
msd = 4.5
mcsd = 10

res = (cq.Workplane("XY")
       .tag("o")
       # flap
       .box(length, w, th, centered=(True, True, False))
       .edges()
       .fillet(1)
       # round part
       .workplaneFromTagged("o")
       .transformed(offset=(length/2 - th/2, w/2, -eps), rotate=(90, 0, 0))
       .tag("r")
       .circle(th+eps)
       .extrude(w)
       # pin hole
       .workplaneFromTagged("r")
       .circle(pinhole_dia/2).cutThruAll()
       # cutouts
       .workplaneFromTagged("o")
       .transformed(offset=(length/2 + w/2 - th/2 - th - 5*eps, w/3, -w/2))
       .rect(w, w/3)
       .cutBlind(w)
       .workplaneFromTagged("o")
       .transformed(offset=(length/2 + w/2 - th/2 - th - 5*eps, -w/3, -w/2))
       .rect(w, w/3)
       .cutBlind(w)
       # mounting holes
       .workplaneFromTagged("o")
       .workplane(invert=True)
       .transformed(offset=(hole_offset, 0, 0))
       .rarray(hole_cc, 1, 2, 1)
       .cskHole(msd, mcsd, 82)
       )

show_object(res)
