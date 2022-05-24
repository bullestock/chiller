r1 = 14.5;
r2 = 12.0;
r3 = 6.0;
r4 = 3.5;
h1 = 20;
h2 = 3;
h3 = 15;

difference() {
  cylinder(r = r1, h = h1+h2+h3);
  translate([0, 0, -1]) cylinder(r = r4, h = h1+h2+h3+2);
  translate([0, 0, -1]) cylinder(r = r2, h = h3+1);
  difference() {
    translate([0, 0, h3+h2]) cylinder(r = r1+1, h = h1+1);
    translate([0, 0, h3+h2+-1]) cylinder(r = r3, h = h1+1);
  }
}
