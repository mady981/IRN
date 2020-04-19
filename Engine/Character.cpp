#include "Character.h"

Character::Character( const int width,const int height,const float holdtime,const int nanimations,const Vec2f& pos,const float speed,const Surface& sprite )
	:
	pos( pos ),
	speed( speed ),
	sprite( sprite )
{
	//Walking Animation
	for ( int i = 0; i < ( int )Sequence::StandingLeft; ++i )
	{
		animations.emplace_back( Animation( width,i * height,width,height,holdtime,nanimations,sprite ) );
	}
	//Standing Animation
	for ( int i = ( int )Sequence::StandingLeft; i < ( int )Sequence::Count; ++i )
	{
		animations.emplace_back( Animation( 0,( i - ( int )Sequence::StandingLeft ) * height,width,height,holdtime,1,sprite ) );
	}
}

void Character::SetDirection( Vec2f& dir )
{
	if ( dir.x < 0 )
	{
		CurrAniation = Sequence::WalkingLeft;
	}
	else if ( dir.x > 0 )
	{
		CurrAniation = Sequence::WalkingRight;
	}
	else if ( dir.y < 0 )
	{
		CurrAniation = Sequence::WalkingUp;
	}
	else if ( dir.y > 0 )
	{
		CurrAniation = Sequence::WalkingDown;
	}
	else
	{
		if ( ( int )CurrAniation < ( ( int )Sequence::Count / 2 ) )
		{
			CurrAniation = Sequence( ( int )CurrAniation + ( ( int )Sequence::Count / 2 ) );
		}
	}
	dir.Nomalize();
	vel = dir * speed;
}

void Character::Update( float dt )
{
	pos += vel * dt;
	animations[( int )CurrAniation].Update( dt );
}

void Character::Draw( Graphics& gfx ) const
{
	animations[( int )CurrAniation].Draw( pos,gfx );
}
