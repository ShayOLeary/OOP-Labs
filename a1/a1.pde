int centX,centY;
void setup()
{
  size(600, 600);
  stroke(255);
  fill(0);
  centX = width / 2;
  centY = height / 2;
}
void draw()
{
  background(255);
  rectMode(CENTER);
  Player a = new Player();
}


class Player {
  
  
  Player()
  {
  paint();
  }
  
  void paint()
  {
    fill(0,0,255);
    rect(centX,height-25,50,50);
  }
  
}

