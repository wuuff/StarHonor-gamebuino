#include "StarField.h"


StarField::StarField()
{
  _Stars = new Star[20];

  for( int i(0); i < 20; i++ )
  {
    Star newStar;
    newStar.xPosition = random(0, 84);
    newStar.yPosition = random(0, 48);
    newStar.velocity = random(1, 25);
    _Stars[i] = newStar;
  }
}

void StarField::Draw()
{
  for( int i(0); i < 20; i++ )
  {
    Star star = _Stars[i];
    //arduboy.drawPixel( star.xPosition, star.yPosition, 1 );
    arduboy.display.drawPixel( star.xPosition, star.yPosition );
  }
}


void StarField::Move( Vector2d v )
{
  for( int i(0); i < 20; i++ )
  {
    Star* star = &_Stars[i];
    float velocityOverTime = star->velocity * DeltaTime;
    star->xPosition += v.x * velocityOverTime;
    star->yPosition += v.y * velocityOverTime;

    BoundsCheck(star);
  }
}

void StarField::BoundsCheck(Star* star)
{
  bool setVelocity = false;
  int xPos = star->xPosition;
  int yPos = star->yPosition;
  if ( xPos > 84 )
  {
    star->xPosition = 0.0f;
    star->yPosition = random(0, 48);
    setVelocity = true;
  }
  else if ( xPos < 0 )
  {
    star->xPosition = 84.0f;
    star->yPosition = random(0, 48);
    setVelocity = true;
  }
  else if ( yPos > 48 )
  {
    star->xPosition = random(0, 84);
    star->yPosition = 0.0f;
    setVelocity = true;
  }
  else if ( yPos < 0 )
  {
    star->xPosition = random(0, 84);
    star->yPosition = 48;
    setVelocity = true;
  }
  if ( setVelocity )
    star->velocity = random(1, 25);
}

