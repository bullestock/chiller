import cadquery as cq

d1 = 16
d2 = 25
w1 = 12.5
w2 = 20
extra_x = -4
w3 = 40
th1 = 2
h1 = 25.5
h2 = 40

# Outer shape
res = (cq.Workplane("XY")
       .tag("bot")
       .rect(2*w3+extra_x, h2)
       .extrude(d2)
       #.workplaneFromTagged("bot")
       .edges("|Z")
       .fillet(5)
       )

extra_z = 5
cutout_depth = d2-d1-2
cutout = (cq.Workplane("XY")
          .tag("cbot")
          # Main cavity
          .transformed(offset=(0, 0, cutout_depth))
          .rect(h1 + 2, h1)
          .extrude(d2)
          .edges("|Z")
          .fillet(2)
          # Round cutout for pipes
          .workplaneFromTagged("cbot")
          .transformed(offset=(0, h2/2, d2-extra_z),
                       rotate=(90, 0, 0))
          .circle(w1/2)
          .extrude(h2)
          # Extension of round cutout
          .workplaneFromTagged("cbot")
          .transformed(offset=(0, 0, d2-extra_z))
          .rect(w1, h2)
          .extrude(d1)
          # Cutout for flanges
          .workplaneFromTagged("cbot")
          .transformed(offset=(0, 0, d2-th1))
          .rect(w2, h2)
          .extrude(th1)
          )

res = (res
       - cutout.translate((-(w3+extra_x)/2, 0, 0))
       - cutout.translate(((w3+extra_x)/2, 0, 0))
       )

log(f'cc: {w3+extra_x}')

# Screw holes

msox = w1*0.6 + (w3+extra_x)/2
msoy = w1*0.6
msd = 4.5
mcsd = 10
csd = 3.5
ndia = 6.5
nth = 3

res = (res
       # mounting holes
       .workplaneFromTagged("bot")
       .transformed(offset=(msox, msoy, cutout_depth))
       .cskHole(msd, mcsd, 82)
       .workplaneFromTagged("bot")
       .transformed(offset=(msox - w1*2*0.6, -msoy, cutout_depth))
       .cskHole(msd, mcsd, 82)
       .workplaneFromTagged("bot")
       .transformed(offset=(-msox, -msoy, cutout_depth))
       .cskHole(msd, mcsd, 82)
       .workplaneFromTagged("bot")
       .transformed(offset=(-msox + w1*2*0.6, msoy, cutout_depth))
       .cskHole(msd, mcsd, 82)
       # screw holes
       .workplaneFromTagged("bot")
       .rarray((w2+w3)/2 - extra_x/2, (h1+h2)/2, 3, 2)
       .circle(csd/2)
       .cutThruAll()
       # nut holes
       .workplaneFromTagged("bot")
       .rarray((w2+w3)/2 - extra_x/2, (h1+h2)/2, 3, 2)
       .polygon(6, ndia)
       .cutBlind(nth)
       )

show_object(res)
#show_object(cutout)
