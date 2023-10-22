import cadquery as cq

stud_w = 6.7
stud_l = 20
ridge_w = 0.3
ridge_h = 0.8
ridge_spacing = 5
bracket_th = 5
bracket_w = 20
bracket_l = 50
hole_cc = bracket_l - bracket_w
hole_d = 4.3

# Stud
res = (cq.Workplane("XY")
       .tag("o")
       .box(stud_w, stud_w, stud_l, centered=(True, True, False))
       .edges(">Z")
       .chamfer(1)
       .edges("|Z")
       .fillet(1)
       )

def ridge(z):
   offset = 0.7
   return (cq.Workplane("XY")
           .transformed(offset=(0, 0, z))
           .rarray(stud_w - offset, stud_w - offset, 2, 2)
           .sphere(0.5)
           )

# Ridges on stud
for i in range(1, 4):
   res = (res + ridge(i*ridge_spacing))

# Construct bracket
bracket = (cq.Workplane("XY")
       .transformed(offset=(0, 0, -bracket_th))
       .box(bracket_l, bracket_w, bracket_th, centered=(True, True, False))
       .edges("|Z")
       .fillet(3)
       )

# Combine bracket and stud, cut mounting holes
res = (res
       .union(bracket)
       .rarray(hole_cc, 2, 2, 1)
       .circle(hole_d/2)
       .cutThruAll()
       )

show_object(res)
