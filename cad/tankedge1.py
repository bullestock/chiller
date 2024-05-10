points = [(0, 0), (0, 10), (0, 20), (0, 40),
          (-5, 55), (-12, 85), (-2.5, 110), (50, 111),
          (75, 111), (100, 111), (157.5, 111)]

spline_path = cq.Workplane("YX").spline(points)

solid = cq.Workplane("YZ").rect(10, 10).sweep(spline_path)

notch = (cq.Workplane("YZ")
         .transformed(offset=(0, 3, 0))
         .rect(3, 5)
         .sweep(spline_path)
)

solid = solid - notch

show_object(solid)
#show_object(notch)