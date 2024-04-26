
#include <SFML/Graphics.hpp>
#include <time.h>
#include "player.h"
#include "enemy_copy.h"
#include<cmath>
#include<string.h>
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
Sprite background,pause; //Game background sprite
Texture bg_texture,pause_texture;
Font Calibri;//font declared
Player* p; //player 
bullet* b;
int size=200;// size of the array for the bullets class 
enemy* en; //pointer of the enemy class  //dont use e as e is in event 
int enemy_size=20;// size of the enemy array
Bomb** bomb;

// add other game attributes


Game()
{
p=new Player("img/player_ship.png");
en=new enemy[enemy_size];
b=new bullet[size];
bomb=new Bomb*[enemy_size];
for (int i=0;i<enemy_size;i++)
{
	bomb[i]=new Bomb[size];
}
//e=new enemy("img/enemy_1.png");
bg_texture.loadFromFile("img/background.jpg");
background.setTexture(bg_texture);
background.setScale(1, 1.5);
pause_texture.loadFromFile("img/pause.png");
pause.setTexture(pause_texture);
pause.setScale(1, 1.5);

Calibri.loadFromFile("img/Calibri.ttf");

}
void start_game()
{
    srand(time(0));
    RenderWindow window(VideoMode(980,780), title);
    Clock clock;
    float timer=0;  int a=0;//for displaying the bullets after an interval 
    float timer_enemy_danger=0; // for displaying the danger sign
    float timer_enemy_alpha=0;
    float timer_enemy_beta=0;
    float timer_enemy_gama=0; //used for enemy bombs
    int release=0;
    int release_enemy1=0; //for alpha bullets count 
    int release_enemy2=0; //for beta 
    int release_enemy3=0; //for gama
    int check=-1;
    int timer_check=0; //used to basically convert timer to int 
    int checker_enemy[enemy_size];//this array is created to check the collison 
    int checker_enemy_store=0;// used for the index of above array
    int checker_bullet[enemy_size];//this array is created to avoid checking of the same bullet after collision
    int checker_bullet_store=0;// used for the index of above array7
    int wave_checker=1;
    int level=1;
    int score=0; //for storing the value of score.
    bool danger_check=false;
  
    for (int i=0;i<enemy_size;i++)
    	checker_enemy[i]=-1;
    for (int i=0;i<enemy_size;i++)
    	checker_bullet[i]=-1;
    
    int a_limit=0;
    int b_limit=0;//it is used when displaying the enemies like after a certain limit display beta then gama invader 
    int a_b=0;
    int lives=3; //this represents the lives of spaceship
    int lives_copy=lives;
    string player_name="ABDULLAH";
    //cin>>player_name;
    bool hit_danger_check=false;
    bool hit_live_check=false;//used for checking the collision
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time;  
        timer_enemy_danger+=time; 
        timer_enemy_alpha+=time; 
        timer_enemy_beta+=time; 
        timer_enemy_gama+=time; 
 	Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
          
	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
            p->move("l");    // Player will move to left
	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");  //player will move to right
	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards
        if (Keyboard::isKeyPressed(Keyboard::W)) // If space  key is pressed
            p->rotate("a");  //player will move diagoanlly left
        if (Keyboard::isKeyPressed(Keyboard::S)) // If enter  key is pressed
            p->rotate("s");  //player will move diagoanlly right
        
        // below part is for pause menu
         if (Keyboard::isKeyPressed(Keyboard::P)) // If P  key is pressed
         {
         	RenderWindow window_pause(VideoMode(630, 500), "PAUSE");
         	while (window_pause.isOpen())
		{
			Event e2;
			while (window_pause.pollEvent(e2))
			{  
	   			if (e2.type == Event::Closed) // If cross/close is clicked/pressed
		        		window_pause.close(); //close the game                        	    
			}
				if (Keyboard::isKeyPressed(Keyboard::Num1))
				{
					window_pause.close();
					
				}
				if (Keyboard::isKeyPressed(Keyboard::Num2))
				{
					window_pause.close();
					window.close();
					
				}
			window_pause.clear(Color::Black);
			window_pause.draw(pause);
			window_pause.display();
		}
           }
           //for displaying the score on screen 
           		string scores=to_string(score);//to display on screen
			Text Score(scores,Calibri);
			Score.setCharacterSize(20);
			Score.setFillColor(Color::Red);
			Score.setPosition(830,250);
			Text text1;
			text1.setFont(Calibri);
			text1.setString("SCORE");
			text1.setCharacterSize(27);
			text1.setFillColor(Color::Red);
			text1.setPosition(830,200);
	// to display the time consumed 		
			string timing=to_string(timer);//to display on screen
			Text Score1(timing,Calibri);
			Score1.setCharacterSize(20);
			Score1.setFillColor(Color::Red);
			Score1.setPosition(830,350);
			Text text2;
			text2.setFont(Calibri);
			text2.setString("TIMER");
			text2.setCharacterSize(27);
			text2.setFillColor(Color::Red);
			text2.setPosition(830,300);
	// to display the name of the player 			
       		Text text3;
			text3.setFont(Calibri);
			text3.setString(player_name);
			text3.setCharacterSize(27);
			text3.setFillColor(Color::Red);
			text3.setPosition(830,150);
       
      //  p->lives_ship(1,40,650);
       // cout<<p->position_x()<<p->position_y()<<endl;
	////////////////////////////////////////////////
	/////  Call your functions here            ////
	//////////////////////////////////////////////

	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
	window.draw(p->sprite);   // setting player on screen
	window.draw(Score);
	window.draw(text1);
	window.draw(Score1);
	window.draw(text2);
	window.draw(text3);
	livecount l[lives];
       int x=40;
       for (int i=0;i<lives;i++)
       {
       	l[i].lives_ship(x,650);
       	x+=30;
       }
        a++;
       // cout<<a<<endl;
        if (a%20==0)
        {
        	
         	//cout<<p->position_x()<<p->position_y()<<endl;
        	b[release].release(p->position_x(),p->position_y());
        	//window.draw(b[release].sprite1);   //setting the bullet 
        	release++;
        	if (release==size)
        		window.close();
        		
        	
        	
        }
	for (int i=0;i<lives;i++)
		window.draw(l[i].lives);
	//this is used  for the danger sign 
	 if (timer_enemy_danger>10)
        {
        	p->release_danger();
        	p->release_live();
        	timer_enemy_danger=0;
        	danger_check=true;
        	
        }
         //bool simple_check=false;
	if (danger_check)
        {
        	
       	 p->fire_danger();
       	 p->fire_live();
       	 if (!hit_live_check)
       		 window.draw(p->sprite6);
       	 if (!hit_danger_check)
       		 window.draw(p->sprite5);
       	 if (((p->y4>=p->y-20)&&(p->y4<=p->y+20))&&((p->x4>=p->x-10)&&(p->x4<=p->x+30)))
       	 {
       	 	
       	 	lives_copy--;
       	 	lives=lives_copy;
       	 	p->y4=-200;
       	 	p->x4=-100;
       	 	p->x=340;p->y=650; 
       	 	p->sprite.setPosition(p->x,p->y);
       	 	hit_danger_check=true;
       	 	//p->explosion();
       	 	//window.draw(p->s);
       	 }
       	 if (((p->y6>=p->y-20)&&(p->y6<=p->y+20))&&((p->x6>=p->x-10)&&(p->x6<=p->x+30)))
       	 {
       	 	lives_copy=lives+1;
       	 	lives=lives_copy;
       	 	p->y6=-200;
       	 	p->x6=-100;
       	 	hit_live_check=true;
       	 }
       	 
       }
       if (p->y4>=750) //y4 is multi level inheritance of danger class ...x4 y4 are  of dannger 
       {
       	danger_check=false;
       	//if (!simple_check)
       	//	score+=5;
       	//simple_check=true;
       	if (!hit_danger_check)
       		score+=5;
       	hit_danger_check=false;
       	p->x4=-100;
       	p->y4=-200;
       }
       
      	
       // this loop is used to display the bullets as well as check if the bullet has collided with the enemy or not 
	bool true_checker2=false;
	for (int i=0;i<release;i++)
        {
        	for (int j=0;j<enemy_size;j++)
        	{
        		if (i!=checker_bullet[j])
        		{
        			true_checker2=true;
        			
			}
			else 
			{
				true_checker2=false;
				break;
			}
		}
		if (true_checker2)
		{
			b[i].fire();  
        		window.draw(b[i].sprite1); 
        	}
        	true_checker2=false;
		
	        	
        }
        // the below loop is used for displaying the enemy sprites as well as checking if that enemy has been killed or not 
        float enemy_position_x=0;
        float enemy_position_y=0;
        if (level==1)
        { 
        
      	if (wave_checker==1)
      	{
		 enemy_position_x=en[0].x2;
		 enemy_position_y=en[0].y2;
		a_limit=7;
		b_limit=14;
        }
        else if (wave_checker==2)
        {
        	enemy_position_x=350;
        	enemy_position_y=50;
        	a_limit=3;
        	b_limit=6;
        	
        }
        else if (wave_checker==3)
        {
		enemy_position_x=350;
        	enemy_position_y=150;
        	a_limit=3;
        	b_limit=6;
        	wave_checker=4;
        }
        bool true_checker=false;
	for (int i=0;i<enemy_size;i++)
	{
		if (wave_checker==1)
		{
			en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			enemy_position_x+=80;
			if (i==(enemy_size/2 -1))
			{
				enemy_position_x=en[0].x2;
				enemy_position_y+=100;
			}
		}
		else if (wave_checker==2)
		{
		
			if (i==0)
			{
				enemy_position_x=350;
        			enemy_position_y=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,3,6);
				enemy_position_x-=100;
				enemy_position_y+=100;
			}
			else if (i==1||i==2)
			{
				en[i].placement(enemy_position_x,enemy_position_y,i,3,6);
				enemy_position_x+=165;
				if (i==2)
				{
					enemy_position_x-=400;
					enemy_position_y+=100;
				}
			}
			else if (i==3||i==4)
			{
				en[i].placement(enemy_position_x,enemy_position_y,i,3,6);
				enemy_position_x+=275;
				if (i==4)
				{
					enemy_position_x-=600;
					enemy_position_y+=100;
				}
			}
			else 
			{
				en[i].placement(enemy_position_x,enemy_position_y,i,3,6);
				enemy_position_x+=100;
				//enemy_position_y+=100;
			}
		}
		else 
		{
			if (i==0)
				enemy_position_x=350;
			if (i==0||i==1||i==7||i==8)
			{
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				enemy_position_y+=100;
				if (i==1)
					enemy_position_x=100;
			}
			else
			{
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				enemy_position_x+=100;
				if (i==6)
				{
					enemy_position_x=350;
					enemy_position_y+=100;
				}
			}
		}
		
		
		for (int j=0;j<enemy_size;j++)
		{
			if (i!=checker_enemy[j])
			{
				true_checker=true;
			}
			else
			{
				true_checker=false;
				//en[j].x2=0; en[j].y2=0;
				break;
			}
		}
		if (true_checker)
		{
		
			if (i<a_limit)
			{
				
				window.draw(en[i].a.sprite2);
				
			}
			else if (i<b_limit)
			{
				
				window.draw(en[i].b.sprite2);
				
			}
			else
			{
				
				window.draw(en[i].g.sprite2);
				
			}
		}
	}
	//the below loop is used for displaying the enemy bullets 
	
	if (timer_enemy_alpha>2)
	{
		for (int i=0;i<a_limit;i++)
		{
			bomb[i][release_enemy1].release_enemy(en[i].x2,en[i].y2);
			if (i==1)
				break;
		}
		timer_enemy_alpha=0;
		release_enemy1++;
	}
	if (timer_enemy_beta>3)
	{
		for (int i=a_limit;i<b_limit;i++)
		{
			bomb[i][release_enemy2].release_enemy(en[i].x2,en[i].y2);
			if (i==a_limit+1)
				break;
		}
		timer_enemy_beta=0;
		release_enemy2++;
	}
	if (timer_enemy_gama>5)
	{
		for (int i=b_limit;i<enemy_size;i++)
		{
			bomb[i][release_enemy3].release_enemy(en[i].x2,en[i].y2);
			if (i==b_limit+1)
				break;
		}
		timer_enemy_gama=0;
		release_enemy3++;
	}
	bool true_checker3=false;
	for (int i=0;i<enemy_size;i++)
	{
		for (int j=0;j<enemy_size;j++)
		{
			if (i!=checker_enemy[j])
			{
				true_checker3=true;
			}
			else
			{
				true_checker3=false;
				//en[j].x2=0; en[j].y2=0;
				break;
			}
		}
		
		if (true_checker3)
		{
			if (release_enemy1!=0&&i<a_limit)
			{
				for (int j=0;j<release_enemy1;j++)
				{
					//cout<<"HELLO1"<<endl;
					
					bomb[i][j].fire_enemy();
					window.draw(bomb[i][j].sprite3);
				}
			}
			if (release_enemy2!=0&&i>=a_limit&&i<b_limit)
			{
				for (int j=0;j<release_enemy2;j++)
				{
					//cout<<"HELLO1"<<endl;
					
					bomb[i][j].fire_enemy();
					window.draw(bomb[i][j].sprite3);
				}
			}
			if (release_enemy3!=0&&i>=b_limit)
			{
				for (int j=0;j<release_enemy3;j++)
				{
					//cout<<"HELLO1"<<endl;
					
					bomb[i][j].fire_enemy();
					window.draw(bomb[i][j].sprite3);
				}
			}
		}
		true_checker3=false;
		
	}
	//cout<<bomb[14][0].y3<<endl;
	
	//the below loop is used to check whether any of the enemy laser has collided with the spaceship or not 
	//this loop needs amendments 
	bool hit_check=false;
	for (int i=0;i<a_limit;i++)
	{	
		for (int j=0;j<release_enemy1;j++)
		{
			if (((bomb[i][j].y3>=p->y-20)&&(bomb[i][j].y3<=p->y+20))&&((bomb[i][j].x3>=p->x-10)&&(bomb[i][j].x3<=p->x+30)))
			{
				cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				lives_copy--;
				lives=lives_copy;
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				p->x=340;p->y=650; 
       	 		p->sprite.setPosition(p->x,p->y);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}
	for (int i=a_limit;i<b_limit;i++)
	{	
		for (int j=0;j<release_enemy2;j++)
		{
			if (((bomb[i][j].y3>=p->y-20)&&(bomb[i][j].y3<=p->y+20))&&((bomb[i][j].x3>=p->x-10)&&(bomb[i][j].x3<=p->x+30)))
			{
				cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				lives_copy--;
				lives=lives_copy;
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				p->x=340;p->y=650; 
       	 		p->sprite.setPosition(p->x,p->y);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}
	for (int i=b_limit;i<enemy_size;i++)
	{	
		for (int j=0;j<release_enemy3;j++)
		{
			if (((bomb[i][j].y3>=p->y-20)&&(bomb[i][j].y3<=p->y+20))&&((bomb[i][j].x3>=p->x-10)&&(bomb[i][j].x3<=p->x+30)))
			{
				cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				lives_copy--;
				lives=lives_copy;
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				p->x=340;p->y=650; 
       	 		p->sprite.setPosition(p->x,p->y);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}
	
	//the below loop is used for the collison check! based on checker_enemy and checker_bullet
	bool true_checker1=false;
	
	for (int i=0;i<release;i++)
	{
		for (int j=0;j<enemy_size;j++)
		{
			for (int k=0;k<enemy_size;k++)
			{
				if (j!=checker_enemy[k])
				{
					true_checker1=true;
				}
				else 
				{
					true_checker1=false;
					break;
				}
			}
				if (true_checker1)
				{	
				if ((b[i].x1>=(en[j].x2-10)&&b[i].x1<=(en[j].x2+40))&&(b[i].y1>=(en[j].y2-30)&&b[i].y1<=(en[j].y2+30))) 
				{
					
						checker_enemy[checker_enemy_store]=j;
						checker_enemy_store++;
						//cout<<checker_enemy_store<<endl;
						checker_bullet[checker_bullet_store]=i;
						//cout<<checker_bullet[checker_bullet_store]<<endl;
						checker_bullet_store++;
						//cout<<i<<endl;
						if (j<a_limit)
							score=(score+(10*level));
						else if (j<b_limit)
							score=(score+(20*level));
						else 
							score=(score+(30*level)); 
					
					
				}
				}
			
		}
		
		true_checker1=false;
	} 
	}//this is the end of the level==1 condition
	
	if (level==2)
	{
		//cout<<1<<endl;
		      	if (wave_checker==1)
      	{
		 enemy_position_x=350;
		 enemy_position_y=40;
		a_limit=7;
		b_limit=14;
        }
        else if (wave_checker==2)
        {
        	enemy_position_x=350;
        	enemy_position_y=40;
        	a_limit=7;
        	b_limit=14;
        	
        }
        else if (wave_checker==3)
        {
		enemy_position_x=350;
        	enemy_position_y=150;
        	a_limit=5;
        	b_limit=10;
        	wave_checker=4;
        }
        bool true_checker=false;
	for (int i=0;i<enemy_size;i++)
	{
		//cout<<2<<endl;
		if (wave_checker==1)
		{
			
			
		    float angleStep = 360.0f / 20; // calculate the angle between each position in the circle

		    // loop through each position in the circle and calculate its x and y coordinates based on the angle
		    
			float angle = i * angleStep;
			float x = 300 + 200 * cos(angle * 3.14159f / 180.0f);
			float y = 300 + 200 * sin(angle * 3.14159f / 180.0f);
			
			en[i].placement(x,y,i,a_limit,b_limit);
		}
		    
		else if (wave_checker==2)
		{
		
			if (i<5)
			{
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				if (i<4)
				{
					enemy_position_x-=35;
					enemy_position_y+=50;
				}
			}
			else if (i>=5&&i<10)
			{
				enemy_position_x+=35;
				enemy_position_y+=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			}
			else if (i>=10&&i<15)
			{
				enemy_position_x+=35;
				enemy_position_y-=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			}
			else 
			{
				enemy_position_x-=35;
				enemy_position_y-=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			}
		}
		else 
		{
			if (i==0)
			{
				enemy_position_x=350;
				enemy_position_y=200;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			}
			else if (i<3)
			{
				enemy_position_x-=50;
				enemy_position_y-=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			}
			else if (i<5)
			{
				enemy_position_x-=50;
				enemy_position_y+=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			}
			else if (i<10)
			{
				enemy_position_x+=50;
				enemy_position_y+=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			}
			else if (i<15)
			{
				enemy_position_x+=50;
				enemy_position_y-=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				
			}
			else if (i<17)
			{
				enemy_position_x-=50;
				enemy_position_y-=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				
			}
			else if (i<20)
			{
				enemy_position_x-=50;
				enemy_position_y+=50;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				
			}
			
				
				
				
		}
		
		
		for (int j=0;j<enemy_size;j++)
		{
			if (i!=checker_enemy[j])
			{
				true_checker=true;
			}
			else
			{
				true_checker=false;
				//en[j].x2=0; en[j].y2=0;
				break;
			}
		}
		if (true_checker)
		{
		
			if (i<a_limit)
			{
				
				window.draw(en[i].a.sprite2);
				
			}
			else if (i<b_limit)
			{
				
				window.draw(en[i].b.sprite2);
				
			}
			else
			{
				
				window.draw(en[i].g.sprite2);
				
			}
		}
	}
	//the below loop is used for displaying the enemy bullets 
	//cout<<3<<endl;
	// a_b++;
	if (timer_enemy_alpha>2)
	{
		//cout<<331<<endl;
		for (int i=0;i<a_limit;i++)
		{
			bomb[i][release_enemy1].release_enemy(en[i].x2,en[i].y2);
			if (i==1)
				break;
			//cout<<i<<endl;
		}
		timer_enemy_alpha=0;
		release_enemy1++;
	}
	//cout<<31<<endl;
	if (timer_enemy_beta>3)
	{
		//cout<<31567<<endl;
		for (int i=a_limit;i<b_limit;i++)
		{
		
			//cout<<release_enemy2<<i<<endl;
			bomb[i][release_enemy2].release_enemy(en[i].x2,en[i].y2);
			if (i==a_limit+1)
				break;
			//cout<<"hellooooo"<<endl;
			//cout<<i<<endl;
		}
		//cout<<31<<endl;
		timer_enemy_beta=0;
		release_enemy2++;
	}
	//cout<<32<<endl;
	if (timer_enemy_gama>5)
	{
		for (int i=b_limit;i<enemy_size;i++)
		{
			bomb[i][release_enemy3].release_enemy(en[i].x2,en[i].y2);
			if (i==b_limit+1)
				break;
				
			//cout<<i<<endl;
		}
		timer_enemy_gama=0;
		release_enemy3++;
	}
	//cout<<33<<endl;
	bool true_checker3=false;
	for (int i=0;i<enemy_size;i++)
	{
		for (int j=0;j<enemy_size;j++)
		{
			if (i!=checker_enemy[j])
			{
				true_checker3=true;
			}
			else
			{
				true_checker3=false;
				//en[j].x2=0; en[j].y2=0;
				break;
			}
		}
		
		
		if (true_checker3)
		{
			if (release_enemy1!=0&&i<a_limit)
			{
				for (int j=0;j<release_enemy1;j++)
				{
					//cout<<"HELLO1"<<endl;
					
					bomb[i][j].fire_enemy();
					window.draw(bomb[i][j].sprite3);
				}
			}
			if (release_enemy2!=0&&i>=a_limit&&i<b_limit)
			{
				
				//cout<<"HEY"<<i<<endl;
				for (int j=0;j<release_enemy2;j++)
				{
					//cout<<"HELLO1"<<endl;
					
					bomb[i][j].fire_enemy();
					window.draw(bomb[i][j].sprite3);
				}
				//cout<<"HEY1"<<i<<endl;
			}
			if (release_enemy3!=0&&i>=b_limit)
			{
				for (int j=0;j<release_enemy3;j++)
				{
					//cout<<"HELLO1"<<endl;
					
					bomb[i][j].fire_enemy();
					window.draw(bomb[i][j].sprite3);
				}
			}
		}
		cout<<i<<endl;
		true_checker3=false;
		
	}
	//cout<<34<<endl;
	//cout<<bomb[14][0].y3<<endl;
	
	//the below loop is used to check whether any of the enemy laser has collided with the spaceship or not 
	//this loop needs amendments 
	bool hit_check=false;
	for (int i=0;i<a_limit;i++)
	{	
		for (int j=0;j<release_enemy1;j++)
		{
			if (((bomb[i][j].y3>=p->y-20)&&(bomb[i][j].y3<=p->y+20))&&((bomb[i][j].x3>=p->x-10)&&(bomb[i][j].x3<=p->x+30)))
			{
				cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				lives_copy--;
				lives=lives_copy;
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				p->x=340;p->y=650; 
       	 	p->sprite.setPosition(p->x,p->y);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}
	for (int i=a_limit;i<b_limit;i++)
	{	
		for (int j=0;j<release_enemy2;j++)
		{
			if (((bomb[i][j].y3>=p->y-20)&&(bomb[i][j].y3<=p->y+20))&&((bomb[i][j].x3>=p->x-10)&&(bomb[i][j].x3<=p->x+30)))
			{
				cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				lives_copy--;
				lives=lives_copy;
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				p->x=340;p->y=650; 
       	 	p->sprite.setPosition(p->x,p->y);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}
	for (int i=b_limit;i<enemy_size;i++)
	{	
		for (int j=0;j<release_enemy3;j++)
		{
			if (((bomb[i][j].y3>=p->y-20)&&(bomb[i][j].y3<=p->y+20))&&((bomb[i][j].x3>=p->x-10)&&(bomb[i][j].x3<=p->x+30)))
			{
				cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				lives_copy--;
				lives=lives_copy;
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				p->x=340;p->y=650; 
       	 	p->sprite.setPosition(p->x,p->y);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}	
	//the below loop is used for the collison check! based on checker_enemy and checker_bullet
	bool true_checker1=false;
	cout<<41<<endl;
	for (int i=0;i<release;i++)
	{
		for (int j=0;j<enemy_size;j++)
		{
			for (int k=0;k<enemy_size;k++)
			{
				if (j!=checker_enemy[k])
				{
					true_checker1=true;
				}
				else 
				{
					true_checker1=false;
					break;
				}
			}
				if (true_checker1)
				{	
				if ((b[i].x1>=(en[j].x2-10)&&b[i].x1<=(en[j].x2+40))&&(b[i].y1>=(en[j].y2-30)&&b[i].y1<=(en[j].y2+30))) 
				{
					
						checker_enemy[checker_enemy_store]=j;
						checker_enemy_store++;
						//cout<<checker_enemy_store<<endl;
						checker_bullet[checker_bullet_store]=i;
						//cout<<checker_bullet[checker_bullet_store]<<endl;
						checker_bullet_store++;
						//cout<<i<<endl;
						if (j<a_limit)
							score=(score+(10*level));
						else if (j<b_limit)
							score=(score+(20*level));
						else 
							score=(score+(30*level)); 
					
					
				}
				}
			
		}
		
		true_checker1=false;
	} 
	//cout<<42<<endl;
	}//end of level 2  condition
	
	

	
	
	
	
	
	
	window.display();  //Displying all the sprites
	
	if (checker_enemy_store==(enemy_size))
	{
	//first time when the wave gets cleared then wave checker is true then the very moment wave checker becomes false and 
	//the next time it moves to else this check is made false in the enemy placement condition
		
		if (wave_checker==1)
		{
			//cout<<44<<endl;
			wave_checker=2;
			  for (int i=0;i<enemy_size;i++)
	    			checker_enemy[i]=-1;
	    		  for (int i=0;i<enemy_size;i++)
	    			checker_bullet[i]=-1;
	    		cout<<45<<endl;
	    		delete[]b;
	    		
	    		b=new bullet[size];
	    		//cout<<48<<endl;
	    		//for (int i=0;i<enemy_size;i++)
			//	delete[]bomb[i];
			delete[]bomb;
			delete[]en;
			if (level==1)
				enemy_size=10;
			else if (level==2)
				enemy_size=20;
			else 
				enemy_size=20;
			en=new enemy[enemy_size];
			//cout<<47<<endl;
			bomb=new Bomb*[enemy_size];
			for (int i=0;i<enemy_size;i++)
			{
				bomb[i]=new Bomb[size];
			}
			//cout<<46<<endl;
			release=0;
			release_enemy1=0;
			release_enemy2=0;
			release_enemy3=0;
			a=0;
			checker_enemy_store=0;
			checker_bullet_store=0;
			
			//cout<<43<<endl;
		}
		else if (wave_checker==2)
		{
			wave_checker=3;
			for (int i=0;i<enemy_size;i++)
	    			checker_enemy[i]=-1;
	    		  for (int i=0;i<enemy_size;i++)
	    			checker_bullet[i]=-1;
	    		
			
	    		delete[]b;
	    		b=new bullet[size];
	    		for (int i=0;i<enemy_size;i++)
				delete[]bomb[i];
			delete[]en;
			if (level==1)
				enemy_size=10;
			else if (level==2)
				enemy_size=20;
			else 
				enemy_size=20;
			en=new enemy[enemy_size];
			delete[]bomb;
			bomb=new Bomb*[enemy_size];
			for (int i=0;i<enemy_size;i++)
			{
				bomb[i]=new Bomb[size];
			}
			release=0;
			release_enemy1=0;
			release_enemy2=0;
			release_enemy3=0;
			a=0;
			checker_enemy_store=0;
			checker_bullet_store=0;
			
		}
    		if (wave_checker==4)
    		{
    			if (level==2)
    			{
    				window.close();
    				//cout<<"SCORE: "<<score<<endl;
    				Sprite level2;
	    			Texture level2c;
	    			level2c.loadFromFile("img/level2.png");
				level2.setTexture(level2c);
				level2.setScale(1, 1);
	    			RenderWindow window_complete_level2(VideoMode(200,300), "LEVEL-2 COMPLETED");
	    			while (window_complete_level2.isOpen())
				{
					
				 	Event level2_complete;
					while (window.pollEvent(level2_complete))
					{  
					    if (level2_complete.type == Event::Closed) // If cross/close is clicked/pressed
						window_complete_level2.close(); //close the game                        	    
					}
					if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
		   				window_complete_level2.close();
					window_complete_level2.clear(Color::Black); //clears the screen
					window_complete_level2.draw(level2);  // setting background
					window_complete_level2.display();
					
					
				}
    			}
    			//previous setup because after it will come completing level 2 3 waves it goes there 
    			level=2;
    			wave_checker=1;
    			
    			
    			Sprite level1;
    			Texture level1c;
    			level1c.loadFromFile("img/level1.png");
			level1.setTexture(level1c);
			level1.setScale(2, 1.5);
    			RenderWindow window_complete_level1(VideoMode(300,300), "LEVEL-1 COMPLETED");
    			while (window_complete_level1.isOpen())
		        {
				
			 	Event level1_complete;
				while (window.pollEvent(level1_complete))
				{  
				    if (level1_complete.type == Event::Closed) // If cross/close is clicked/pressed
					window_complete_level1.close(); //close the game                        	    
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
           				window_complete_level1.close();
				window_complete_level1.clear(Color::Black); //clears the screen
				window_complete_level1.draw(level1);  // setting background
				window_complete_level1.display();
				
				
			}
			
			for (int i=0;i<enemy_size;i++)
	    			checker_enemy[i]=-1;
	    		  for (int i=0;i<enemy_size;i++)
	    			checker_bullet[i]=-1;
	    		delete[]b;
	    		b=new bullet[size];
	    		for (int i=0;i<enemy_size;i++)
				delete[]bomb[i];
			delete[]bomb;
			enemy_size=20;
			bomb=new Bomb*[enemy_size];
			for (int i=0;i<enemy_size;i++)
			{
				bomb[i]=new Bomb[size];
			}
			release=0;
			release_enemy1=0;
			release_enemy2=0;
			release_enemy3=0;
			//timer_enemy_alpha=0;
			//timer_enemy_beta=0;
			//timer_enemy_gama=0;
			a=0;
			checker_enemy_store=0;
			checker_bullet_store=0;
			delete[]en;
			//if (level==1)
			//	enemy_size=10;
			//else if (level==2)
				
			//else 
			//	enemy_size=20;
			en=new enemy[enemy_size];
    			
    			cout<<"CONGRATULATIONS ON COMPLETING LEVEL 1 OF THE GAME"<<endl;
    			cout<<"CONGRATULATIONS ON COMPLETING LEVEL 2 OF THE GAME"<<endl;
    			cout<<"SCORE: "<<score<<endl;
    			
    			
    		}
    		cout<<"HELLO"<<endl;
		
		
	}
	
	
	if (lives==0)
	{
		cout<<"YOU RAN OUT OF LIVES"<<endl;
		window.close();
		Texture over_texture;
		Sprite over;
		over_texture.loadFromFile("img/gameover.png");
		over.setTexture(over_texture);
		over.setScale(1, 1.5);
		RenderWindow window_over(VideoMode(630, 500), "GAMEOVER");
		while (window_over.isOpen())
		{
			Event e3;
			while (window_over.pollEvent(e3))
			{  
	   			if (e3.type == Event::Closed) // If cross/close is clicked/pressed
			      		window_over.close(); //close the game                        	    
			}
				
			window_over.clear(Color::Black);
			window_over.draw(over);
			window_over.display();
		}
	}
	
    }
    
	//for (int i=0;i<enemy_size;i++)
	//	cout<<checker_enemy[i]<<endl;
	

}
/*~Game()
{
	for (int i=0;i<enemy_size;i++)
		delete[]bomb[i];
	delete[]bomb;
	delete[]en;
	delete[]b;
	delete[]p;
}
*/

};

