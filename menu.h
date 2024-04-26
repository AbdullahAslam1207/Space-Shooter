
#include "game1.h"
#include<string>
class Menu{
public:
	Texture tex,tex1,tex2,tex3;
	Sprite s,s1,s2,s3;
	Font Calibri;//font declared
	
	//bool value=false;

//add menu attributes here
Menu()
{
tex.loadFromFile("img/game_start.png");
s.setTexture(tex);
s.setScale(1, 1.5);
tex1.loadFromFile("img/menu.png");
s1.setTexture(tex1);
s1.setScale(1, 1.5);
tex2.loadFromFile("img/ins.png");
s2.setTexture(tex2);
s2.setScale(1, 1.5);
tex3.loadFromFile("img/high.png");
s3.setTexture(tex3);
s3.setScale(2, 1.5);
Calibri.loadFromFile("img/Calibri.ttf");
//constructors body
}

void display_menu()

{
	RenderWindow window(VideoMode(630, 500), "START");
	//RenderWindow window_start(VideoMode(780, 780), "MENU");
	//RenderWindow window_inst(VideoMode(780, 780), "INSTRUCTIONS");
	while (window.isOpen())
    	{
        
	 	Event e;
		while (window.pollEvent(e))
		{  
		    if (e.type == Event::Closed) // If cross/close is clicked/pressed
		        window.close(); //close the game                        	    
		}
		  
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			window.close();
			RenderWindow window_start(VideoMode(630, 500), "MENU");
			while (window_start.isOpen())
			{
				Event e1;
				while (window_start.pollEvent(e1))
				{  
		    			if (e1.type == Event::Closed) // If cross/close is clicked/pressed
		        		window_start.close(); //close the game                        	    
				}
				if (Keyboard::isKeyPressed(Keyboard::Num1))
				{
					window_start.close();
					Game g;
					
					g.start_game();
				}
				else if (Keyboard::isKeyPressed(Keyboard::Num2))
				{
					//window_start.close();
					RenderWindow window_inst(VideoMode(630, 500), "INSTRUCTIONS");
					while (window_inst.isOpen())
					{
						Event e2;
						while (window_inst.pollEvent(e2))
						{  
		    					if (e2.type == Event::Closed) // If cross/close is clicked/pressed
		        					window_inst.close(); //close the game                        	    
						}
						window_inst.clear(Color::Black);
						window_inst.draw(s2);
						window_inst.display();
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Num3))
				{
					//window_start.close();
					RenderWindow window_high(VideoMode(500, 500), "HIGH SCORES");
					while (window_high.isOpen())
					{
						Event e3;
						while (window_high.pollEvent(e3))
						{  
		    					if (e3.type == Event::Closed) // If cross/close is clicked/pressed
		        					window_high.close(); //close the game                        	    
						}
						ifstream inputFile;
						    inputFile.open("scores.txt");
						    
						   
						    int top[3] = {0};
						    int index = 0;
						    int sc = 0;
						    while (inputFile >> sc) {
							for (int i = 0; i < 3; i++) {
							    if (sc > top[i]) {
								for (int j = 2; j > i; j--) {
								    top[j] = top[j - 1];
								}
								top[i] = sc;
								break;
							    }
							}
						    }
						cout<<top[0]<<endl;
						string timing=to_string(top[0]);//to display on screen
						Text Score1(timing,Calibri);
						Score1.setCharacterSize(20);
						Score1.setFillColor(Color::Red);
						Score1.setPosition(300,150);
						
						
						string timing1=to_string(top[1]);//to display on screen
						Text Score2(timing1,Calibri);
						Score2.setCharacterSize(20);
						Score2.setFillColor(Color::Red);
						Score2.setPosition(300,270);
						
						string timing3=to_string(top[2]);//to display on screen
						Text Score3(timing3,Calibri);
						Score3.setCharacterSize(20);
						Score3.setFillColor(Color::Red);
						Score3.setPosition(300,370);
						
						
			
						window_high.clear(Color::Black);
						window_high.draw(s3);
						window_high.draw(Score1);
						window_high.draw(Score2);
						window_high.draw(Score3);
						//window.draw(text3);
						window_high.display();
					}
				}
				window_start.clear(Color::Black);
				window_start.draw(s1);
				window_start.display();
			}
		}
	
					
		       		     
		    
		    
		window.clear(Color::Black); //clears the screen
		window.draw(s);  // setting background
		window.display();
	}
		   
		
	
        
    



}


};


