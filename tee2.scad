// Pipe bore
r1 = 4.5;
// Sensor bore
r2 = 3.0;
w1 = 15.0;
w2 = 15.0;
w3 = 30.0;

difference()
{
   translate([-w1/2, -w2/2, -w2/2])
      cube([w1, w2, w3]);

   rotate([0,90,0])
      translate([0,0,-w2/2-1])
         cylinder(r = r1, h = w2+2);

   cylinder(r = r2, h = w3);
}
