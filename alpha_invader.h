#include<SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
using namespace std;
class alpha
{
public:
	float x2,y2;
	Texture tex2;
	Sprite sprite2;
	alpha()
	{
		this->x2=0;
		this->y2=0;
	}
void place_alpha(float x2,float y2)
{
	        tex2.loadFromFile("img/enemy_1.png");
		sprite2.setTexture(tex2);
		this->x2=x2;
		this->y2=y2;
		sprite2.setPosition(x2,y2);
		//sprite2.setRotation(300.f);
		sprite2.setScale(0.45,0.45);
}
};
