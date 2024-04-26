#include<SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include "alpha_invader.h"
#include "beta_invader.h"
#include "gama_invader.h"
#include "monster.h"
#include "bomb.h"
using namespace std;
class enemy
{
public:
	Texture tex2;
	Sprite sprite2;
	alpha a;
	beta b;
	gama g;
	float acc;
	float x2,y2;//locationoftheenemy
	
	enemy()
	{
		x2=10; 
		y2=250;
	}

void placement(float x2,float y2,int i,int a_,int b_)
{
	this->x2=x2;
	this->y2=y2;
	
	//cout<<this->x2<<" "<<this->y2<<endl;
	if (i<a_)
		a.place_alpha(x2,y2);
	else if(i<b_)
		b.place_beta(x2,y2);
	else
		g.place_gama(x2,y2);
	
		
}
virtual void display(){};

};
	
	
class monster: public enemy
{
public:
	bool move_right=false;
	Sprite sprite;
	Texture tex;
	float x_beam=0;
	float y_beam=0;
	monster(){};
	virtual void display()
	{
		tex2.loadFromFile("img/monster1.png");
		sprite2.setTexture(tex2);
		this->x2=50;
		this->y2=50;
		this->acc=3;
		sprite2.setPosition(x2,y2);
		//sprite2.setRotation(300.f);
		sprite2.setScale(0.45,0.45);
	}
	void movement_monster()
	{
		 
		float delta_x,delta_y=0;
		if (x2<20)
		{
			move_right=true;
			
		}
		//else if (x2>700)
		//{
		//	move_right=false;
		//	delta_x-=1;
		//}
		if (!move_right)
		{
			delta_x=-1;
			delta_x*=acc;    		
			delta_y*=acc;
			
			x2+=delta_x;
			y2+=delta_y;
			
			sprite2.move(delta_x, delta_y);
		}
		else 
		{
			delta_x+=1;
			delta_x*=acc;    		
			delta_y*=acc;
			
			x2+=delta_x;
			y2+=delta_y;
			
			sprite2.move(delta_x, delta_y);
			if (x2>500)
				move_right=false;
		}
		
		
		
	}
	bool fire_monster()
	{
		if (move_right)
		{
			tex.loadFromFile("img/fire08.png");
			sprite.setTexture(tex);
			//x=350;y=620; 
			
			
			x_beam=x2+135;
			y_beam=y2+270;
			sprite.setPosition(x_beam,y_beam);
			//sprite.setRotation(300.f);
			sprite.setScale(1,10);
			return 1 ;
			
		}
		return 0;
	}
};




class dragon: public enemy
{
public:
	
	Sprite sprite;
	Texture tex;
	float x_beam=0;
	float y_beam=0;
	//monster(){ };
	virtual void display(float rotate=0,float x_pos=250, float y_pos=50,string png="img/dragon2.png")
	{
		tex2.loadFromFile(png);
		sprite2.setTexture(tex2);
		this->x2=x_pos-10;
		this->y2=y_pos;
		this->acc=0.1;
		sprite2.setPosition(x2,y2);
		//sprite2.setRotation(rotate);
		//sprite2.setRotation(300.f);
		sprite2.setScale(0.5,0.5);
	}
	void movement_dragon(float x)
	{
		
		 
		float delta_x=x,delta_y=0;
		
		
			
			delta_x*=acc;    		
			delta_y*=acc;
			
			x2+=delta_x;
			y2+=delta_y;
			
			sprite2.move(delta_x, delta_y);
		
		
		
		
	}
	void fire_dragon(float x,float y,float rotate=0,string png="img/laserRed03.png")
	{
		
			tex.loadFromFile(png);
			sprite.setTexture(tex);
			//x=350;y=620; 
			
			
			x_beam=x+50;
			y_beam=y;
			sprite.setPosition(x_beam,y_beam);
			//sprite.setRotation(300.f);
			sprite.setScale(1,10);
			sprite.setRotation(rotate);
	}
	void movement_beam(float x)
	{
		
		 
		float delta_x=x,delta_y=0;
		
		
			
			delta_x*=acc;    		
			delta_y*=acc;
			
			x_beam+=delta_x;
			y_beam+=delta_y;
			
			sprite.move(delta_x, delta_y);
		
		
		
		
	}
};
