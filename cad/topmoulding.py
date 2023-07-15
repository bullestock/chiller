import cadquery as cq

length = 155 # max is 250
# horizontal/vertical part
d1 = 5
# angled part
d2 = 3
# chamfer amount
ch = 1.5
# slot width
sw = 3.4 # was 3.2
# slot depth
sd = 2

result = (cq.Workplane("XY")
          .tag("o")
          # profile
          .hLine(d1 + d2)
          .vLine(d1)
          .lineTo(d1, d1 + d2)
          .hLine(-d1)
          .close()
          .extrude(length)
          .faces(">Z or <Z")
          .chamfer(ch)
          # vertical slot
          .workplaneFromTagged("o")
          .transformed(offset=((d1 + d2)/2, sd/2, 0))
          .rect(sw, sd)
          .cutThruAll()
          # horizontal slot
          .workplaneFromTagged("o")
          .transformed(offset=(sd/2, (d1 + d2)/2, 0))
          .rect(sd, sw)
          .cutThruAll()
)

show_object(result)

