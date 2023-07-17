import cadquery as cq
import math

slot_w = 3.1
slot_depth = 3
thickness = 5
width = 180
depth = 51
angle = 24.84
hole_x_offset = 155 # End of profile to hole center
hole_z_offset = 10 # Top of slot to hole center
flange_w = 10
hole_cc = 30
insert_r = 2.1
insert_l = 4

depth_l = depth + thickness
depth_u = depth_l - math.sin(math.radians(angle))*thickness

res = (cq.Workplane("XY")
       .tag("bot")
       # Basic shape
       .rect(width, depth_l)
       .workplane(thickness)
       .transformed(offset=(0, (depth_l - depth_u)/2, 0))
       .rect(width, depth_u)
       .loft()
       # Slot
       .workplaneFromTagged("bot")
       .transformed(offset=(0, (depth_l - slot_w)/2 - thickness, 0))
       .rect(width, slot_w)
       .cutBlind(slot_depth)
       # Flange
       .workplaneFromTagged("bot")
       .transformed(offset=(hole_x_offset/2, (depth_l - thickness)/2, 0))
       .rect(flange_w, thickness)
       .extrude(-(hole_z_offset+thickness))
       # Hole for front plate screw
       .workplaneFromTagged("bot")
       .transformed(offset=(hole_x_offset/2, 0, -(hole_z_offset - slot_depth)),
                            rotate=(90, 0, 0))
       .circle(6/2)
       .cutThruAll()
       # Holes for connecting to part 2
       .workplaneFromTagged("bot")
       .transformed(offset=(width/2 - thickness, 0, thickness))
       .rarray(1, hole_cc, 1, 2)
       .circle(insert_r)
       .cutBlind(-insert_l)
       )

show_object(res)

