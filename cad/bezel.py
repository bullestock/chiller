import cadquery as cq

height = 75
width = 120
thickness = 3
centerXY = (True, True, False)

result = (cq.Workplane("XY")
         .box(width, height, thickness, centered=centerXY)
         .tag("o")
         .edges("<Z")
         .fillet(thickness*0.9999)
         )

# display hole
dhh = 58
dhw = 86
disp_x_offset = 3.25
# pch size
dph = 62
dpw = 109
# inserts
ix_cc = 102
iy_cc = 54.75
i_r = 2
h1 = 3

disphole = (cq.Workplane("XY")
            .transformed(offset=(disp_x_offset, 0, 0))
            .box(dhw+2*thickness, dhh+2*thickness, thickness, centerXY)
            .faces(">Z")
            .chamfer(thickness*0.99)
            )

result = (result
          .faces(">Z")
          .rarray(ix_cc, iy_cc, 2, 2)
          .circle(6/2)
          .extrude(thickness+h1)
          .faces(">Z")
          .workplane()
          .rarray(ix_cc, iy_cc, 2, 2)
          .circle(i_r)
          .cutBlind(-h1)
          )

frame_th = 2
frame_d = 5
frame_w = dpw + 2*frame_th
frame_h = dph + 2*frame_th
log(f'frame {frame_w} x {frame_h}')

frame = (cq.Workplane("XY")
         .workplane(thickness)
          .box(frame_w, frame_h, frame_d, centered=centerXY)
          .faces(">Z or <Z")
          .shell(frame_th)
          )

result = result.cut(disphole) + frame

show_object(result)

