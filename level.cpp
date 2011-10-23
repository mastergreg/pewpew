#include "level.h"
level::level()
{
  WINDOW_SIZEX=800;
  WINDOW_SIZEY=600;
  windowX=0;
  windowY=0;
  font = GLUT_BITMAP_TIMES_ROMAN_24;
  tinyFont = GLUT_BITMAP_8_BY_13;
  enemies_killed = 0;
  enemies_before = 0;
  enemies_after = 0;
  score = 0;
  dtime = 0;
  ftime = 0;
  startingSpeed.set_vector(vector2D(0.001,0.005,0,0));
  playerShip = new ship();
  playerShip->set_speed(startingSpeed);
  lifeDraw=playerShip->get_life();
  //paused=true;
  xploded=false;
  MenuChoice=0;
  ZoomLevel=100;
  srand(time(NULL));
}
void level::display()
{
  drawScene();
  play();
}
void level::ZooMStart()
{
}


void level::start()
{
}
void level::drawScene()
{
  drawAll();
}
void level::play()
{
  ScoreBasedEvents();
  TimeBasedEvents();
  if (playerShip->isAlive())
  {
    std::list<game_object *> newdrawList;
    int prlife = playerShip->get_life();
    newdrawList = playerShip->collisions(enemyList);
    if (prlife>playerShip->get_life()) 
    {
      playerShip->downgradeWeapons();
      rumble();
    }
    drawableList.insert(drawableList.end(),newdrawList.begin(),newdrawList.end());
  }
  moveAll();
  playStick();
}
void level::drawAll()
{
  drawGrid();
  if (playerShip->isAlive()) 
  {
    displayLife();
    playerShip->draw();
    playerShip->drawUpgradeRing(fireUpgradeList,lifeUpgradeList);
    clipArroundShip();

  }
  else
  {
    shipExplode(playerShip->get_pos());
  }
  for_each(drawableList.begin(),drawableList.end(),draw_all);
  for_each(fireList.begin(),fireList.end(),draw_all);
  for_each(fireUpgradeList.begin(),fireUpgradeList.end(),draw_all);
  for_each(lifeUpgradeList.begin(),lifeUpgradeList.end(),draw_all);
  for_each(enemyList.begin(),enemyList.end(),draw_all);
}

void level::TimeBasedEvents()
{
  dtime++;
  ftime++;
  if (dtime==200)
  {
    insertDummyShip();
    dtime=0;
  }
  if(playerShip->isAlive() && ftime>=10)
  {
    std::list<fire *> newFireList;
    ftime=0;
    newFireList = playerShip->shoot(shipMouseAngle());
    fireList.insert(fireList.end(),newFireList.begin(),newFireList.end());
  }

}
void level::moveAll()
{
  if(playerShip->isAlive()) 
  {
    playerShip->move(); 
  }
  for_each(drawableList.begin(),drawableList.end(),move_all);
  for_each(enemyList.begin(),enemyList.end(),move_all);
  for_each(fireList.begin(),fireList.end(),move_all);
  for_each(fireUpgradeList.begin(),fireUpgradeList.end(),move_all);
  for_each(lifeUpgradeList.begin(),lifeUpgradeList.end(),move_all);
}
void level::reset()
{
  glLoadIdentity();
  enemies_killed =0 ;
  enemies_before = 0;
  enemies_after = 0;
  score = 0;           
  dtime = 0;
  ftime=0;     
  delete playerShip;

  playerShip = new ship;
  playerShip->set_speed(startingSpeed);
  lifeDraw=playerShip->get_life();

  //delete all elements TODO
  fireList.clear();
  enemyList.clear();
  fireUpgradeList.clear();
  lifeUpgradeList.clear();
  drawableList.clear();

  xploded=false;
  ZoomLevel=100;
  srand(time(NULL));
}
void level::ScoreBasedEvents()
{
  enemies_before = (int) enemyList.size();
  globalCollisions();
  clearDead();
  enemies_after = (int) enemyList.size();
  enemies_killed+=enemies_before-enemies_after;
  if (enemies_killed > 0)
  {
    enemies_killed = 0;
    if(score % 10000 == 0)
      insertFireUpgrade();
    if(score % 50000 == 0) 
    {
      insertSpiralShip();
    }
    if(score % 100000 == 0) 
    {
      insertLifeUpgrade();
    }
  }
}
void level::shipExplode(vector2D position)
{
  if(!xploded) drawableList.push_back(new xplosion(position));
  xploded=true;
}
void level::insertSpiralShip()
{
  double px = ((rand() % 2000)-1000)*(DIMENSION-0.4)/1000.;
  double py = ((rand() % 2000)-1000)*(DIMENSION-0.4)/1000.;
  vector2D rpos(px,py,0,0);
  double sx = 0.001;
  double sy = 0.001;
  vector2D resp(sx,sy,0,0);
  enemyList.push_back(new spiralShip(rpos,resp));
}
void level::insertLifeUpgrade()
{
  double px = ((rand() % 2000)-1000)*(DIMENSION-0.25)/1000.;
  double py = ((rand() % 2000)-1000)*(DIMENSION-0.25)/1000.;
  vector2D rpos(px,py,0,0);
  lifeUpgradeList.push_back(new lifeUpgrade(rpos));
}
void level::insertFireUpgrade()
{
  double px = ((rand() % 2000)-1000)*(DIMENSION-0.25)/1000.;
  double py = ((rand() % 2000)-1000)*(DIMENSION-0.25)/1000.;
  vector2D rpos(px,py,0,0);
  fireUpgradeList.push_back(new fireUpgrade(rpos));
}
void level::insertDummyShip()
{
  double px = ((rand() % 2000)-1000)*(DIMENSION-0.25)/1000.;
  double py = ((rand() % 2000)-1000)*(DIMENSION-0.25)/1000.;
  vector2D rpos(px,py,0,0);
  double sx = ((rand() % 2000)-1000)/100000.;
  double sy = ((rand() % 2000)-1000)/100000.;
  vector2D resp(sx,sy,0,0);
  enemyList.push_back(new dummyship(rpos,resp));
}
void level::clipArroundShip()
{
  vector2D position = playerShip->get_pos();
  vector2D speed = playerShip->get_speed();
  double px=position.getX();
  double py=position.getY();
  //double pz=position.getZ();
  double sx=speed.getX();
  double sy=speed.getY();
  double speedL = sqrt(sx*sx+sy*sy);
  double playWindow = 900000*speedL/SPEED_MAX;
  playWindow =  playWindow < 3 ? playWindow : 3;
  playWindow =  playWindow > 0.5 ? playWindow : 0.5;
  double initZoom = DIMENSION*ZoomLevel/100.;
  if(initZoom>playWindow)
  {
    glLoadIdentity();
    glOrtho(px-initZoom,px+initZoom,py-initZoom,py+initZoom,-5,5);
    ZoomLevel--;
  }
  else
  {
    glLoadIdentity();
    glOrtho(px-playWindow, px+playWindow, py-playWindow, py+playWindow, -5.0, 5.0); 
  }

}


void level::drawGrid()
{
  double i;
  GLfloat  gridColor[]={0.,0.25,0.5};
  GLfloat  borderColor[]={0.66,0.0,0.0};
  for(i=-DIMENSION+0.2;i<DIMENSION;i+=0.2)
  {
    glPushMatrix();
    glLineWidth(1);
    glColor3fv(gridColor);
    glBegin(GL_LINES);
    glVertex3f(i,-DIMENSION,0);
    glVertex3f(i,DIMENSION,0);
    glVertex3f(-DIMENSION,i,0);
    glVertex3f(DIMENSION,i,0);
    glEnd();
    glPopMatrix();
  }
  glLineWidth(5);
  glColor3fv(borderColor);
  glBegin(GL_LINES);

  glVertex3f(DIMENSION-0.2,-DIMENSION,0);
  glVertex3f(DIMENSION-0.2,DIMENSION,0);

  glVertex3f(-DIMENSION+0.2,-DIMENSION,0);
  glVertex3f(-DIMENSION+0.2,DIMENSION,0);

  glVertex3f(-DIMENSION,DIMENSION-0.2,0);
  glVertex3f(DIMENSION,DIMENSION-0.2,0);

  glVertex3f(-DIMENSION,-DIMENSION+0.2,0);
  glVertex3f(DIMENSION,-DIMENSION+0.2,0);

  glEnd();

}
void level::displayLife()
{
  int mlife = playerShip->get_life();
  glPushMatrix();
  glLoadIdentity();
  show_score(1.0,1.0,score);
  if (lifeDraw<mlife) 
  {
    lifeDraw+=10;
  }
  else if (lifeDraw > mlife ) 
  {
    lifeDraw-=10;
  }
  glBegin(GL_LINES);
  GLfloat  myBcolor[]={0.0,0.0,0.0};
  GLfloat  my1color[]={0.0,1.0,0.0};
  glColor3fv(myBcolor);
  glLineWidth(30);
  glVertex3f(-1.0,.999,0);  
  glVertex3f(1.0,.999,0);  
  glLineWidth(10);
  glColor3fv(my1color);
  glVertex3f(-0.9,1.,0);  
  GLfloat  mycolor[]={0.66,0.0,0.0};
  glColor3fv(mycolor);
  glVertex3f(lifeDraw/3000.0-0.9,1.,0);  
  glEnd();
  glPopMatrix();
}
void level::collisionDetect(std::list<game_ship *> bullets,std::list<game_ship *> enemies)
{
  std::list<game_ship *>::iterator enemy = enemies.begin();
  std::list<game_object *> newdrawList;
  while (enemy !=enemies.end())
  {
    newdrawList = (*enemy)->collisions(bullets);
    drawableList.insert
      (drawableList.end(),newdrawList.begin(),newdrawList.end());
    enemy++;
  }
}

void level::pauseResume()
{
  gpause();
}
void level::globalCollisions()
{
  collisionDetect(fireList,enemyList);
  playerShip->collectFireUpgrades(fireUpgradeList);
  playerShip->collectLifeUpgrades(lifeUpgradeList);
}
void level::clearDead()
{
  clean_dead(&fireList);
  clean_dead(&fireUpgradeList);
  clean_dead(&lifeUpgradeList);
  clean_dead(&enemyList);
  clean_dead(&drawableList);
}

void level::clean_dead(std::list<game_ship *> *ls)
{
  std::list<game_ship *>::iterator iter = ls->begin();
  for(;iter!=ls->end();iter++)
  {
    if ((*iter)->get_life()<0)
    {
      delete *iter;
      *iter = NULL;
    }
  }
  ls->remove(NULL);

}
void level::clean_dead(std::list<game_object *> *ls)
{
  std::list<game_object *>::iterator iter = ls->begin();
  for(;iter!=ls->end();iter++)
  {
    if ((*iter)->get_life()<0)
    {
      delete *iter;
      *iter = NULL;
    }
  }
  ls->remove(NULL);

}

void level::insertScoreTag(vector2D pos,int points)
{
  drawableList.push_back(new score_tag(pos,points));
  increaseScore(points);
}



void level::increaseScore(int points)
{
  score+=points;
}



void level::show_score(double x,double y,int score)
{
  int len, i;
  char c_score[20];
  sprintf(c_score,"%d",score);
  glRasterPos2f(x, y);
  len = (int) strlen(c_score);
  for (i = 0; i < len; i++) 
  {
    glutBitmapCharacter(font, c_score[i]);
  }
}
void level::reshape(int w,int h)
{
  GLsizei minSize=w>h ? (GLsizei) h : (GLsizei) w;
  minSize-=50;
  GLsizei startX=((w-h)/2.0-100);
  if (startX>0)
  {
    glViewport(startX,0,minSize,minSize);
  }
  else
  {
    glViewport(0,-startX,minSize,minSize);
  }
  WINDOW_SIZEX=w;
  WINDOW_SIZEY=h;
}
void level::myMouseFunction(int x,int y)
{
  vector2D pos = playerShip->get_pos();
  GLint viewport[4];
  GLdouble mvmatrix[16], projmatrix[16];
  GLint realy;  /*  OpenGL y coordinate position  */
  GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */

  glGetIntegerv (GL_VIEWPORT, viewport);
  glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
  glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
  /*  note viewport[3] is height of window in pixels  */
  realy = viewport[3] - (GLint) y - 1;
  gluUnProject ((GLdouble) x, (GLdouble) realy, 0.0,
      mvmatrix, projmatrix, viewport, &wx, &wy, &wz);

  mX=wx-pos.getX();
  mY=wy-pos.getY();

}
double level::shipMouseAngle()
{
  double ax=mX;

  double ay=mY;
  if(ax>0) 
  {
    return atan(ay/ax);
  }
  else if (ax<0)
  {
    return atan(ay/ax)+M_PI;
  }
  else if (ay>0)
  {
    return M_PI/2;
  }
  else 
  {
    return -M_PI/2;
  }
}
void level::keyboardReleaseFunction(unsigned char key,int x, int y)
{
  vector2D current_speed;
  current_speed.set_vector(playerShip->get_speed());
  switch (key)
  {
    case 'w':
      //current_speed.increase_vector(0,0.001,0);
      current_speed.increase_reset();//scale(1.2,1.2,1.2);
      playerShip->set_speed(current_speed);
      break;

    case 'a':
      //current_speed.increase_vector(-0.001,0,0);
      current_speed.rotate_reset();
      playerShip->set_speed(current_speed);
      break;
    case 's':
      //current_speed.increase_vector(0,-0.001,0);
      current_speed.increase_reset();//scale(1.2,1.2,1.2);
      playerShip->set_speed(current_speed);
      break;

    case 'd':
      //current_speed.increase_vector(0.001,0,0);
      current_speed.rotate_reset();
      playerShip->set_speed(current_speed);
      break;
    case 'q':
      current_speed.scale(0.25,0.25);
      playerShip->set_speed(current_speed);
      break;
    case 'e':
      current_speed.scale(4,4);
      playerShip->set_speed(current_speed);
      break;
  }
}
void level::playStick()
{
  vector2D current_speed;
  current_speed.set_vector(playerShip->get_speed());
  static wwvi_js_event js_state;
  js_state.button[4]=0;
  js_state.button[5]=0;
  if (get_joystick_status(&js_state)==0)
  {
    double out = 0;
    if (js_state.button[9]==1)
    {
      pauseResume();
    }
    if (js_state.button[7]==1)
    {
      current_speed.vincrease();
      playerShip->set_speed(current_speed);
    }
    else if (js_state.button[6]==1)
    {
      current_speed.vdecrease();
      playerShip->set_speed(current_speed);
    }
    else if (js_state.button[5]==1)
    {
      current_speed.scale(2,2);
      playerShip->set_speed(current_speed);
    }
    else if (js_state.button[4]==1)
    {
      current_speed.scale(0.5,0.5);
      playerShip->set_speed(current_speed);
    }
    else
    {
      current_speed.increase_reset();//scale(1.2,1.2,1.2);
      playerShip->set_speed(current_speed);
    }
    double newAngle=playerShip->get_angle();
    double newX = (double) js_state.stick1_x;
    double newY = (double) js_state.stick1_y;
    if (newX != 0)
    {
      jX = newX;
    }
    if (newY != 0)
    {
      jY = -newY;
    }

    if  (jX > 0)
    {
      newAngle = atan(jY/jX);
      playerShip->set_angle(newAngle);
    }
    else if (jX < 0 )
    {
      newAngle = M_PI+atan(jY/jX);
      playerShip->set_angle(newAngle);
    }
    else
    {
      if (jY != 0)
      {
        newAngle = ((jY > 0) ? -1 : ((jY < 0) ? 1 : 0) )*atan(M_PI/2);
        playerShip->set_angle(newAngle);
      }
    }
    out = (double) js_state.stick2_x;
    if  (out != 0)
    {
      mX = out;
    }
    out = (double) js_state.stick2_y;
    if  (out != 0)
    {
      mY = -out;
    }
  }
}
void level::keyboardFunction(unsigned char key,int x,int y)
{
  vector2D current_speed;
  current_speed.set_vector(playerShip->get_speed());
  switch (key)
  {
    case 27:
      pauseResume();
      break;
    case 'w':
      //current_speed.increase_vector(0,0.001,0);
      current_speed.vincrease();//scale(1.2,1.2,1.2);
      playerShip->set_speed(current_speed);
      break;
    case 'a':
      //current_speed.increase_vector(-0.001,0,0);
      current_speed.rotatel();
      current_speed.scale(1.01,1.01);
      playerShip->set_speed(current_speed);
      break;
    case 's':
      //current_speed.increase_vector(0,-0.001,0);
      current_speed.vdecrease();//scale(0.8,0.8,0.8);
      playerShip->set_speed(current_speed);
      break;
    case 'd':
      //current_speed.increase_vector(0.001,0,0);
      current_speed.rotater();
      current_speed.scale(1.01,1.01);
      playerShip->set_speed(current_speed);
      break;
    case 'q':
      current_speed.scale(4,4);
      playerShip->set_speed(current_speed);
      break;
    case 'e':
      current_speed.scale(0.25,0.25);
      playerShip->set_speed(current_speed);
      break;
    case 'p':
      pauseResume();
      break;
    case 'r':
      if (!playerShip->isAlive())
      {
        reset();
      }
      break;
  }

}
void level::specialKeyboardFunction(int key,int x, int y)
{
}

