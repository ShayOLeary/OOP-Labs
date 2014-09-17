

void setup() {
  background(0);
  stroke(255, 255, 0);
  size(700, 200);
}


void draw() {
  int i;
  //create array of face objects
  Face[] faces = new Face[7];
  
  for (i=1; i<faces.length; i++)
  {
    faces[i] = new Face(100*i);
  }
}


class Face {

  int x;
  Face(int px) {
    x =  px;
    paint();
  }

  void paint() {
    fill(0);
    ellipse(x, 50, 100, 100); 
    //mouth
    line(x-15, 70, x+15, 70);
    line(x-20, 65, x-15, 70);
    line(x+15, 70, x+20, 65);
    //eyes
    ellipse(x-20, 20, 8, 8);
    ellipse(x+20, 20, 8, 8);
    //nose
    ellipse(x, 45, 8, 8);
  }
}

