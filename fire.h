#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>

using namespace std;
class fire
{
public:
	Texture tex7;
	Sprite sprite7;
	float acc_fire=3;//speed of danger sign 
	float x7=0,y7=0;//locations 
fire() 
{
	
}
void release_fire()
{
	tex7.loadFromFile("img/bolt_gold.png");
	sprite7.setTexture(tex7);
	//x=350;y=620; 
	
	x7=150; y7=50;
	sprite7.setPosition(x7,y7);
	//sprite.setRotation(300.f);
	sprite7.setScale(1.5,1.5);
	
}

void fire_fire()
{
	
	//cout<<"HELLO"<<endl;
	//movement of the bullet 
	float delta_x=0,delta_y=1;
	delta_x*=acc_fire;    		//b is from bullet class
	delta_y*=acc_fire;
	/*if (movement)
	{
		b->sprite7.setPosition(sf::Vector2f(x,y));
		movement=false;
	}*/
	x7+=delta_x;
	y7+=delta_y;
	//cout<<x7<<" "<<y7<<endl;
	sprite7.move(delta_x, delta_y);
	
	//delete b;
	//b=new bullet("img/bullet.png");
	
}
};
