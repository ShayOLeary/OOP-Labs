//sketch for blue gate with increasing square pattern

void setup()
{
  background(255);
  size(500, 500);
}

void draw()
{
  int centX=width/2;
  int centY=height/2;
  background(255);
  rectMode(CENTER);
  noFill();
  strokeWeight(5);
  stroke(0, 0, 255);
  line(0, 0, 500, 500);
  line(500, 0, 0, 500);

  for (int i=0; i<width-100; i++)
  {
    rect(centX, centY, 70*i, 70*i);
  }
}

