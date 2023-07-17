import cadquery as cq
import math

width = 20
height = 108
depth = 50
# distance between mounting holes
hole_cc = 55
hole_offset = 0
# screw
screw_d = 4.2
sh_d = 10
sh_h = 50
th = 5
# inserts
insert_r = 6/2
insert_l = 5.5
insert_cc = height - 15
insert_offset = -15

# basic profile
result = (cq.Workplane("XY")
          # profile
          .vLine(height)
          .hLine(depth)
          .close()
          .extrude(width)
          )

# mounting holes
result = (result
          .faces("<X")
          .transformed(offset=(depth + th, height/2 + hole_offset, width/2), rotate=(0, 90, 0))
          .rarray(1, hole_cc, 1, 2)
          .cboreHole(screw_d, sh_d, depth)
          )

angle = math.degrees(math.atan(depth/height))
(result
 .faces("<X")
 .workplane(offset=0, invert=False)
 .transformed(offset=(insert_offset, 0, 0), rotate=(0, -angle, 0))
 .tag("top")
 )

result = (result
          .workplaneFromTagged("top")
          .workplane(-29) # magic
          .rarray(insert_cc, 1, 2, 1)
          .circle(insert_r)
          .cutBlind(insert_l)
          )

show_object(result)
