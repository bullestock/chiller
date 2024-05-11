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

notch = (cq.Workplane("YZ")
         .transformed(offset=(0, 3.5, 0))
         .rect(2.5, 5)
         .sweep(spline_path)
)

solid = solid - notch

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

#show_object(notch)
