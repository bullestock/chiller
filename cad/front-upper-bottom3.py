import cadquery as cq
import math

thickness = 4
width = 30
depth = 40
hole_cc_x = 30
hole_cc_y = 16
hole_r = 3.2/2

depth = depth + thickness

res = (cq.Workplane("XY")
       .tag("bot")
       # Basic shape
       .rect(width, depth)
       .extrude(thickness)
       .edges("|Z")
       .fillet(2)
       # Holes for connecting to parts 2 and 3
       .faces("Z")
       .rarray(hole_cc_y, hole_cc_x, 2, 2)
       .circle(hole_r)
       .cutThruAll()
       # Ensure room for inserts
       .faces("<Z")
       .rarray(hole_cc_y, hole_cc_x, 2, 2)
       .circle(4)
       .cutBlind(0.5)
       )

show_object(res)

