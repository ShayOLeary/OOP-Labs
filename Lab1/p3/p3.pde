

void setup() {
  background(0);
  stroke(255, 255, 0);
  size(700, 800);
}


void draw() {
  int i, j;

  //create array of face objects
  Face[][] faces = new Face[8][8];
  for (i=1; i<faces[i].length-1; i++)
  {
    //nested loop for rows
    for (j=1; j<faces[j].length-1; j++) {
      faces[i][j] = new Face(100*i, 100*j);
    }
  }
}


class Face {

  int x, y;
  Face(int px, int py) {
    x= px;
    y= py;
    paint();
  }


  void paint() {
    fill(0);
    ellipse(x, y, 100, 100); 
    //mouth
    line(x-15, y+20, x+15, y+20);
    line(x-20, y+9, x-15, y+19);
    line(x+15, y+19, x+20, y+9);
    //eyes
    ellipse(x-20, y-20, 8, 8);
    ellipse(x+20, y-20, 8, 8);
    //nose
    ellipse(x, y, 8, 8);
  }
}

