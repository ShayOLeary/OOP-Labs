

void setup() {
  background(0);
  stroke(255, 255, 0);
  size(800, 800);
}


void draw() {
  int i, j;

  //create array of face objects
  Face[][] faces = new Face[8][8];
 
  for (i=1; i<faces[i].length-1; i++)
  {
    for (j=1; j<faces[j].length-1; j++) {
      //happy faces will be even numbers
      if (i%2==0) {
        faces[i][j] = new Face(100*i, 100*j, true);
      } else
      {
        faces[i][j] = new Face(100*i, 100*j, false);
      }
    }
  }
}


class Face {

  int x, y;
  boolean happy;
  //set all the required attributes through the constructor
  Face(int px, int py, boolean happyYN ) {
    x= px;
    y= py;
    happy = happyYN;
    paint();
  }


  void paint() {

    fill(0);
    ellipse(x, y, 100, 100); 
    //mouth
    //eyes
    ellipse(x-20, y-20, 8, 8);
    ellipse(x+20, y-20, 8, 8);
    //nose
    ellipse(x, y, 8, 8);
    if (happy) {
      //happy mouth
      line(x-15, y+20, x+15, y+20);
      line(x-20, y+10, x-15, y+20);
      line(x+15, y+20, x+20, y+10);
    } else {
      //sad mouth 
      line(x-15, y+20, x+15, y+20);
      line(x-15, y+20, x-20, y+25);
      line(x+15, y+20, x+20, y+25);
    }
  }
}

