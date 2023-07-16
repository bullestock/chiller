import cadquery as cq

length = 155 # max is 250
# horizontal/vertical part
d1 = 5
# angled part
d2 = 3
# chamfer amount
ch = 1.5
# slot width
sw = 3.25
# slot depth
sd = 2
# knob/hole dimension
kn_w = 2
kn_l = 4

# basic profile
result = (cq.Workplane("XY")
          .tag("o")
          # profile
          .hLine(d1 + d2)
          .vLine(d1)
          .lineTo(d1, d1 + d2)
          .hLine(-d1)
          .close()
          .extrude(length)
          )

# lower end
result = (result
          .workplaneFromTagged("o")
          .hLine(d1 + d2)
          .vLine(d1)
          .lineTo(d1, d1 + d2)
          .hLine(-d1)
          .close()
          .workplaneFromTagged("o")
          .transformed(offset=(0, 0, -ch))
          .hLine(d1 + d2 - ch)
          .vLine(d1 - ch)
          .lineTo(d1 - ch, d1 + d2 - ch)
          .hLine(-(d1 - ch))
          .close()
          .loft()
          )

# upper end
result = (result
          .workplaneFromTagged("o")
          .transformed(offset=(0, 0, length))
          .hLine(d1 + d2)
          .vLine(d1)
          .lineTo(d1, d1 + d2)
          .hLine(-d1)
          .close()
          .workplaneFromTagged("o")
          .transformed(offset=(0, 0, length + ch))
          .hLine(d1 + d2 - ch)
          .vLine(d1 - ch)
          .lineTo(d1 - ch, d1 + d2 - ch)
          .hLine(-(d1 - ch))
          .close()
          .loft()
          )

# knob
kn_offset = 0.3
result = (result
          .workplaneFromTagged("o")
          .transformed(offset=((d1 + d2)/2 - kn_offset , (d1 + d2)/2 - kn_offset , length + ch))
          .rect(kn_w, kn_w)
          .extrude(kn_l)
          )

# hole
result = (result
          .workplaneFromTagged("o")
          .transformed(offset=((d1 + d2)/2 - kn_offset , (d1 + d2)/2 - kn_offset , -ch))
          .rect(kn_w + 0.2, kn_w + 0.2)
          .cutBlind(kn_l + 1)
          )

result = (result
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

