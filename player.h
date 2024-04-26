#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include "bullet.h"
#include "addon.h"
using namespace sf;
using namespace std;
class Player: public addon {
public:
	Texture tex;
	Sprite sprite;
	Texture t;
	Sprite s;
	float speed=4;
	float  x,y;
	float rotate_l=-1,rotate_r=1; 
	bool movement_right=false;//if the spaceship has moved
	bool movement_left=false;//if the spaceship has moved
	bool movement=false;
	string png;
	//bullet* b;//bullet
	//addon* dang;
Player() 
{

	
	
	
}
void place_ship(string png_path,bool mover=false,bool movel=false)
{
	tex.loadFromFile(png_path);
	sprite.setTexture(tex);
	x=340;y=650; 
	sprite.setPosition(x,y);
	//sprite.setRotation(300.f);
	sprite.setScale(0.75,0.75);
	this->png=png_path;
}
	
void explosion()
{
	
	//b=new bullet("img/bullet.png");
	t.loadFromFile("img/playerShip3_damage2.png");
	s.setTexture(t);
	
	s.setPosition(x,y);
	//sprite.setRotation(300.f);
	s.setScale(0.75,0.75);
}
void move(std::string s)
{
	float delta_x=0,delta_y=0;
	//if(s=="l")
		//move the player left
	//else if(s=="r")
		//move the player right
	if(s=="u")
	{
		
			delta_y=-1;// y-=1;
		
			if (movement_left)
			{
				delta_x=-1;
				//movement_right=false;
				
			}
			if (movement_right)
			{
				 delta_x=1;
				//movement_left=false;
			}
		
		
		//cout<<x<<y<<endl;
		
	}
	else if(s=="d")
	{
		
			delta_y=1; //y+=1;
		
			if (movement_left)
			{
				delta_x=1;
				//movement_right=false;
				
			}
			if (movement_right)
			{
				 delta_x=-1;
				//movement_left=false;
			}
		
		
		
	}
	else if (s=='l')
	{
		
			delta_x=-1; //x-=1;
		
		
		
	}
	else if(s=='r')
	{
		
			delta_x=1; //x+=1;
		
		
		
	}

	delta_x*=speed;
	delta_y*=speed;
	x+=delta_x;
	y+=delta_y;
	if (x>750)
	{
		x=0;
		sprite.setPosition(x,y);
	}
	else if (x<0)
	{
		x=750;
		sprite.setPosition(x,y);
	}
	else if (y<0)
	{
		y=780;
		sprite.setPosition(x,y);
	}
	else if (y>780)
	{
		y=0;
		sprite.setPosition(x,y);
	}
	
	sprite.move(delta_x, delta_y);
	

}
void rotate(string s)
{
	
	if (s=='w')//diagnolly left 
	{
		//rotate_l;
		//sprite.setRotation(-45);
		//rotate_l-=1;
		movement_left=true;
		movement_right=false;
		movement=true;
		if (this->png=="img/player_ship.png")
		{
			tex.loadFromFile("img/rotate/image(6).png");
			sprite.setTexture(tex);
		}
		else if (this->png=="img/PNG/playerShip2_orange.png")
		{
			tex.loadFromFile("img/rotate/image(9).png");
			sprite.setTexture(tex);
		}
		else if (this->png=="img/PNG/playerShip1_blue.png")
		{
			tex.loadFromFile("img/rotate/image(10).png");
			sprite.setTexture(tex);
		}
		
	}
	
	else if (s=='s')//diagnolly right 
	{
		//rotate_r;
		//sprite.setRotation(45);
		//rotate_r+=1;
		movement_right=true;
		movement_left=false;
		movement=true;
		if (this->png=="img/player_ship.png")
		{
			tex.loadFromFile("img/rotate/image(7).png");
			sprite.setTexture(tex);
		}
		else if (this->png=="img/PNG/playerShip2_orange.png")
		{
			tex.loadFromFile("img/rotate/image(8).png");
			sprite.setTexture(tex);
		}
		else if (this->png=="img/PNG/playerShip1_blue.png")
		{
			tex.loadFromFile("img/rotate/image(11).png");
			sprite.setTexture(tex);
		}
	}
	else if (s=='a')
	{
		movement_right=false;
		movement_left=false;
		//sprite.setRotation(0);
		if (this->png=="img/player_ship.png")
		{
			tex.loadFromFile("img/player_ship.png");
			sprite.setTexture(tex);
		}
		else if (this->png=="img/PNG/playerShip2_orange.png")
		{
			tex.loadFromFile("img/PNG/playerShip2_orange.png");
			sprite.setTexture(tex);
		}
		else if (this->png=="img/PNG/playerShip1_blue.png")
		{
			tex.loadFromFile("img/PNG/playerShip1_blue.png");
			sprite.setTexture(tex);
		}
	}
	
	//cout<<rotate_l<<endl;
}

	
float position_x() //return the x co-ordinate of the space ship
{
	return x;

}
float position_y()//returns the position of y co-ordinate
{
	return y;
}
void bullet_speed_change(bullet& b, int x)
{
	if (x==1)
		b.acc=8;
	else if (x==2)
		b.acc=12;
	else if (x==3)
		b.acc=10;
}
	
~Player()
{
	//delete b;
	//b=NULL;
}	
};


class livecount
{
public:
	Texture live;
	Sprite lives;
	livecount(){};
	void lives_ship(int x,int y)
	{
		live.loadFromFile("img/player_ship.png");
		lives.setTexture(live);
		
		lives.setPosition(x,y);
		//sprite.setRotation(300.f);
		lives.setScale(0.3,0.3);
	}
};
