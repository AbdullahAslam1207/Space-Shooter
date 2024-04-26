
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include<fstream>
#include<sstream>
#include "player.h"
#include "enemy.h"
#include<cmath>
#include<cstdlib>
#include<string.h>
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
string bullet_choose;
Sprite background,pause; //Game background sprite
Texture bg_texture,pause_texture;
Font Calibri;//font declared
Player* p; //player 
bullet* b;
int size=300;// size of the array for the bullets class 
enemy* en; //pointer of the enemy class  //dont use e as e is in event 
int enemy_size=22;// size of the enemy array
Bomb** bomb;
bullet** b2;//b2 is the double pointer 
dragon* d;//for dragon
dragon* d2;
dragon* d3;
monster* m; //used for monster
// add other game attributes


Game()
{
// please choose a space ship for playing 
/*cout<<"\t\tSPACE SHIP TYPES "<<endl;
int choice=0;
cout<<"PLEASE ENTER A CHOICE FROM 1 TO 3"; cin>>choice;
if (choice==1)*/
	

en=new enemy[enemy_size];
b=new bullet[size];
bomb=new Bomb*[enemy_size];
for (int i=0;i<enemy_size;i++)
{
	bomb[i]=new Bomb[size];
}
b2=new bullet*[5];
for (int i=0;i<5;i++)
{
	b2[i]=new bullet[size];
}
/*d=new dragon;
d2=new dragon;
d3=new dragon;
m=new monster;*/
//e=new enemy("img/enemy_1.png");

pause_texture.loadFromFile("img/pause.png");
pause.setTexture(pause_texture);
pause.setScale(1, 1.5);

Calibri.loadFromFile("img/Calibri.ttf");

}
void choose_ship()
{
	//before game starts this loop works so that player can get a option to choose a space ship of his/her choice 
    		Texture start;
		Sprite start1;
		start.loadFromFile("img/ships.png");
		start1.setTexture(start);
		start1.setScale(1, 1.5);
		RenderWindow window_ship(VideoMode(200, 500), "CHOOSE SPACESHIP");
		while (window_ship.isOpen())
		{
			Event e4;
			while (window_ship.pollEvent(e4))
			{  
	   			if (e4.type == Event::Closed) // If cross/close is clicked/pressed
			      		window_ship.close(); //close the game                        	    
			}
			if (Keyboard::isKeyPressed(Keyboard::Num1)) 
			{
           			 p=new Player;
           			 p->place_ship("img/player_ship.png");
           			 window_ship.close();  
           		}
           		if (Keyboard::isKeyPressed(Keyboard::Num2)) 
           		{
           			 p=new Player;
           			 p->place_ship("img/PNG/playerShip2_orange.png");
           			 window_ship.close();  
           		}
           		if (Keyboard::isKeyPressed(Keyboard::Num3)) 
           		{
           			 p=new Player; 
           			 p->place_ship("img/PNG/playerShip1_blue.png");
           			 window_ship.close(); 
           		}
           	
				
			window_ship.clear(Color::Black);
			window_ship.draw(start1);
			window_ship.display();
		}
	// end 
}
void choose_bullet()
{
	//before game starts this loop works so that player can get a option to choose a space ship of his/her choice 
    		Texture start;
		Sprite start1;
		start.loadFromFile("img/bullet_choose.png");
		start1.setTexture(start);
		start1.setScale(1, 1.5);
		RenderWindow window_ship(VideoMode(200, 500), "CHOOSE SPACESHIP");
		while (window_ship.isOpen())
		{
			Event e4;
			while (window_ship.pollEvent(e4))
			{  
	   			if (e4.type == Event::Closed) // If cross/close is clicked/pressed
			      		window_ship.close(); //close the game                        	    
			}
			if (Keyboard::isKeyPressed(Keyboard::Num9)) 
			{
           			 bullet_choose="img/PNG/Lasers/laserGreen05.png";
           			 //return 1;
           			 window_ship.close();  
           		}
           		if (Keyboard::isKeyPressed(Keyboard::Num8)) 
           		{
           			 bullet_choose="img/PNG/Lasers/laserGreen01.png";
           			 window_ship.close();  
           		}
           		if (Keyboard::isKeyPressed(Keyboard::Num7)) 
           		{
           			 bullet_choose="img/PNG/Lasers/laserRed10.png" ;
           			 window_ship.close(); 
           		}
           	
				
			window_ship.clear(Color::Black);
			window_ship.draw(start1);
			window_ship.display();
		}
		//return 0;
	// end 
}
void start_game()
{
    
    choose_bullet();
    choose_ship();
    srand(time(0));
    RenderWindow window(VideoMode(980,780), title);
    Clock clock;
    float timer=0;  int a=0;//for displaying the bullets after an interval 
    float timer_enemy_danger=0; // for displaying the danger sign
    float timer_bullet_fire=0;// for displaying the fire power up
    float timer_enemy_alpha=0;
    float timer_enemy_beta=0;
    float timer_enemy_gama=0; //used for enemy bombs
    float timer_fire_display=0; //this check is for 5 seconds display of power up
    float timer_bullet_multiple=0;
    float timer_multiple_display=0;
    float timer_release_dragon=0;
    float timer_display_dragon=0;//when dragon is displayed this works for 5 seconds 
    float timer_release_monster=0;
    float timer_display_monster=0;//when dragon is displayed this works for 5 seconds
    float timer_fire_monster=0;//for firing after 2 seconds
    float x_dragon_pos=0;
    int release=0;
    int release_enemy1=0; //for alpha bullets count 
    int release_enemy2=0; //for beta 
    int release_enemy3=0; //for gama
    int release_multiple=0; //for multiple bullets 
    int check=-1;
    int timer_check=0; //used to basically convert timer to int 
    int checker_enemy[40];//this array is created to check the collison 
    int checker_enemy_store=0;// used for the index of above array
    int checker_bullet[40];//this array is created to avoid checking of the same bullet after collision
    int checker_bullet_store=0;// used for the index of above array7
    int wave_checker=1;
    int level=1;
    int score=0; //for storing the value of score.
    bool danger_check=false;
    bool fire_check=false;
    bool multiple_check=false;
  
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
    bool hit_fire_check=false;
    bool hit_live_check=false;//used for checking the collision
    bool hit_multiple_check=false;
    bool move_right=false;// this is used beacuse of rotation of bullet
    bool move_left=false;
    bool dragon_check=false;
    bool monster_check=false;
    
    bool game_complete=false;
    const string filename = "scores.txt";
    ofstream outputFile;
    outputFile.open(filename, ios::app);
    
        Music music;
        music.openFromFile("music/lady-of-the-80x27s-128379.ogg");
        music.setVolume(95);
        music.play();
   
    
    
    
    while (window.isOpen())
    {
    	srand(time(0));
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time;  
        timer_enemy_danger+=time; 
        timer_enemy_alpha+=time; 
        timer_enemy_beta+=time; 
        timer_enemy_gama+=time; 
        timer_bullet_fire+=time;
        timer_bullet_multiple+=time;
        
       // timer_fire_display+=time;
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
        if (Keyboard::isKeyPressed(Keyboard::W)) // If w  key is pressed
        {
            p->rotate("w");  //player will move diagoanlly left
            move_left=true;
            move_right=false;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) // If s  key is pressed
        {
            p->rotate("s");  //player will move diagoanlly right
            move_left=false;
            move_right=true;
            
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) // If enter  key is pressed
        {
            p->rotate("a");  //player will move diagoanlly right
            move_left=false;
            move_right=false;
        }
            
        
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
	string png="";
	if (level==1)
	{
		png="img/background.jpg";
	}
	else if (level==2)
	{
		png="img/background1.jpg";
		p->speed=6;
	}
	else if (level==3)
	{
		png="img/background2.jpg";
		p->speed=8;
	}
	bg_texture.loadFromFile(png);
	background.setTexture(bg_texture);
	background.setScale(1, 1.5);
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
    if ((!dragon_check)&&(!monster_check))
    {
       if (!hit_multiple_check)
       {
        if (a%5==0)
        {
        	 //if (Keyboard::isKeyPressed(Keyboard::Space)) // If space  key is pressed
          	//{
            
         	if (hit_fire_check)
         	{
         		
         		
         		
         			b[release].release(p->position_x(),p->position_y(),move_right,move_left,hit_fire_check,false,false);
         			p->bullet_speed_change(b[release],level);
         	}
         	else 
        		b[release].release(p->position_x(),p->position_y(),move_right,move_left,hit_fire_check,false,false,bullet_choose);
        		p->bullet_speed_change(b[release],level);
        	//window.draw(b[release].sprite1);   //setting the bullet 
        	release++;
        	
        	//}
        	if (release==size)
        		window.close();	
        	
        	
        }
       }
    }
	for (int i=0;i<lives;i++)
		window.draw(l[i].lives);
	//this is used  for the danger sign 
	 if (timer_enemy_danger>25)
        {
        	p->release_danger();
        	p->release_live();
        	timer_enemy_danger=0;
        	danger_check=true;
        	hit_danger_check=false;
        	hit_live_check=false;
        	
        }
        
        //this is used to display the fire power up
        if (timer_bullet_fire>30)
        {
        	p->release_fire();
        	//p->release_live();
        	timer_bullet_fire=0;
        	
        	fire_check=true;
        	
        }
        //for movement of fire up
        if (fire_check)
        {
        	p->fire_fire();
        	if (!hit_fire_check)
        		window.draw(p->sprite7);
        	if (((p->y7>=p->y-20)&&(p->y7<=p->y+20))&&((p->x7>=p->x-10)&&(p->x7<=p->x+30)))
        	{
        		hit_fire_check=true;
        		p->y7=-1000;
       	 	p->x7=-1000;
        	}
        	if (hit_fire_check)
        		timer_fire_display+=time;
        	if (timer_fire_display>=5)
         		{
         			hit_fire_check=false;
         			fire_check=false;
         			cout<<timer_fire_display<<endl;
         			timer_fire_display=0;
         		}
        }
        // if fire moves out of game
        if (p->y7>=750)
        {
        	fire_check=false;
        	p->y7=-1000;
        	p->x7=-1000;
        }
         //bool simple_check=false;
	if (danger_check)
        {
        	
       	 p->fire_danger();
       	 p->fire_live();
       	 if (!hit_live_check)
       	 {
       		 window.draw(p->sprite6);
       	}
       	 if (!hit_danger_check)
       		 window.draw(p->sprite5);
       	 if (((p->y4>=p->y-20)&&(p->y4<=p->y+20))&&((p->x4>=p->x-10)&&(p->x4<=p->x+30)))
       	 {
       	 	
       	 	lives_copy--;
       	 	lives=lives_copy;
       	 	p->y4=-1000;
       	 	p->x4=-1000;
       	 	p->x=340;p->y=650; 
       	 	p->sprite.setPosition(p->x,p->y);
       	 	hit_danger_check=true;
       	 	danger_check=false;
       	 	//p->explosion();
       	 	//window.draw(p->s);
       	 }
       	 if (((p->y6>=p->y-20)&&(p->y6<=p->y+20))&&((p->x6>=p->x-10)&&(p->x6<=p->x+30)))
       	 {
       	 	lives_copy=lives+1;
       	 	lives=lives_copy;
       	 	p->y6=-1000;
       	 	p->x6=-1000;
       	 	hit_live_check=true;
       	 	danger_check=false;
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
       	hit_live_check=false;
       	p->x4=-1000;
       	p->y4=-1000;
       }
       // for multiple bullet power up
       if (timer_bullet_multiple>5)
        {
        	p->release_multiple();
        	//p->release_live();
        	timer_bullet_multiple=0;
        	
        	multiple_check=true;
        	
        }
        //for movement of fire up
        if (multiple_check)
        {
        	p->multiple_multiple();
        	if (!hit_multiple_check)
        		window.draw(p->sprite8);
        	if (((p->y8>=p->y-20)&&(p->y8<=p->y+20))&&((p->x8>=p->x-10)&&(p->x8<=p->x+30)))
        	{
        		hit_multiple_check=true;
        		p->y8=-1000;
       	 	p->x8=-1000;
       	 	
        	}
        	if (hit_multiple_check)
        		timer_multiple_display+=time;
        	if (timer_multiple_display>5)
        	{
			timer_multiple_display=0;
			hit_multiple_check=false;
			multiple_check=false;
		}
		timer_bullet_multiple=0;
        	
         	
        }
        //the below part is for multiple bullets that is it contains power up feature of multiple bullets 
        // a couple of things are going to be repeated again
        // will be using b2 as a double pointer for displaying
        if (hit_multiple_check&&((!dragon_check)&&(!monster_check)))
        {
        if (a%20==0)
        {
        	for (int i=0;i<5;i++)
        	{
         		if (i==0)
         			b2[i][release_multiple].release(p->position_x(),p->position_y(),false,false,false,false,false,bullet_choose);
         		else if (i==1)
         			b2[i][release_multiple].release(p->position_x()+50,p->position_y(),true,false,false,false,false,bullet_choose);
         		else if (i==2)
         			b2[i][release_multiple].release(p->position_x()-50,p->position_y(),false,true,false,false,false,bullet_choose);
         		else if (i==3)
         			b2[i][release_multiple].release(p->position_x()+25,p->position_y(),false,false,false,true,false,bullet_choose);
         		else if (i==4)
         			b2[i][release_multiple].release(p->position_x()-25,p->position_y(),false,false,false,false,true,bullet_choose);
         		p->bullet_speed_change(b2[i][release_multiple],level);
         	}
         	
        	
        	release_multiple++;
        }
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<release_multiple;j++)
			{
				if (i==0)
		 			b2[i][j].fire(false,false,false,false);
		 		else if (i==1)
		 			b2[i][j].fire(true,false,false,false);
		 		else if (i==2)
		 			b2[i][j].fire(false,true,false,false);
		 		else if (i==3)
		 			b2[i][j].fire(false,false,true,false);
		 		else if (i==4)
		 			b2[i][j].fire(false,false,false,true);
		 		window.draw(b2[i][j].sprite1);
		 	}
		}
        
        //this is for if(multiple_check)
        
       //for collison check 
       bool true_checker7=false;
	
	for (int i=0;i<5;i++)
	{
		for (int h=0;h<release_multiple;h++)
		{
		for (int j=0;j<enemy_size;j++)
		{
		
			for (int k=0;k<enemy_size;k++)
			{
				if (j!=checker_enemy[k])
				{
					true_checker7=true;
				}
				else 
				{
					true_checker7=false;
					break;
				}
			}
				if (true_checker7)
				{	
				if ((b2[i][h].x1>=(en[j].x2-10)&&b2[i][h].x1<=(en[j].x2+40))&&(b2[i][h].y1>=(en[j].y2-30)&&b2[i][h].y1<=(en[j].y2+30))) 
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
		}
		
		true_checker7=false;
	} 
	}//end of multiple check
	if (p->y8>=750) //y4 is multi level inheritance of danger class ...x4 y4 are  of dannger 
       {
       	multiple_check=false;
       	//if (!simple_check)
       	//	score+=5;
       	//simple_check=true;
       	if (!hit_danger_check)
       		score+=5;
       	hit_danger_check=false;
       	hit_live_check=false;
       	p->x8=-1000;
       	p->y8=-1000;
       }
       //multiple bullets end
       
       
       //dragon calling
       if (level==3)
      {
       	timer_release_dragon+=time;
        
	       if (timer_release_dragon>5&&(!dragon_check))
	       {
	       	d=new dragon;
	       	d2=new dragon;
	       	d3=new dragon;
	       	d->display();
	       	d2->display(-10,85,200,"img/rotate/image(12).png");
	       	d3->display(10,700,200,"img/rotate/image(13).png");
	       	d->fire_dragon(320,320);
	       	d2->fire_dragon(120,350,-10,"img/rotate/image(17).png");
	       	d3->fire_dragon(670,350,10,"img/rotate/image(16).png");
			dragon_check=true;
			timer_release_dragon=0;
			p->speed=1;
		}
		if (dragon_check)
		{
			
			if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
			{
						if (p->x<0)
		      					x_dragon_pos=1;// Player will move to left
		      				else 
		      					x_dragon_pos=-1;
		      	}
			if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
			{
		    				if (p->x>750)
		      					x_dragon_pos=-1;// Player will move to left
		      				else 
		      					x_dragon_pos=1;
		    	}
			d->movement_dragon(x_dragon_pos);// for first dragon
			
			d->movement_beam(x_dragon_pos);
			d2->movement_dragon(x_dragon_pos);//for second dragon
			
			d2->movement_beam(x_dragon_pos);
			d3->movement_dragon(x_dragon_pos);//for third dragon
			
			d3->movement_beam(x_dragon_pos);
			
			window.draw(d->sprite2);
			window.draw(d->sprite);
			window.draw(d2->sprite2);
			window.draw(d2->sprite);
			window.draw(d3->sprite2);
			window.draw(d3->sprite);
			timer_display_dragon+=time;
			if (((d->y_beam+330>=p->y-20)&&(d->y_beam<=p->y+20))&&((d->x_beam>=p->x-10)&&(d->x_beam<=p->x+30)))
			{
				p->x=40;p->y=650; 
       	 		p->sprite.setPosition(p->x,p->y);
       	 		lives_copy--;
       	 		lives=lives_copy;
			}
			if (((d2->y_beam+330>=p->y-20)&&(d2->y_beam<=p->y+20))&&((d2->x_beam-10>=p->x-10)&&(d2->x_beam<=p->x+30)))
			{
				p->x=40;p->y=650; 
       	 		p->sprite.setPosition(p->x,p->y);
       	 		lives_copy--;
       	 		lives=lives_copy;
			}
			if (((d3->y_beam+330>=p->y-20)&&(d3->y_beam<=p->y+20))&&((d3->x_beam-35>=p->x-10)&&(d3->x_beam<=p->x+30)))
			{
				p->x=40;p->y=650; 
       	 		p->sprite.setPosition(p->x,p->y);
       	 		lives_copy--;
       	 		lives=lives_copy;
			}
			if (timer_display_dragon>15)
			{
				dragon_check=false;
				timer_display_dragon=0;
				x_dragon_pos=0;
				if (lives!=0)
					score+=50;
				delete d;
				delete d2;
				delete d3;
			}
			timer_release_dragon=0;
			
			
		}
	}
	
	//calling monster and doing all the checks and stuff
	if (level==2)
	{
		timer_release_monster+=time;
		if (timer_release_monster>20&&(!monster_check))
	       {
	       	m=new monster;
	       	m->display();
	       	
			monster_check=true;
			timer_release_monster=0;
		}
		if (monster_check)
		{
			
			m->movement_monster();
			bool val=m->fire_monster();
			
			window.draw(m->sprite2);
			if (val)
			{
				timer_fire_monster+=time;
				if (timer_fire_monster<2)
				{
					window.draw(m->sprite);
					//timer_fire_monster=0;
				}
				else if (timer_fire_monster>4)
					timer_fire_monster=0;
			}
			else 
			{
				m->x_beam=-1000;
				m->y_beam=-1000;
				timer_fire_monster=0;
			}
			
				//window.draw(m->sprite);
			timer_display_monster+=time;
			if (((m->y_beam+330>=p->y-20)&&(m->y_beam<=p->y+20))&&((m->x_beam>=p->x-10)&&(m->x_beam<=p->x+30)))
			{
				p->x=340;p->y=650; 
       	 		p->sprite.setPosition(p->x,p->y);
       	 		lives_copy--;
       	 		lives=lives_copy;
			}
			if (timer_display_monster>10)
			{
				monster_check=false;
				timer_display_monster=0;
				//x_dragon_pos=0;
				if (lives!=0)
					score+=40;
				delete m;
				m=NULL;
			}
			timer_release_monster=0;
			
			
			
		}
       
       }
       
       
       
       
       
       
      	
       // this loop is used to display the bullets as well as check if the bullet has collided with the enemy or not 
	bool true_checker2=false;
	for (int i=0;i<release;i++)
        {
        	if (!hit_fire_check)
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
		}
		else 
			true_checker2=true;
		if (true_checker2)
		{
			b[i].fire(move_right,move_left,false,false);  
        		window.draw(b[i].sprite1); 
        	}
        	true_checker2=false;
		
	        	
        }
        // the below loop is used for displaying the enemy sprites as well as checking if that enemy has been killed or not 
        float enemy_position_x=0;
        float enemy_position_y=0;
        if (level==1&&((!dragon_check)&&(!monster_check)))
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
			/*if (i==(enemy_size/2 -1))
			{
				enemy_position_x=en[0].x2;
				enemy_position_y+=100;
			}*/
			if (i==9)
			{
				enemy_position_x=en[0].x2;
				enemy_position_y+=100;
			}
			if (i==10)
			{
				enemy_position_x=720;
				//enemy_position_y+=100;
			}
			if (i==11)
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
	int a_rand=rand()%a_limit;
	int b_rand=rand()%b_limit;
	int c_rand=rand()%enemy_size;
	bool true_checker4=false;
	if (timer_enemy_alpha>2)
	{
		for (int i=0;i<a_limit;i++)
		{
			if (a_rand!=checker_enemy[i])
			{
				true_checker4=true;
			}
			else
			{
				true_checker4=false;
				//en[j].x2=0; en[j].y2=0;
				break;
			}
				
			
			//if (i==1)
			//	break;
		}
		if (true_checker4)
			bomb[a_rand][release_enemy1].release_enemy(en[a_rand].x2,en[a_rand].y2);
		timer_enemy_alpha=0;
		release_enemy1++;
	}
	bool true_checker5=false;
	if (timer_enemy_beta>3)
	{
		if (b_rand>=a_limit)
		{
			for (int i=a_limit;i<b_limit;i++)
			{
				if (b_rand!=checker_enemy[i])
				{
					true_checker5=true;
				}
				else
				{
					true_checker5=false;
					//en[j].x2=0; en[j].y2=0;
					break;
				}
				
			//	if (i==a_limit+1)
			//		break;
			}
			if (true_checker5)
				bomb[b_rand][release_enemy2].release_enemy(en[b_rand].x2,en[b_rand].y2);
		}
		timer_enemy_beta=0;
		release_enemy2++;
	}
	bool true_checker6=false;
	if (timer_enemy_gama>5)
	{
		if (c_rand>=b_limit)
		{
			for (int i=b_limit;i<enemy_size;i++)
			{
				if (c_rand!=checker_enemy[i])
					{
						true_checker6=true;
					}
					else
					{
						true_checker6=false;
						//en[j].x2=0; en[j].y2=0;
						break;
					}
					
				
			//	if (i==b_limit+1)
			//		break;
			}
			if (true_checker6)
				bomb[c_rand][release_enemy3].release_enemy(en[c_rand].x2,en[c_rand].y2);
		}
		
		timer_enemy_gama=0;
		release_enemy3++;
	}
	//bool true_checker3=false;
	for (int i=0;i<enemy_size;i++)
	{
		/*for (int j=0;j<enemy_size;j++)
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
		}*/
		
		//if (true_checker3)
		//{
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
		//}
		//true_checker3=false;
		
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
				//cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				if (!hit_multiple_check)
				{
					lives_copy--;
					lives=lives_copy;
					p->x=340;p->y=650; 
	       	 		p->sprite.setPosition(p->x,p->y);
	       	 		bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
	       	 	}
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				
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
				if (!hit_multiple_check)
				{
					lives_copy--;
					lives=lives_copy;
					p->x=340;p->y=650; 
	       	 		p->sprite.setPosition(p->x,p->y);
	       	 		bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
	       	 	}
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				
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
				if (!hit_multiple_check)
				{
					lives_copy--;
					lives=lives_copy;
					p->x=340;p->y=650; 
	       	 		p->sprite.setPosition(p->x,p->y);
	       	 		bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
	       	 	}
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				
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
	//collsion of space ship with enemy
	bool true_checker7=false;
	for (int i=0;i<enemy_size;i++)
	{
		for (int j=0;j<enemy_size;j++)
		{	
			if (i!=checker_enemy[j])
			{
					true_checker7=true;
			}
			else 
			{
					true_checker7=false;
					break;
			} 
		}
		if (true_checker7)
		{
			if (((en[i].y2>=p->y-20)&&(en[i].y2<=p->y+20))&&((en[i].x2>=p->x-10)&&(en[i].x2<=p->x+30)))
			{
				lives_copy--;
	       	 	lives=lives_copy;
	       	 	
	       	 	p->x=340;p->y=650; 
	       	 	p->sprite.setPosition(p->x,p->y);
	       	 }
	      	}
		
	}
	}//this is the end of the level==1 condition
	
	if (level==2&&((!dragon_check)&&(!monster_check)))
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
			
			
		    float S = 360.0f / 20; // calculate the angle between each position in the circle

		    // loop through each position in the circle and calculate its x and y coordinates based on the angle
		    
			float ang = i * S;
			float x = 300 + 200 * cos(ang * 3.14159f / 180.0f);
			float y = 300 + 200 * sin(ang * 3.14159f / 180.0f);
			
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
	int a_rand=rand()%a_limit;
	int b_rand=rand()%b_limit;
	int c_rand=rand()%enemy_size;
	
	bool true_checker4=false;
	if (timer_enemy_alpha>2)
	{
		for (int i=0;i<a_limit;i++)
		{
			if (a_rand!=checker_enemy[i])
			{
				true_checker4=true;
			}
			else
			{
				true_checker4=false;
				//en[j].x2=0; en[j].y2=0;
				break;
			}
				
			
			//if (i==1)
			//	break;
		}
		if (true_checker4)
			bomb[a_rand][release_enemy1].release_enemy(en[a_rand].x2,en[a_rand].y2);
		timer_enemy_alpha=0;
		release_enemy1++;
	}
	bool true_checker5=false;
	if (timer_enemy_beta>3)
	{
		if (b_rand>=a_limit)
		{
			for (int i=a_limit;i<b_limit;i++)
			{
				if (b_rand!=checker_enemy[i])
				{
					true_checker5=true;
				}
				else
				{
					true_checker5=false;
					//en[j].x2=0; en[j].y2=0;
					break;
				}
				
			//	if (i==a_limit+1)
			//		break;
			}
			if (true_checker5)
				bomb[b_rand][release_enemy2].release_enemy(en[b_rand].x2,en[b_rand].y2);
		}
		timer_enemy_beta=0;
		release_enemy2++;
	}
	bool true_checker6=false;
	if (timer_enemy_gama>5)
	{
		if (c_rand>=b_limit)
		{
			for (int i=b_limit;i<enemy_size;i++)
			{
				if (c_rand!=checker_enemy[i])
					{
						true_checker6=true;
					}
					else
					{
						true_checker6=false;
						//en[j].x2=0; en[j].y2=0;
						break;
					}
					
				
			//	if (i==b_limit+1)
			//		break;
			}
			if (true_checker5)
				bomb[c_rand][release_enemy3].release_enemy(en[c_rand].x2,en[c_rand].y2);
		}
		
		timer_enemy_gama=0;
		release_enemy3++;
	}
	//cout<<33<<endl;
	//bool true_checker3=false;
	for (int i=0;i<enemy_size;i++)
	{
		/*for (int j=0;j<enemy_size;j++)
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
		*/
		
		//if (true_checker3)
		//{
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
		//}
		//cout<<i<<endl;
		//true_checker3=false;
		
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
				//cout<<bomb[i][j].y3<<" "<<p->y+30<<" "<<i<<" "<<j<<endl;
				lives_copy--;
				lives=lives_copy;
				hit_check=true;
				bomb[i][j].x3=0;
				bomb[i][j].y3=0;
				p->x=340;p->y=650; 
       	 	p->sprite.setPosition(p->x,p->y);
       	 	bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
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
       	 	bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
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
       	 	bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}	
	//the below loop is used for the collison check! based on checker_enemy and checker_bullet
	bool true_checker1=false;
	//cout<<41<<endl;
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
	//collsion of space ship with enemy
	bool true_checker7=false;
	for (int i=0;i<enemy_size;i++)
	{
		for (int j=0;j<enemy_size;j++)
		{	
			if (i!=checker_enemy[j])
			{
					true_checker7=true;
			}
			else 
			{
					true_checker7=false;
					break;
			} 
		}
		if (true_checker7)
		{
			if (((en[i].y2>=p->y-20)&&(en[i].y2<=p->y+20))&&((en[i].x2>=p->x-10)&&(en[i].x2<=p->x+30)))
			{
				lives_copy--;
	       	 	lives=lives_copy;
	       	 	
	       	 	p->x=340;p->y=650; 
	       	 	p->sprite.setPosition(p->x,p->y);
	       	 }
	      	}
		
	}
	}//end of level 2  condition
	
	if (level==3&&((!dragon_check)&&(!monster_check)))
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
        enemy_position_x=10;
        enemy_position_y=250;
	for (int i=0;i<enemy_size;i++)
	{
		
		//cout<<2<<endl;
		if (wave_checker==1)
		{
			
			
		 	
			if (i==10)
			{
				enemy_position_x=10;
				enemy_position_y+=100;
			}
			else if (i==20)
			{
				enemy_position_x=10;
				enemy_position_y+=100;
			}
			else if (i==30)
			{
				enemy_position_x=10;
				enemy_position_y+=100;
			}
			en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
			enemy_position_x+=80;
			
		 //rectangle enimies and enemy_szie=31;
		}
		    
		else if (wave_checker==2)
		{
		
			if (i<20)
			{
			 float angleStep = 360.0f / 20; // calculate the angle between each position in the circle

		    // loop through each position in the circle and calculate its x and y coordinates based on the angle
		    
			float angle = i * angleStep;
			float x = 300 + 200 * cos(angle * 3.14159f / 180.0f);
			float y = 300 + 200 * sin(angle * 3.14159f / 180.0f);
			
			en[i].placement(x,y,i,a_limit,b_limit);
			}
			else if (i<30)
			{
				float angleStep = 360.0f / 15; // calculate the angle between each position in the circle

		    // loop through each position in the circle and calculate its x and y coordinates based on the angle
		    
			float angle = i * angleStep;
			float x = 300 + 150 * cos(angle * 3.14159f / 180.0f);
			float y = 300 + 150 * sin(angle * 3.14159f / 180.0f);
			
			en[i].placement(x,y,i,a_limit,b_limit);
			}
			else if (i<40)
			{
				float angleStep = 360.0f / 10; // calculate the angle between each position in the circle

		    // loop through each position in the circle and calculate its x and y coordinates based on the angle
		    
			float angle = i * angleStep;
			float x = 300 + 100 * cos(angle * 3.14159f / 180.0f);
			float y = 300 + 100 * sin(angle * 3.14159f / 180.0f);
			
			en[i].placement(x,y,i,a_limit,b_limit);
			}// for filled circle enemy_size=40;
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
			else if (i<21)
			{
				enemy_position_x=400;
				enemy_position_y=400;
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				enemy_position_x-=50;
				enemy_position_y-=50;
			}
			else if (i<23)
			{
				
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				enemy_position_x+=100;
				//enemy_position_y-=50;
				if (i==22)
				{
					enemy_position_x-=250;
					enemy_position_y-=50;
				}
				
			}
			else if (i<26)
			{
				
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				
				enemy_position_x+=100;
				//enemy_position_y-=50;
				if (i==25)
				{
					enemy_position_x=250;
					enemy_position_y-=50;
				}
				
			}
			else if (i<30)
			{
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				
				enemy_position_x+=100;
				if (i==29)
				{
					enemy_position_x=200;
					enemy_position_y-=50;
				}
				
				//enemy_position_y-=50;
			}
			else if (i<34)
			{
				
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				if (i==31)
					enemy_position_x+=200;
				else 
					enemy_position_x+=100;
				//enemy_position_y-=50;
				if (i==33)
				{
					enemy_position_x=240;
					enemy_position_y-=50;
				}
				
			}
			else if (i<36)
			{
				
				en[i].placement(enemy_position_x,enemy_position_y,i,a_limit,b_limit);
				
					enemy_position_x+=300;
				
				
				
			}//enemy_size=36
				
				
				
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
	int a_rand=rand()%a_limit;
	int b_rand=rand()%b_limit;
	int c_rand=rand()%enemy_size;
	
	bool true_checker4=false;
	if (timer_enemy_alpha>2)
	{
		for (int i=0;i<a_limit;i++)
		{
			if (a_rand!=checker_enemy[i])
			{
				true_checker4=true;
			}
			else
			{
				true_checker4=false;
				//en[j].x2=0; en[j].y2=0;
				break;
			}
				
			
			//if (i==1)
			//	break;
		}
		if (true_checker4)
			bomb[a_rand][release_enemy1].release_enemy(en[a_rand].x2,en[a_rand].y2);
		timer_enemy_alpha=0;
		release_enemy1++;
	}
	bool true_checker5=false;
	if (timer_enemy_beta>3)
	{
		if (b_rand>=a_limit)
		{
			for (int i=a_limit;i<b_limit;i++)
			{
				if (b_rand!=checker_enemy[i])
				{
					true_checker5=true;
				}
				else
				{
					true_checker5=false;
					//en[j].x2=0; en[j].y2=0;
					break;
				}
				
			//	if (i==a_limit+1)
			//		break;
			}
			if (true_checker5)
				bomb[b_rand][release_enemy2].release_enemy(en[b_rand].x2,en[b_rand].y2);
		}
		timer_enemy_beta=0;
		release_enemy2++;
	}
	bool true_checker6=false;
	if (timer_enemy_gama>5)
	{
		if (c_rand>=b_limit)
		{
			for (int i=b_limit;i<enemy_size;i++)
			{
				if (c_rand!=checker_enemy[i])
					{
						true_checker6=true;
					}
					else
					{
						true_checker6=false;
						//en[j].x2=0; en[j].y2=0;
						break;
					}
					
				
			//	if (i==b_limit+1)
			//		break;
			}
			if (true_checker5)
				bomb[c_rand][release_enemy3].release_enemy(en[c_rand].x2,en[c_rand].y2);
		}
		
		timer_enemy_gama=0;
		release_enemy3++;
	}
	//cout<<33<<endl;
	//bool true_checker3=false;
	for (int i=0;i<enemy_size;i++)
	{
		/*for (int j=0;j<enemy_size;j++)
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
		}*/
		
		
		//if (true_checker3)
		//{
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
		//}
		//cout<<i<<endl;
		//true_checker3=false;
		
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
       	 	bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
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
       	 	bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
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
       	 	bomb[i][j].x3=-1000;
	       	 		bomb[i][j].y3=-1000;
	       	 		bomb[i][j].sprite3.setPosition(bomb[i][j].x3,bomb[i][j].y3);
				break;
				
				//cout<<"COLLISION HAS OCCURED"<<endl;
			}
			
		}
		if (hit_check)	
			break;
	}	
	//the below loop is used for the collison check! based on checker_enemy and checker_bullet
	bool true_checker1=false;
	//cout<<41<<endl;
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
	//collsion of space ship with enemy
	bool true_checker7=false;
	for (int i=0;i<enemy_size;i++)
	{
		for (int j=0;j<enemy_size;j++)
		{	
			if (i!=checker_enemy[j])
			{
					true_checker7=true;
			}
			else 
			{
					true_checker7=false;
					break;
			} 
		}
		if (true_checker7)
		{
			if (((en[i].y2>=p->y-20)&&(en[i].y2<=p->y+20))&&((en[i].x2>=p->x-10)&&(en[i].x2<=p->x+30)))
			{
				lives_copy--;
	       	 	lives=lives_copy;
	       	 	
	       	 	p->x=340;p->y=650; 
	       	 	p->sprite.setPosition(p->x,p->y);
	       	 }
	      	}
		
	}
	}//end of level 3  condition
	
	

	
	
	
	
	
	
	window.display();  //Displying all the sprites
	if (level==3&&((checker_enemy_store==(enemy_size)-1)))
		checker_enemy_store++;
	if (checker_enemy_store==(enemy_size))
	{
	//first time when the wave gets cleared then wave checker is true then the very moment wave checker becomes false and 
	//the next time it moves to else this check is made false in the enemy placement condition
		if (level==3)
				cout<<"WAVE CHECKER"<<endl;
		if (wave_checker==1)
		{
			if (level==3)
				cout<<"WAVE CHECKER"<<endl;
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
				enemy_size=40;
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
			for (int i=0;i<5;i++)
				delete[]b2[i];
			delete []b2;
			b2=new bullet*[5];
			for (int i=0;i<5;i++)
			{
				b2[i]=new bullet[size];
			}
			
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
				enemy_size=36;
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
			for (int i=0;i<5;i++)
				delete[]b2[i];
			delete []b2;
			b2=new bullet*[5];
			for (int i=0;i<5;i++)
			{
				b2[i]=new bullet[size];
			}
			
		}
    		if (wave_checker==4)
    		{
    			if (level==1)
    			{
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
			}
    			if (level==2)
    			{
    				//window.close();
    				//cout<<"SCORE: "<<score<<endl;
    				Sprite level2;
	    			Texture level2c;
	    			level2c.loadFromFile("img/level2.png");
				level2.setTexture(level2c);
				level2.setScale(1, 1);
	    			RenderWindow window_complete_level2(VideoMode(300,300), "LEVEL-2 COMPLETED");
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
    			if (level==3)
    			{
    				game_complete=true;
    				//cout<<"SCORE: "<<score<<endl;
    				Sprite level2;
	    			Texture level2c;
	    			level2c.loadFromFile("img/level3.jpeg");
				level2.setTexture(level2c);
				level2.setScale(1, 1);
	    			RenderWindow window_complete_level3(VideoMode(300,300), "LEVEL-3 COMPLETED");
	    			while (window_complete_level3.isOpen())
				{
					
				 	Event level3_complete;
					while (window.pollEvent(level3_complete))
					{  
					    if (level3_complete.type == Event::Closed) // If cross/close is clicked/pressed
						window_complete_level3.close(); //close the game                        	    
					}
					if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
		   				window_complete_level3.close();
					window_complete_level3.clear(Color::Black); //clears the screen
					window_complete_level3.draw(level2);  // setting background
					window_complete_level3.display();
					
					
				}
			}
    			//previous setup because after it will come completing level 2 3 waves it goes there 
    			if (level==1)
    				level=2;
    			else if (level==2)
    				level=3;
    				
    			
    				wave_checker=1;
    			
    			
			if (level==2)
			{
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
				
    			}
    			if (level==3)
    			{
    				for (int i=0;i<enemy_size;i++)
		    			checker_enemy[i]=-1;
		    		  for (int i=0;i<enemy_size;i++)
		    			checker_bullet[i]=-1;
		    		delete[]b;
		    		b=new bullet[size];
		    		for (int i=0;i<enemy_size;i++)
					delete[]bomb[i];
				delete[]bomb;
				enemy_size=31;
				//wave_checker=1;
			}
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
				for (int i=0;i<5;i++)
					delete[]b2[i];
				delete []b2;
				b2=new bullet*[5];
				for (int i=0;i<5;i++)
				{
					b2[i]=new bullet[size];
				}
			
    			//cout<<"CONGRATULATIONS ON COMPLETING LEVEL 1 OF THE GAME"<<endl;
    			//cout<<"CONGRATULATIONS ON COMPLETING LEVEL 2 OF THE GAME"<<endl;
    			//cout<<"SCORE: "<<score<<endl;
    			
    			
    		}
    		//cout<<"HELLO"<<endl;
		
		
	}
	
	
	if (lives==0||game_complete )
	{
		
		//cout<<"YOU RAN OUT OF LIVES"<<endl;
		outputFile << score << endl;
   		 outputFile.close();
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
    //cout<<score;
    
    
  

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








    
  
   

