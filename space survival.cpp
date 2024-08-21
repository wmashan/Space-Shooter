/*
c++ mini PROJECT GROUP 11
members
1. IM/2022/025     -   Ashan  
2. IM/2022/014     - Nirasha
3. IM/2022/112     - Tharindu
4. IM/2022/111     -   Gihan

about our game - 
name -Space shooter
type -shooting 
*/

#include<iostream>
#include<conio.h>
#include <windows.h>   //to move cursor, beep sound
#include <time.h>


#define SCREEN_WIDTH 95
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 90   



using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int ObjectY[3];
int ObjectX[3];
int ObjectFlag[3];
string playerName;

//shape of ship
char Ship[3][5] = { ' ',' ',4,' ',' ',  // initialize 2D array for bullets
					'[',']',4,'[',']',  
					'=',4,4,4,'=' };
int ShipPos = WIN_WIDTH/2;
int score = 0;
int bullets[22][4];
int bulletsLife[20];
int bIndex = 0;

//cursor shift

void gotoxy(int x, int y);  
void setcursor(bool visible, DWORD size);
void drawBorder();
void genObject(int ind);
void drawObject(int ind);
void eraseObject(int ind);
void resetObject(int ind);
void genBullet();
void moveBullet();
void drawBullets();
void eraseBullets();
void eraseBullet(int i);
void interface1();
void interface2();
void interface3();
void quitWindow();
void playerInfo();
void credits();
void drawShip();
void eraseShip();
void drawRocketBlasting();

int bulletHit();
void gameover();
void updatescore();
void instructions();
void playTimeBased();
void playCampaign();


int main()
{
	setcursor(0,0); // avoid cursor distrupting the interface while playing
	interface1();
    return 0;
}

void gotoxy(int x, int y){   //Most important function, for move cursor pointer for desired position 
	CursorPosition.X = x;  //Updates CursorPosition.X and CursorPosition.Y to the given coordinates.                                        
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition); //Calls SetConsoleCursorPosition(console, CursorPosition) to move the cursor to the desired position.
}

void setcursor(bool visible, DWORD size) { //Controls the visibility and size of the console cursor. It can hide or show the cursor and adjust its size.
	if(size == 0) //If size is 0, it sets a default size of 20.
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor); //Configures lpCursor with the given visibility and size and applies it using SetConsoleCursorInfo.
}


void drawBorder(){  // to draw specific symbolic border using printf , in palying area

	for(int i=22; i<=SCREEN_WIDTH; i++){  //22  bottom line play area
		gotoxy(i,SCREEN_HEIGHT+2); //Uses gotoxy to place the cursor at different points around the screen and prints border characters (e.g., ' and |) to create the borders.
		printf("%c",193);

	}

	for(int i=2; i<=SCREEN_HEIGHT+1; i++){
	    gotoxy(22,i);   //left line paly area
		printf("%c",208);

		gotoxy(SCREEN_WIDTH,i);  //right line paly area
		printf("%c",208);

	}

}


//generate object
void genObject(int ind){ //Generates random positions for obstacles or objects on the screen. The ind parameter indicates which object (out of three) is being generated.
	ObjectX[ind] = 44 + rand()%(44);    //to change obstacles generate width in console 
}                                       //Sets ObjectX[ind] to a random value between 44 and 88.

//for drawing object Shape using cout statements while object flag is true.
void drawObject(int ind){   //Draws an obstacle or object at a specified position on the screen. The object is represented with a series of ASCII characters.
	if( ObjectFlag[ind] == true ){
		gotoxy(ObjectX[ind], ObjectY[ind]+1);
        cout<<" -^- ";
		gotoxy(ObjectX[ind], ObjectY[ind]+2);
	    cout<<" *** ";
        gotoxy(ObjectX[ind], ObjectY[ind]+3);
		cout<<"-!!!-";
	    gotoxy(ObjectX[ind], ObjectY[ind]+4);
		cout<<"  +  ";
	

	}
}
//erase each drawn object using empty spaces
void eraseObject(int ind){
	if( ObjectFlag[ind] == true ){
		gotoxy(ObjectX[ind], ObjectY[ind]+1);
		cout<<"      ";
		gotoxy(ObjectX[ind], ObjectY[ind]+2);
		cout<<"      ";
		gotoxy(ObjectX[ind], ObjectY[ind]+3);
		cout<<"      ";
		gotoxy(ObjectX[ind], ObjectY[ind]+4);
		cout<<"      ";
	}
}
void resetObject(int ind){   // resting an object
	eraseObject(ind); //Calls eraseObject(ind) to clear the current object.
	ObjectY[ind] = 4; //Resets ObjectY[ind] to 4 and generates a new position using genObject(ind).
	genObject(ind);

}

//Generates bullets at the position of the ship. The bullets are stored in an array, and bIndex is used to keep track of the bullets.
void genBullet(){   //To increase the bullet generation area in console game,
	bullets[bIndex][0] = 25;  // // Initial Y position  windows height minus ship height
	bullets[bIndex][1] = ShipPos; //  Bullet position based on ship's position
	bullets[bIndex][2] = 25;   //Initial Y position for the second bullet
	bullets[bIndex][3] = ShipPos+4;  //Adjust X position for the second bullet
	bIndex++;
	if( bIndex == 10)  //windows height minus ship height
		bIndex = 0;
}
void moveBullet(){ //Moves the bullets upwards on the screen by decreasing their Y-coordinate. If the bullet goes off the screen, it resets the position to 0.
	for(int i=0; i<20; i++){      //Decreases the Y-position of each bullet to simulate upward movement.
		if( bullets[i][0] > 2 )   //Resets the position if the bullet goes off the screen.
			bullets[i][0]--;
		else
			bullets[i][0] = 0;

		if( bullets[i][2] > 2 )
			bullets[i][2]--;
		else
			bullets[i][2] = 0;
	}
}
//Draws all the bullets currently on the screen based on their positions stored in the bullets array.
void drawBullets(){ //draw bullets accoding to rocket position
	for(int i=0; i<20; i++){
		if( bullets[i][0] > 1){  //Uses gotoxy to move the cursor to each bullet's position and prints a '^' to represent the bullet.
			gotoxy(bullets[i][1],bullets[i][0]); cout<<"^";
			gotoxy(bullets[i][3],bullets[i][2]); cout<<"^";
		}
	}
}
void eraseBullets(){ //erase each drawn bullets using empty blanks
	for(int i=0; i<20; i++){
		if( bullets[i][0] >= 1 ){
			gotoxy(bullets[i][1],bullets[i][0]); cout<<" ";
			gotoxy(bullets[i][3],bullets[i][2]); cout<<" ";
		}
	}
}
void eraseBullet(int i){//Erases the bullets by overwriting them with spaces.
	gotoxy(bullets[i][1],bullets[i][0]); cout<<" ";
	gotoxy(bullets[i][3],bullets[i][2]); cout<<" ";
}
void drawShip(){ //create rocket ship according to ship position
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+ShipPos, i+25); cout<<Ship[i][j]; //Iterates through the 2D array Ship and uses gotoxy to draw the ship at ShipPos.
		}
	}
}
void eraseShip(){ //erase drwn ship according to left-right movements, useing empty blanks
	for(int i=0; i<3; i++){
		for(int j=0; j<5; j++){
			gotoxy(j+ShipPos, i+25); cout<<" ";
		}
	}
}

int collision(){  // use 2D array matching to get collion to according to ship position
    for(int i = 0; i < 3; i++){  //Compares the positions of the ship and objects using their X and Y coordinates.
        if( ObjectY[i] + 4 >= 25 ){  // Adjusted to match ship's Y position
            if( ObjectX[i] + 4 >= ShipPos && ObjectX[i] <= ShipPos + 4 ){
                return 1;  // Collision detected
            }
        }
    }
    return 0;  // No collision
}

int bulletHit(){//  function for mapping bullets and object using XY based 2D arrays 
	for(int i=0; i<20; i++){
		for(int j=0; j<4; j+=2){  //If a bullet hits an object, it erases the bullet, resets the object, and returns 1.
			if( bullets[i][j] != 0 ){
				if( bullets[i][j] >= ObjectY[0] && bullets[i][j] <= ObjectY[0]+4 ){
					if( bullets[i][j+1] >= ObjectX[0] && bullets[i][j+1] <= ObjectX[0]+4 ){
						eraseBullet(i);     
						bullets[i][j] = 0;
						resetObject(0);
						return 1;
					}
				}
				if( bullets[i][j] >= ObjectY[1] && bullets[i][j] <= ObjectY[1]+4 ){
					if( bullets[i][j+1] >= ObjectX[1] && bullets[i][j+1] <= ObjectX[1]+4 ){
						eraseBullet(i);
						resetObject(1);
						bullets[i][j] = 0;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
void gameover(){ // function for represent game over screen

    Beep(6059,80);

    system("cls");
    system("color 4F");
    char ch;                //Plays a beep sound, clears the screen, and displays the game over message.
	cout<<endl;
	cout << endl;
    gotoxy(45, 9);cout<<"......Unfortunately......";
    gotoxy(46, 10);cout<<"Your Rocket is Destroyed";
    gotoxy(44, 11);cout << "___________________________" ;


	gotoxy(45,14);
	cout<<"Your score :"<<score<<endl;
	gotoxy(45,18);
	cout << "Retry?(y/n) = "; //Asks the player if they want to retry and calls interface2() if they do.
    cin >> ch;
    ch=tolower(ch);
    if(ch=='y')
    {
        interface2();

    }

    else if(ch=='n'){
    drawRocketBlasting(); 
}
}


void drawRocketBlasting() {  //function for drawing ascii art for exit screen 
    system("cls");
    system("color 0B");

    gotoxy(19, 5);cout << "               /\\" << endl;
    gotoxy(19, 6);cout << "              /  \\" << endl;
    gotoxy(19, 7);cout << "     ^  ^    /    \\" << endl;
    gotoxy(19, 8);cout << "    / \\/ \\  /\\" << endl;
    gotoxy(19, 9);cout << "  <       >  |    |" << endl;
    gotoxy(19, 10);cout << "    \\     /  |    |" << endl;
    gotoxy(19, 11);cout << "    |    |" << endl;
    gotoxy(19, 12);cout << "    ||" << endl;
    gotoxy(19, 13);cout << "    |    |" << endl;
    gotoxy(19, 14);cout << "    |    |" << endl;
    gotoxy(19, 15);cout << "   /| |  |\\  " << endl;
    gotoxy(19, 16);cout << "  / | |  | \\ "<< endl;
    gotoxy(19, 17);cout << "   ======= "<< endl;
    gotoxy(19, 18);cout << "      ||  "<< endl;
    gotoxy(19, 19);cout << "      ||  "<< endl;
    gotoxy(19, 20);cout << "      ||  "<< endl;
    gotoxy(19, 21);cout << "     /||\\  "<< endl;
    gotoxy(19, 22);cout << "    / || \\ " << endl;
    gotoxy(19, 23);cout << "   /  ||  \\" << endl;
    gotoxy(19, 24);cout << "  /   ||   \\" << endl;
    gotoxy(19, 25);cout << "      ||" << endl;
    gotoxy(19, 26);cout << "      ||" << endl;
    gotoxy(19, 27);cout << "      ||" << endl;
    gotoxy(19, 28);cout << "     /  \\" << endl;
    gotoxy(19, 29);cout << "    /    \\" << endl;
    gotoxy(19, 30);cout << "                      /      \\" << endl;
 gotoxy(32, 13);cout << "   ||||||   |||||  |||    ||| |||||||      |||||   ||    || |||||||  |||||  ";
 gotoxy(32, 14);cout << "  ||       ||   || ||||  |||| ||          ||    || ||    || ||      ||   || ";
 gotoxy(32, 15);cout << "  ||  |||| ||||||| || |||| || |||||       ||    || ||    || |||||   |||||   ";
 gotoxy(32, 16);cout << "  ||    || ||   || ||  ||  || ||          ||    ||  ||  ||  ||      ||   || ";
 gotoxy(32,17);cout << "   ||||||  ||   || ||      || |||||||      |||||     ||||   ||||||| ||   || ";

    
    
    getch();

    
}
void updateScore(){  // acceccing create file for read high scores
	gotoxy(WIN_WIDTH+7, 10);
	cout<<"Your score: "<<score<<endl;

     Beep(700,80);

}
void instructions(){

	system("cls");
    gotoxy(43,9);
	system("color E0");
	cout<<"INSTRUCTION";
	gotoxy(30,2);cout<<"------------------------------";
	gotoxy(30,4);cout<<"KEY BORAD CONTROLS ";
	gotoxy(30,6);cout<<"Shooting   - Shift key      ";
	gotoxy(30,7);cout<<"Move Left  - Lest Arrow Key ";
	gotoxy(30,8);cout<<"Move Right - Right Arrow Key";
	gotoxy(30,9);cout<<"------------------------------";
	gotoxy(30,11);cout<<"PLAYER MODES ";
	gotoxy(30,13);cout<<"o Campaign Mode  - Player has already 5 Ship Strengths to play";
	gotoxy(30,14);cout<<"                  one collision reduce 1 Strength, successful bullet hit add one point";
	gotoxy(30,15);cout<<"                  when strength is 0 game will over";
	gotoxy(30,17);cout<<"o Time Based Mode - Player time is limited to strength timer";
	gotoxy(30,18);cout<<"                    You have to get more bullets hits to Win !";
	gotoxy(30,19);cout<<"                    when strength is 0 game will over";
	gotoxy(30,23);cout<<"Press any key to go back to menu";
	while(getch()){
		Beep(1225,105);
		interface2();
	};
}

void credits(){  //our team member details

	system("cls");
    gotoxy(43,9);
	system("color E0");
	cout<<"PROJECT GROUP 11";
	gotoxy(43,10);
	cout<<"----------------";
	gotoxy(41,12);
	cout<<"1. IM/2022/025  -   Ashan   ";
	gotoxy(41,13);
	cout<<"2. IM/2022/024  -   Nirasha ";
	gotoxy(41,14);
	cout<<"3. IM/2022/112  -   Tharindu";
	gotoxy(41,15);
	cout<<"4. IM/2022/111  -   Gihan   ";
	gotoxy(41,17);
	cout<<"Press any key to go back to menu";
	while(getch()){
	Beep(1225,105);	//1458hz
	interface2();
	};
}
void interface1() {   // user interface 1
    system("cls");
    system("color 0C");
    
	gotoxy(5,5); cout<<"                888888888     88888888888            888               888888888     8888888888888              "<<endl;                                                         
	gotoxy(5,6); cout<<"               88888888888    888888888888          88888             88888888888    8888888888888              "<<endl;
	gotoxy(5,7); cout<<"              888             888        88        888 888          888              888                        "<<endl;
	gotoxy(5,8); cout<<"             888              888        88       888   888        888               888                        "<<endl;
	gotoxy(5,9); cout<<"             8888888888       888888888888       888     888       888               8888888888888              "<<endl;
	gotoxy(5,10);cout<<"              8888888888      88888888888       8888888888888      888               8888888888888              "<<endl;
	gotoxy(5,11);cout<<"                     888      888              888888888888888     888               888                        "<<endl;
	gotoxy(5,12);cout<<"                    888       888             888           888     888              888                        "<<endl;
	gotoxy(5,13);cout<<"           88888888888        888            888             888     88888888888     8888888888888              "<<endl;
	gotoxy(5,14);cout<<"            888888888         888           888               888     888888888      8888888888888              "<<endl;
	
	gotoxy(1,15);cout<<"                          eeeeee                                                                        ee                  "<<endl;
	gotoxy(1,16);cout<<"                         eeeeeeee                                      ee                               ee                  "<<endl;
	gotoxy(1,17);cout<<"                        ee         ee    ee   ee   ee  ee        ee        ee        ee   eeeeeee       ee                  "<<endl;
	gotoxy(1,18);cout<<"                        eeeeeeee   ee    ee   ee ee     ee      ee     ee   ee      ee          ee      ee                  "<<endl;
	gotoxy(1,19);cout<<"                          eeeeee   ee    ee   eeee       ee    ee      ee    ee    ee      eeeeeee      ee                  "<<endl;
	gotoxy(1,20);cout<<"                             ee    ee    ee   ee          ee  ee       ee     ee  ee      ee    ee      ee                  "<<endl;
	gotoxy(1,21);cout<<"                      eeeeeeee     eeeeeeee   ee           eeee        ee      eeee       ee    ee      ee                  "<<endl;
	gotoxy(1,22);cout<<"                       eeeeee       eeeeee    ee            ee         ee       ee         eeeeee       ee                  "<<endl;
	
    gotoxy(35, 25);
    cout << ">>....Press Space key to start Rocket Engine....<< ";
    int a= getch();
	if (a==32)
	 {    // this line to check for keyboard input
        Beep(1459,105);
		interface2();
    }
    else{
	system("cls");
    gotoxy(45, 6);
    cout<<"YOU ARE NOT SURVIVED IN SPACE"<<endl;
	}
} 
void interface2(){   // user interface 2
		do{
		system("cls");
		system("color 06");  //system(colour XY)  X-Background , Y-Forground
		gotoxy(43,9); cout<<" --------------------- ";
		gotoxy(43,10); cout<<" |    SPACE SURVIVAL  |     ";
		gotoxy(43,11); cout<<" ---------------------";
		gotoxy(45, 13);
        cout << "1. START GAME";
        gotoxy(45, 15);
        cout << "2. INSTRUCTIONS";
        gotoxy(45, 17);
        cout << "3. CREDITS";
        gotoxy(45, 19);
        cout << "4. QUIT";
        gotoxy(45, 21);
        cout << "Select an Option- ";
		char op = getch();

		if( op=='1')
        {
             Beep(1459,105);
             playerInfo(); // program flow pass to interface2()
        }
		else if( op=='2')
        {
             Beep(1459,105);
             instructions();
        }
        else if( op=='3')
        {
             Beep(1459,105);
             credits();
        }
		else if( op=='4')
            {
            Beep(1459,105);
            quitWindow();
           
        }



	}while(1);
}
void playerInfo(){ 
          
		system("cls");
		system("color F5");  //system(colour XY)  X-Background , Y-Forground
	    
	gotoxy(15,2); cout<<"  ------------------------------------------------------------------------ ";
    gotoxy(15,4);cout << "      _____         _  __-__-__-__-__-__-__-__-__-__-__-__-__-__                 " << endl;
    gotoxy(15,5);cout << "     /     \\    _  | |/                                         \\  " << endl;
    gotoxy(15,6);cout << "    | () () |  | |  - |   Wellcome ! to the onboard Astronut    |" << endl;
    gotoxy(15,7);cout << "     \\  ^  /    -     \\Please Enter Your Name to Begin Adventure/" << endl;
    gotoxy(15,8);cout << "      |||||            \\__-__-__-__-__-__-__-__-__-__-__-__-___/                  " << endl;
    gotoxy(15,9);cout << "      |||||" << endl;
    gotoxy(15,10);cout << "  -------------" << endl;
    gotoxy(15,11);cout << " /  |   ||   |  \\" << endl;
    gotoxy(15,12);cout << "|   |   ||   |   |" << endl;
    gotoxy(15,13);cout << " \\ |___||___|  //" << endl;
    gotoxy(15,14);cout << "       |  |" << endl;
    gotoxy(15,15);cout << "       |  |" << endl;
    gotoxy(15,16);cout << "       /  \\ " << endl;
    gotoxy(15,17);cout << "      /    \\" << endl;
    gotoxy(38,11); cout<<" Enter Here : ";
    cin>>playerName;
	
    interface3();
    }
      
void interface3(){     //user interface 3
	system("cls");
    system("color 0B");
    gotoxy(43,9); cout<<" --------------------- ";
    gotoxy(43,10); cout<<" |  SELECT GAME TYPE  |     ";
    gotoxy(43,11); cout<<" ---------------------";
    gotoxy(45, 13); cout << "1. Campaign"; //level based game play
    gotoxy(45, 15); cout << "2. time based"; // play in specific time period
    gotoxy(45, 17); cout << "3. Go to back";
    gotoxy(45, 19); cout << "Select an Option- ";
    char input= getch();                        //initialize input variable for key board input
    
    	if( input=='1')
        {
             Beep(1459,105);
             playCampaign(); // program flow pass to interface2()
        }
		else if( input=='2')
        {
             Beep(1459,105);
             playTimeBased();
        }

		else if( input=='3')
            {
            system("cls");
            system("color 1");
            Beep(1225,105);
            interface2();
        }
    
}

void quitWindow(){
    system("cls");
    system("color 0F");

	    gotoxy(15,8);cout << "     .oooooo.                              .o8       oooooooooo.                        .o. \n";
		gotoxy(15,9);cout << "    d8P'  `Y8b                             888       `888'   `Y8b                       888 \n";
		gotoxy(15,10);cout << "   888            .ooooo.   .ooooo.   .oooo888        888     888 oooo    ooo  .ooooo.  888 \n";
		gotoxy(15,11);cout << "   888           d88' `88b d88' `88b d88' `888        888oooo888'  `88.  .8'  d88' `88b Y8P \n";
		gotoxy(15,12);cout << "   888     ooooo 888   888 888   888 888   888        888    `88b   `88..8'   888ooo888 `8' \n";
		gotoxy(15,13);cout << "   `88.    .88'  888   888 888   888 888   888        888    .88P    `888'    888    .o .o. \n";
		gotoxy(15,14);cout << "    `Y8bood8P'   `Y8bod8P' `Y8bod8P' `Y8bod88P       o888bood8P'      .8'     `Y8bod8P' Y8P \n";
		gotoxy(15,15);cout << "                                                                  .o..P'                    \n";
		gotoxy(15,16);cout << "                                                                  `Y8P'                     \n";
		gotoxy(55,19);cout << "Have a nice day ! ";
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
		cout<<endl;
	
		exit(0);
	}


void playCampaign(){   // initializing game campaign functions

    system("cls");
    system("color 0E");

	ShipPos = 10 + WIN_WIDTH/2; // win width is predefined value in above
	score = 0;
	ObjectFlag[0] = 1;     
	ObjectFlag[1] = 1;
	ObjectY[0] = ObjectY[1] = 1;
    int shipLives = 5; //asign ship starting strengeth 
	for(int i=0; i<20; i++){
		bullets[i][0] = bullets[i][1] = 0;
	}

	system("cls");
	drawBorder();

	updateScore();
	genObject(0);
	genObject(1);
	genObject(2);
	gotoxy(36, 13);cout<<"Press any key to start";                            
	getch();
	gotoxy(36, 13);cout<<"                      ";

	while(1){                                                    //        all ship movements
		if(kbhit()){
			char ch = getch();
			if( ch==75 ){
				if( ShipPos > 26 )
					ShipPos -= 5;  //ship left align   
			}
			if( ch==77){
				if( ShipPos <85 )                               //shit movement controll right
					ShipPos += 5; // ship right align
			}
			if(ch==32){
				genBullet();    // press shift for relese bullets
				//drawBullets();

			}
			if(ch==27){  //  press key for release bullets
				break;
			}
		}

		drawShip();     
		drawObject(0);
		drawObject(1);
		drawObject(2);
		drawBullets();
		
		if( collision() == 1  ){
			Beep(1459,105);//  500,80
            shipLives -= 1;  // Decrease ship's lives on collision

	    if (shipLives <= 0) {  // Check if lives are exhausted
				gameover();
				return;
			}
		
		}
		if(  bulletHit() == 1 ){
			Beep(1459,105);
			score++;
	        updateScore();
		}
		gotoxy(WIN_WIDTH+7, 8);cout<<"| "<<playerName<<" Performance | ";
		gotoxy(WIN_WIDTH+7, 12);cout<<"Rocket Strength : "<<shipLives;	
		Sleep(123);//108

		eraseShip();
		eraseObject(0);
		eraseObject(1);

		eraseBullets();
		moveBullet();

		if( ObjectFlag[0] == 1 )
			ObjectY[0] += 1;

		if( ObjectFlag[1] == 1 )
			ObjectY[1] += 1;

		if( ObjectY[0] > SCREEN_HEIGHT-4 ){
			resetObject(0);
		}
		if( ObjectY[1] > SCREEN_HEIGHT-4 ){
			resetObject(1);
		}
	}
}

void playTimeBased(){   // play game in specific time period

    system("cls");
    system("color 0E");     
    int countdown = 1000 ;  // Set the countdown timer to in seconds

   
    
	ShipPos = 10 + WIN_WIDTH/2;
	score = 0;
	ObjectFlag[0] = 1;
	ObjectFlag[1] = 1;
	ObjectY[0] = ObjectY[1] = 1;

	for(int i=0; i<20; i++){
		bullets[i][0] = bullets[i][1] = 0;
	}

	system("cls");
	drawBorder();

	updateScore();
	genObject(0);
	genObject(1);
	genObject(2);

	gotoxy(WIN_WIDTH + 9, 13);cout<<"Control ";
	gotoxy(WIN_WIDTH + 9, 14);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 9, 15);cout<<"<- Key - Left";
	gotoxy(WIN_WIDTH + 9, 16);cout<<"-> Key - Right";

	gotoxy(36, 13);cout<<"Press any key to start";
	getch();
	gotoxy(36, 13);cout<<"                      ";
    
     // Start the timer
     
     while (countdown >= 0) {{          //start timer as energy / if use sleep function inside loop t0tal game will lag
        gotoxy(WIN_WIDTH+7, 8);cout<<"| "<<playerName<<" Performance | ";
    	gotoxy(WIN_WIDTH + 7, 19);cout << "Rocket energy left: " << endl;
        gotoxy(WIN_WIDTH + 7, 21);cout<<countdown<<" Watt Hours"<<endl;
        
        	if(kbhit()){
			char ch = getch();
			if( ch==75 ){
				if( ShipPos > 26 )
					ShipPos -= 5;  //ship right align
			}
			if( ch==77){
				if( ShipPos <85 )
					ShipPos += 5; // ship left align
			}
			if(ch==32){
				genBullet();    // press shift for relese bullets
				//drawBullets();

			}
			if(ch==27){  //  press key for release bullets
				break;
			}
		}

		drawShip();     
		drawObject(0);
		drawObject(1);
		drawObject(2);
		drawBullets();
		if( collision() == 1  ){
			gameover();
			return;
		}
		if(  bulletHit() == 1 ){
			score++;
			updateScore();
		}
		Sleep(108);

		eraseShip();
		eraseObject(0);
		eraseObject(1);

		eraseBullets();
		moveBullet();

		if( ObjectFlag[0] == 1 )
			ObjectY[0] += 1;   //used to fast the object moveing speed

		if( ObjectFlag[1] == 1 )
			ObjectY[1] += 1;   //used to fast the object moveing speed

		if( ObjectY[0] > SCREEN_HEIGHT-4 ){
			resetObject(0);              
		}
		if( ObjectY[1] > SCREEN_HEIGHT-4 ){
			resetObject(1);
		}
	}
	       // Wait for 1 second
       countdown--;  // Decrease the countdown by 1

        
}
	  gameover();  // End the game when time's up

}


