//Sketch for rectangle roll over button and a bouncing button

int centX;
int centY;
int ballX=50;
int ballY=50;
int ballXSpeed = 5;
int ballYSpeed = 3;
static boolean toggled = false;
void setup()
{
  size(450, 450);
  background(255);
}

void draw()
{
  background(255);
  int centX = width / 2; 
  int centY = height / 2;
  if (!toggled)fill(200);
  rectMode(CENTER);
  rect(centX, centY, width*.3, height*.3);
  
 
  fill(255,0,0);
  ellipse( ballX, ballY, 30, 30 );

  ballX=ballX+ballXSpeed;
  ballY=ballY+ballYSpeed;

  if (ballX > width || ballX < 0) ballXSpeed *= -1;
  
  if (ballY > height || ballY < 0) ballYSpeed *= -1;
  
  if ((mouseX > 150) && (mouseX < 300) && (mouseY <300) && (mouseY > 150) && !toggled)
  {
    fill(0, 0, 255);
    rect(centX, centY, width*.3, height*.3);
  }
}

void mousePressed()
{
  if (!toggled)
  {
    fill(255, 0, 0);
    rect(centX = width/2, centY=height/2, width*.3, height*.3);
    toggled=true;
  }
}


