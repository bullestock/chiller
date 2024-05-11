from tankedgedefs import *

pts = points
points = []
for p in pts:
    points.append((-p[0], p[1]))
    
p = points[-1]
p = (p[0] - 11, p[1])
points[-1] = p

spline_path = cq.Workplane("YX").spline(points)

solid = cq.Workplane("YZ").rect(10, 12).sweep(spline_path)

ir = 4/2
ih = 5

solid = (solid
         .faces("<Z")
         .workplane()
         .tag("b")
         .transformed(offset=(10, 0, 0))
         .circle(ir).cutBlind(-ih)
         .workplaneFromTagged("b")
         .transformed(offset=(25, 0, 0))
         .circle(ir).cutBlind(-ih)
         .workplaneFromTagged("b")
         .transformed(offset=(112, 150 + 11, 0))
         .circle(ir).cutBlind(-ih)
         .workplaneFromTagged("b")
         .transformed(offset=(112, 135 + 11, 0))
         .circle(ir).cutBlind(-ih)
         .workplaneFromTagged("b")
         .transformed(offset=(112, 0, 0))
         .circle(ir).cutBlind(-ih)
         )

show_object(solid)

cq.exporters.export(solid,
                    "/home/torsten/Downloads/tankseal2.svg",
                    opt={
                        "showAxes": False,
                        "projectionDir": (0, 0, -1),
                        "showHidden": True,
                    })
