import cadquery as cq
import math

w = 20
th = 3
id = 9
od = 15
angle = 0
ch = th/2
sd = 3
st = 1.5
cr = 3

dist_to_corner = w/2 - w*math.cos(math.radians(90 - angle))
inset = (w - od)/2
arc_mid = w/2 + math.cos(math.radians(45)) * od/2

result = (cq.Workplane("XY")
          .tag('o')
          # top part
          .vLine(w)
          .hLine(dist_to_corner)
          .vLine(-inset)
          .threePointArc((arc_mid, arc_mid), (w - inset, dist_to_corner))
          .hLine(inset)
          .lineTo(w, 0)
          .close()
          .extrude(th)
          # center hole
          .workplane(centerOption = 'CenterOfBoundBox')
          .circle(id/2)
          .cutThruAll()
          # extend top
          .workplaneFromTagged('o')
          .hLine(w)
          .vLine(-(th - ch))
          .lineTo(w - ch, -th)
          .hLine(-(w + th))
          .lineTo(w - ch, -th)
          .lineTo(-(th - cr), -th)
          .lineTo(-th, -(th - cr))
          .vLine(w + th - ch - cr)
          .lineTo(-(th - ch), w)
          .hLine(st)
          .close()
          .extrude(th)
          # sides
          .workplaneFromTagged('o')
          .workplane(th)
          .hLine(w - sd)
          # right-side slot
          .vLine(-st)
          .hLine(sd)
          .lineTo(w - ch, -th)
          # right-side chamfer
          .lineTo(-(th - cr), -th)
          # bottom
          .lineTo(-th, -(th - cr))
          # left side
          .vLine(w + th - ch - cr)
          # top chamfer
          .lineTo(-(th - ch), w)
          # top slot
          .vLine(-sd)
          .hLine(st)
          .close()
          .extrude(w)
          .faces("<Z")
          .fillet(1)
          #.faces("<X or <Y")
          #.fillet(1)
)

show_object(result)
