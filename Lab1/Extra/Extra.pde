float x, y, r, g, b, radius;
int timer;

void setup() {
  size(500, 500);
  background(255);
}

void draw()
{ 
  x = random(width);
  y = random(height);
  radius = random(30);

  fill(random(255), random(255), random(255));
  rect(x, y, radius, radius);
}

