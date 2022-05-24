// Outer pipe
r1 = 4.5;
// Pipe bore
r2 = 3.0;
// Sensor bore
r3 = 3.0;
// Thick pipe
r4 = 6;
// Inner space
r5 = 4;
// Length of each arm
h1 = 20;
// Length of sensor tap
h2 = 20;

difference()
{
  union()
  {
    // Vertical outer pipe
    cylinder(r = r1, h = h1*2);

    // Thick pipe
    translate([0, 0, h1/2]) 
    cylinder(r = r4, h = h1);

    // Horizontal pipe
    translate([0, 0, h1]) 
      rotate([0, 90, 0]) 
        difference()
        {
          // Outer pipe
          translate([0, 0, 0]) cylinder(r = r4, h = h2);
          // Bore
          translate([0, 0, 1]) cylinder(r = r3, h = h2);
        }
  }
  union()
  {
    // Vertical bore
    translate([0, 0, -1]) cylinder(r = r2, h = h1*2+2);
    translate([0, 0, h1-(h1-6)/2]) cylinder(r = r5, h = h1-6);
  }
}
