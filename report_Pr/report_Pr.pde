import processing.serial.*;

Serial port;

int px, py;
int ex_1, ey_1, ex_2, ey_2;
int evx, evy;

void setup()
{
  size(640, 480);
  textAlign(CENTER);
  port = new Serial(this, "COM3", 9600);
  frameRate(30);
  px = 320;
  py = 240;
  evx = 2;
  evy = 2;
  ex_1 = (int)(random(10, 600));
  ey_1 = -250;
  ex_2 = -250;
  ey_2 = (int)(random(0, 440));
  port.clear();
}

/*void keyPressed()
{
  if(px > 20)
    if(keyCode == LEFT)px -= 10;
  if(py > 20)
    if(keyCode ==UP)py -= 10;
  if(px < 620)
    if(keyCode == RIGHT)px += 10;
  if(py < 460)
    if(keyCode == DOWN)py += 10;
}*/

/*void keyPressed()
{
  if(port.available() > 0){
    int p = port.read();
  if(px > 20)
    if(p == 1)px -= 10;
  if(py > 20)
    if(p == 2)py -= 10;
  if(px < 620)
    if(p == 3)px += 10;
  if(py < 460)
    if(p == 4)py += 10;
  }
}*/

void draw()
{
  background(255);
  if(port.available() > 0){
    int p = port.read();
  if(px > 20)
    if(p == 1)px -= 50;
  if(py > 20)
    if(p == 2)py -= 50;
  if(px < 620)
    if(p == 3)px += 50;
  if(py < 460)
    if(p == 4)py += 50;
  }
  ellipse(px, py, 30, 30);
  rect(ex_1, ey_1, 30, 250);
  ey_1 = ey_1 + evy;
  rect(ex_2, ey_2, 250, 30);
  ex_2 = ex_2 + evx;
  if(ey_1 > 480)
  {
    ex_1 = (int)(random(10, 600));
    ey_1 = -250;
    evy += 2;
  }
  if(ex_2 > 640)
  {
    ex_2 = -250;
    ey_2 = (int)(random(0, 440));
    evx += 2;
  }
  if(px > ex_1 && px < ex_1 + 30 && py > ey_1 && py < ey_1 + 250){
    px = ex_1 + 15;
    py = ey_1 + 120;
    port.write('a');
    background(0);
    textSize(100);
    text("Failed", 320, 240);
  }
  if(px > ex_2 && px < ex_2 + 250 && py > ey_2 && py < ey_2 + 30){
    px = ex_2 + 120;
    py = ey_2 + 15;
    port.write('a');
    background(0);
    textSize(100);
    text("Failed", 320, 240);
  }
}
