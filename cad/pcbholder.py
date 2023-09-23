import cadquery as cq

depth = 52
height = 20
bracket_th = 4
w = 90
hole_cc = 41.5
hole_dia = 3.5

result = (cq.Workplane("XY")
          .box(w, depth, bracket_th, centered=(True, True, False))
          .faces("<Z").workplane().tag("bottom")
          # mount plate
          .workplaneFromTagged("bottom")
          .transformed(offset=(0, (depth-bracket_th)/2, -height))
          .box(w, bracket_th, height, centered=(True, True, False))
          # round edges
          .edges().fillet(1)
          # mounting holes
          .workplaneFromTagged("bottom")
          .transformed(offset=(-((w - hole_cc)/2 - height/2), 0, -height/2), rotate=(90, 0, 0))
          .rarray(hole_cc, 1, 2, 1)
          .circle(hole_dia/2).cutThruAll()
          # pcb holes
          .workplaneFromTagged("bottom")
          .transformed(offset=(0, 0, 0))
          .circle(hole_dia/2).cutThruAll()
)

show_object(result)

