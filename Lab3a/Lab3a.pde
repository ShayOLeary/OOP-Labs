//sketch for shiny cirle filled with dots

void setup()
{
  background(255);
  size(500, 500);
}

void draw()
{
  background(255);

  float cx = width/2;
  float cy = height/2;
  float diameter = width*.9;
  stroke(#FF8533);
  fill(#FF8533);
  ellipse(cx, cy, diameter-5, diameter-5);
  stroke(255);
  noFill();
  ellipse(cx, cy, diameter-20, diameter-20);
  fill(#FFAA77);

  for (int i=0; i<diameter+200; i+=20)
  {
    for (int j=0; j<diameter+200; j+=20)
    {
      stroke(255);
      fill(255);
      ellipse(i, j, 5, 5);
    }
  }
}

