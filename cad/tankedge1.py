from tankedgedefs import *

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
         .transformed(offset=(112, -150, 0))
         .circle(ir).cutBlind(-ih)
         .workplaneFromTagged("b")
         .transformed(offset=(112, -135, 0))
         .circle(ir).cutBlind(-ih)
         .workplaneFromTagged("b")
         .transformed(offset=(112, 0, 0))
         .circle(ir).cutBlind(-ih)
         )

show_object(solid)
