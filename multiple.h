#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>

using namespace std;
class multiple
{
public:
	Texture tex8;
	Sprite sprite8;
	float acc_multiple=3;//speed of danger sign 
	float x8=0,y8=0;//locations 
multiple() 
{
	
}
void release_multiple()
{
	tex8.loadFromFile("img/things_gold.png");
	sprite8.setTexture(tex8);
	//x=350;y=620; 
	
	x8=550; y8=50;
	sprite8.setPosition(x8,y8);
	//sprite.setRotation(300.f);
	sprite8.setScale(1.5,1.5);
	
}

void multiple_multiple()
{
	
	//cout<<"HELLO"<<endl;
	//movement of the bullet 
	float delta_x=0,delta_y=1;
	delta_x*=acc_multiple;    		//b is from bullet class
	delta_y*=acc_multiple;
	/*if (movement)
	{
		b->sprite8.setPosition(sf::Vector2f(x,y));
		movement=false;
	}*/
	x8+=delta_x;
	y8+=delta_y;
	//cout<<x8<<" "<<y8<<endl;
	sprite8.move(delta_x, delta_y);
	
	//delete b;
	//b=new bullet("img/bullet.png");
	
}
};
