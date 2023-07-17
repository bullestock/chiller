import cadquery as cq
import math

thickness = 4
width = 20
depth = 51
hole_cc_x = 30
hole_cc_y = 2*thickness
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
       .workplaneFromTagged("bot")
       .rarray(hole_cc_y, hole_cc_x, 2, 2)
       .circle(hole_r)
       .cutThruAll()
       )

show_object(res)

