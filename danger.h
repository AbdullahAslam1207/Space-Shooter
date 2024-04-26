#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>

using namespace std;
class danger
{
public:
	Texture tex5;
	Sprite sprite5;
	float acc_danger=4;//speed of danger sign 
	float x4=0,y4=0;//locations 
danger() 
{
	
}
void release_danger()
{
	tex5.loadFromFile("img/numeralX.png");
	sprite5.setTexture(tex5);
	//x=350;y=620; 
	
	x4=350; y4=50;
	sprite5.setPosition(x4,y4);
	//sprite.setRotation(300.f);
	sprite5.setScale(1.5,1.5);
	
}

void fire_danger()
{
	
	//cout<<"HELLO"<<endl;
	//movement of the bullet 
	float delta_x=0,delta_y=1;
	delta_x*=acc_danger;    		//b is from bullet class
	delta_y*=acc_danger;
	/*if (movement)
	{
		b->sprite5.setPosition(sf::Vector2f(x,y));
		movement=false;
	}*/
	x4+=delta_x;
	y4+=delta_y;
	//cout<<x4<<" "<<y4<<endl;
	sprite5.move(delta_x, delta_y);
	
	//delete b;
	//b=new bullet("img/bullet.png");
	
}
};
