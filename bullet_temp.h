#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
using namespace sf;
using namespace std;
class bullet{
public:
	Texture tex1;
	Sprite sprite1;
	float acc=1;//speed of bullet 
	float x1=0,y1=0;//locations 
	float rotate_l=-1,rotate_r=1; 
	bool b1=true;
bullet() 
{
	
	bool b1=true;

	
	
}
void release(float x,float y)
{
	tex1.loadFromFile("img/bullet.png");
	sprite1.setTexture(tex1);
	//x=350;y=620; 
	x+=17; y-=22;
	x1=x; y1=y;
	sprite1.setPosition(x,y);
	//sprite.setRotation(300.f);
	sprite1.setScale(0.05,0.05);
	
}

void fire()
{
	
	
	//movement of the bullet 
	float delta_x=0,delta_y=-1;
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
