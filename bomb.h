#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>
using namespace std;
class Bomb
{
public:
	Texture tex3;
	Sprite sprite3;
	float acc_enemy=3;//speed of bullet of the enemy
	float x3,y3;//locations 
	
Bomb()
{	
	x3=0;
	y3=0;
}

void release_enemy(float x,float y)
{
	tex3.loadFromFile("img/enemy_laser.png"); 
	sprite3.setTexture(tex3);
	//x=350;y=620; 
	//x+=17; y-=22;
	x3=x; y3=y;
	sprite3.setPosition(x,y);
	//sprite.setRotation(300.f);
	sprite3.setScale(0.5,0.5);
	
}

void fire_enemy()
{
	
	
	//movement of the bullet 
	float delta_x=0,delta_y=1;
	delta_x*=acc_enemy;    		//b is from bullet class
	delta_y*=acc_enemy;
	/*if (movement)
	{
		b->sprite3.setPosition(sf::Vector2f(x,y));
		movement=false;
	}*/
	x3+=delta_x;
	y3+=delta_y;
	//cout<<x1<<" "<<y1<<endl;
	sprite3.move(delta_x, delta_y);
	
	//delete b;
	//b=new bullet("img/bullet.png");
	
}
};
