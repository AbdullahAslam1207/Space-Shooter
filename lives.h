#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>

using namespace std;
class live
{
public:
	Texture tex6;
	Sprite sprite6;
	float acc_live=4;//speed of danger sign 
	float x6=0,y6=0;//locations 
live() 
{
	
}
void release_live()
{
	tex6.loadFromFile("img/pill_blue.png");
	sprite6.setTexture(tex6);
	//x=350;y=620; 
	
	x6=450; y6=50;
	sprite6.setPosition(x6,y6);
	//sprite.setRotation(300.f);
	sprite6.setScale(1.5,1.5);
	
}

void fire_live()
{
	
	//cout<<"HELLO"<<endl;
	//movement of the bullet 
	float delta_x=0,delta_y=1;
	delta_x*=acc_live;    		//b is from bullet class
	delta_y*=acc_live;
	/*if (movement)
	{
		b->sprite6.setPosition(sf::Vector2f(x,y));
		movement=false;
	}*/
	x6+=delta_x;
	y6+=delta_y;
	//cout<<x6<<" "<<y6<<endl;
	sprite6.move(delta_x, delta_y);
	
	//delete b;
	//b=new bullet("img/bullet.png");
	
}
};
