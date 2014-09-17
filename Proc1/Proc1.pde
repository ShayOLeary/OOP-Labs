void setup(){
 background(0);
stroke(255,255,0);
size(400,400);
}


void draw(){
  fill(0);
 ellipse(50,50,100,100); 
 //eyes
  ellipse(30,20,8,8);
  ellipse(70,20,8,8);
  //nose
   ellipse(50,45,8,8);
   //mouth
   line(35,70,65,70);
   line(35,70,32,65);
   line(65,70,68,65);

}
