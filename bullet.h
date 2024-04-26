#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
using namespace sf;
using namespace std;
class bullet{
public:
	Texture tex1;
	Sprite sprite1;
	float acc=8;//speed of bullet 
	float x1=0,y1=0;//locations 
	float rotate_l=-1,rotate_r=1; 
	bool b1=true;
bullet() 
{
	
	bool b1=true;

	
	
}
void release(float x,float y, bool move_right, bool move_left,bool powerup,bool move_30r,bool move_30l,string png="img/laserBlue02.png")
{
	/*if (!powerup)
	{
		tex1.loadFromFile(png);
		sprite1.setTexture(tex1);
		sprite1.setScale(0.5,0.5);
		cout<<png<<endl;
		
	}*/
	//else 
	if (powerup)
	{
		tex1.loadFromFile("img/laserBlue02.png"); 
		sprite1.setTexture(tex1);
		sprite1.setScale(0.8,0.8);
		//cout<<"HELLO"<<endl;
	}

	//x=350;y=620; 
	x+=17; y-=22;
	x1=x; y1=y;
	sprite1.setPosition(x,y);
	//sprite.setRotation(300.f);
	
	if (move_right)
	{
		if (png=="img/laserBlue02.png")
		{
			
			tex1.loadFromFile("img/rotate/rotate45laserBlue02.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserGreen05.png")
		{
			tex1.loadFromFile("img/rotate/rotate45laserGreen05.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserGreen01.png")
		{	
			tex1.loadFromFile("img/rotate/rotatelaserGreen01.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserRed10.png")
		{
			tex1.loadFromFile("img/rotate/rotatelaserRed10.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
	}
	else if (move_left)
	{
		//sprite1.setRotation(-45);
		if (png=="img/laserBlue02.png")
		{
			
			tex1.loadFromFile("img/rotate/rotate-45laserBlue02.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserGreen05.png")
		{
			tex1.loadFromFile("img/rotate/rotate-45laserGreen05.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserGreen01.png")
		{	
			tex1.loadFromFile("img/rotate/rotatelaserGreen01.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserRed10.png")
		{
			tex1.loadFromFile("img/rotate/rotatelaserRed10.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
	}
	else if (move_30r)
	{
		/*if (png=="img/laserBlue02.png")
		{
			
			tex1.loadFromFile("img/rotate/rotate-45laserBlue02.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}*/
		 if (png=="img/PNG/Lasers/laserGreen05.png")
		{
			tex1.loadFromFile("img/rotate/rotate30laserGreen05.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserGreen01.png")
		{	
			tex1.loadFromFile("img/rotate/rotatelaser30Green01.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		 if (png=="img/PNG/Lasers/laserRed10.png")
		{
			tex1.loadFromFile("img/rotate/rotate30laserRed10.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
	}
	else if (move_30l)
	{
		/*if (png=="img/laserBlue02.png")
		{
			
			tex1.loadFromFile("img/rotate/rotate-45laserBlue02.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}*/
		 if (png=="img/PNG/Lasers/laserGreen05.png")
		{
			tex1.loadFromFile("img/rotate/rotate-30laserGreen05.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserGreen01.png")
		{	
			tex1.loadFromFile("img/rotate/rotate-30laserGreen01.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
		else if (png=="img/PNG/Lasers/laserRed10.png")
		{
			tex1.loadFromFile("img/rotate/rotate-30laserRed10.png");
			sprite1.setTexture(tex1);
			sprite1.setScale(0.5,0.5);
		}
	}
	else
	{
		tex1.loadFromFile(png);
		sprite1.setTexture(tex1);
		sprite1.setScale(0.5,0.5);
	}
}

void fire(bool move_right,bool move_left,bool move_30r,bool move_30l)
{
	
	
	//movement of the bullet 
	float delta_x=0,delta_y=-1;
	if (move_right)
		delta_x=1;
	else if (move_left)
		delta_x=-1;
	else if (move_30r)
		delta_x=0.5;
	else if (move_30l)
		delta_x=-0.5;
		
	delta_x*=acc;    		//b is from bullet class
	delta_y*=acc;
	/*if (movement)
	{
		b->sprite1.setPosition(sf::Vector2f(x,y));
		movement=false;
	}*/
	x1+=delta_x;
	y1+=delta_y;
	//cout<<x1<<" "<<y1<<endl;
	sprite1.move(delta_x, delta_y);
	
	//delete b;
	//b=new bullet("img/bullet.png");
	
}


};
