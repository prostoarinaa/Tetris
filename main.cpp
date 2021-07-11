#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


 
class Tetramino {
public:
    int M = 900; // высота игрового поля
    int N = 450; // ширина игрового поля
    int blockPositions[4];
    
    int field[20][10] ; // игровое поле
    struct Coordinates
        {
            int x;
            int y;
        };
    Coordinates massivOfCoordinates [4];
    int Сubes [7][4] {
        1,3,5,7, // I
        2,4,5,7, // S
        3,5,4,6, // Z
        3,5,4,7, // T
        2,3,5,7, // L
        3,5,7,6, // J
        2,3,4,5, // O
    };
    void MoveLeftRight(RenderWindow& window, int direction)
    {
            int x[4]{};
            int y[4]{};
                                         
            for (int i = 0; i < 4; i++)
            {
                y[i] = massivOfCoordinates[i].y;
                x[i] = massivOfCoordinates[i].x;
            }
                                                                                                             
            for (int i = 0; i < 4; i++)
            {
                massivOfCoordinates[i].x += direction;
            }
    }
            
    void CreateTetramino(int num, RenderWindow & window, Sprite tetr, int dx, int flag){
       
         //   int dx = 0;
           
        int numOfTetramino = num, j;
        Coordinates massivOfCoordinates [4] = {};
        
      //  numOfTetramino = rand() % 7 ;
        //numOfTetramino = 1+ rand() % 7 ;
      //  j = numOfTetramino - 1;
        j = 6;
        numOfTetramino = 7;
        for (int i = 0; i < 4; i++)
        {
            blockPositions[i] = Сubes[j][i];
           // cout << "blocpozition="<<
        }
     //  if ()  {
        cout << "massiv= "<< massivOfCoordinates[0].x<< " "<<massivOfCoordinates[0].y<< endl;
      //  if(massivOfCoordinates[0].x==2 && massivOfCoordinates[0].y==1){
        for (int i = 0; i < 4; i++)
        {
           // flag +=1;
            massivOfCoordinates[i].x = blockPositions[i] % 2 +7 ;
            
            massivOfCoordinates[i].y = blockPositions[i] / 2+5;
        }
     //  }
        if ( dx != 0){
            for (int i = 0; i < 4; i++) massivOfCoordinates[i].x += dx;
        }
         
                //int n = 3;*/
        for (int i = 0; i < 4; i++)
                {
                    tetr.setTextureRect(IntRect(numOfTetramino * 45, 0, 45, 45));
                    tetr.setPosition(massivOfCoordinates[i].x * 45, massivOfCoordinates[i].y * 45);
                    window.draw(tetr);
                }
        
        
        
    };
    
};

void tetris(RenderWindow & window){
    bool isGame = true;
    int num = 0;
    Tetramino tetramino;
    int flag=0;
    
    Image texBGimage, texExit, tetrisCubes;
    texBGimage.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/BG.png");
    texExit.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/exitrules.png");
    tetrisCubes.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/tetris.png");
    
    Texture texBG, texEX, texTetrisCubes;
    texBG.loadFromImage(texBGimage);
    texEX.loadFromImage(texExit);
    texTetrisCubes.loadFromImage(tetrisCubes);
    vector<Sprite> vectorOfCubes[8];
    Sprite playBG(texBG), playEXIT(texEX), playTETRISCUBES(texTetrisCubes), playCUBE1(texTetrisCubes), playCUBE2(texTetrisCubes), playCUBE3(texTetrisCubes), playCUBE4(texTetrisCubes), playCUBE5(texTetrisCubes), playCUBE6(texTetrisCubes), playCUBE7(texTetrisCubes), playCUBE8(texTetrisCubes);
    playBG.setPosition(0,0);
    playEXIT.setPosition(700,880);
    playTETRISCUBES.setPosition(0,0);
    
    playCUBE1.setTextureRect(IntRect(0, 0, 45, 45));
    playCUBE2.setTextureRect(IntRect(45, 0, 45, 45));
    playCUBE3.setTextureRect(IntRect(90, 0, 45, 45));
    playCUBE4.setTextureRect(IntRect(135, 0, 45, 45));
    playCUBE5.setTextureRect(IntRect(180, 0, 45, 45));
    playCUBE6.setTextureRect(IntRect(225, 0, 45, 45));
    playCUBE7.setTextureRect(IntRect(270, 0, 45, 45));
    playCUBE8.setTextureRect(IntRect(315, 0, 45, 45));
    
    vector < Sprite > vectorPlayCUBES;
    vectorPlayCUBES.push_back(playCUBE1);
    vectorPlayCUBES.push_back(playCUBE2);
    vectorPlayCUBES.push_back(playCUBE3);
    vectorPlayCUBES.push_back(playCUBE4);
    vectorPlayCUBES.push_back(playCUBE5);
    vectorPlayCUBES.push_back(playCUBE6);
    vectorPlayCUBES.push_back(playCUBE7);
    vectorPlayCUBES.push_back(playCUBE8);
    
    /*
    playCUBE1.setPosition(0,0);
    playCUBE2.setPosition(45,0);
    playCUBE3.setPosition(90,0);
    playCUBE4.setPosition(135,0);
    playCUBE5.setPosition(180,0);
    playCUBE6.setPosition(225,0);
    playCUBE7.setPosition(270,0);
    playCUBE8.setPosition(315,0);
    */
    while (isGame) {
        Event event;
        int dx = 0;
        while (window.pollEvent( event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
             {
            // Эта кнопка – стрелка влево?
            if (event.key.code == sf::Keyboard::Left)
            {
                dx = -1;
            }
                 // Или стрелка вправо?
            if (event.key.code == sf::Keyboard::Right)
            {
                dx = 1;
            }
            
        }
        playEXIT.setColor(Color::White);
        if (IntRect(700, 880, 219, 59).contains(Mouse::getPosition(window))) {
            playEXIT.setColor(Color(249, 131, 101));
            
        }
        if ((Mouse::isButtonPressed(Mouse::Left)) &&((IntRect(700, 880, 219, 59).contains(Mouse::getPosition(window)))))
            isGame = 0;
        window.clear();
        
       
        window.draw(playBG);
        window.draw(playEXIT);
        tetramino.CreateTetramino(num, window, playCUBE1 , dx, flag);
      /*  window.draw(playCUBE1);
        window.draw(playCUBE2);
        window.draw(playCUBE3);
        window.draw(playCUBE4);
        window.draw(playCUBE5);
        window.draw(playCUBE6);
        window.draw(playCUBE7);
        window.draw(playCUBE8);*/
        window.display();
        
    }
}
}
/*  if (event.type == Event::KeyPressed)
 {
// Эта кнопка – стрелка влево?
     if (event.key.code == sf::Keyboard::Left)
     {
         tetramino.moveHoriz(window, -1);
     }
     // Или стрелка вправо?
      if (event.key.code == sf::Keyboard::Right)
     {
         tetramino.moveHoriz(window, 1);
     }
    // Или может стрелка вверх?
     else if (event.key.code == sf::Keyboard::Up)
     {
         tetramino.rotate();
     }
 } */
int main()
{
    int menuNum = 0, menuNumExit = 0;
    bool isMenu = 1;
    RenderWindow window(VideoMode(1024, 1024), "TETRIS");
    
    Image tex1image, tex2image, tex3image, texBackGroundimage, texRulesimage, texExitimage;
    tex1image.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/play.png");
    texRulesimage.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/texrules.png");
    texExitimage.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/exitrules.png");
    tex2image.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/rules.png");
    tex3image.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/exit.png");
    texBackGroundimage.loadFromFile("/Users/pk/Desktop/ццц/tetriss/images/background.png");
    
    Texture tex1, tex2, tex3, texBG, texRules, texExitRules;
    tex1.loadFromImage(tex1image);
    texRules.loadFromImage(texRulesimage);
    texExitRules.loadFromImage(texExitimage);
    tex2.loadFromImage(tex2image);
    tex3.loadFromImage(tex3image);
    texBG.loadFromImage(texBackGroundimage);
    
    Sprite menuPlay(tex1), menuRulesRules(texRules), menuRules(tex2), menuExit(tex3), menuBG(texBG), menuExitRules(texExitRules);
    menuPlay.setPosition(262,420);
    menuRulesRules.setPosition(0,0);
    menuRules.setPosition(262,620);
    menuExit.setPosition(262,820);
    menuExitRules.setPosition(400,920);
    menuBG.setPosition(0,0);
    

    while (window.isOpen()) {
        menuPlay.setColor(Color::White);
        menuRules.setColor(Color::White);
        menuExit.setColor(Color::White);
      
        Event event;
        while (window.pollEvent( event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        menuNum = 0;
        if (IntRect(262, 420, 501, 135).contains(Mouse::getPosition(window))) {
            menuPlay.setColor(Color(249, 131, 101)); menuNum = 1;
        }
        if (IntRect(262, 620, 501, 135).contains(Mouse::getPosition(window))) {
            menuRules.setColor(Color(249, 131, 101)); menuNum = 2;
          
        }
        if (IntRect(262, 820, 501, 135).contains(Mouse::getPosition(window))) {
            menuExit.setColor(Color(249, 131, 101));
            menuNum = 3;
        }
        if (IntRect(400, 920, 219, 59).contains(Mouse::getPosition(window))) {
            menuExit.setColor(Color(249, 131, 101));
            menuNumExit = 4;
        }
        bool flag = 0;
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            flag = 0;
            if (menuNum == 1) {
                isMenu = false;
               tetris(window);
            }
            if (menuNum == 2) {
                do {

                        window.draw(menuRulesRules);
                        window.draw(menuExitRules);
                        window.display();
                    
                 /*////////////// тут пыталсь сделать по нажатию на кнопку exit /////////////
                  if (((Mouse::isButtonPressed(Mouse::Left)))&&(IntRect(400, 920, 219, 59).contains(Mouse::getPosition(window))))
                    {
                        flag = 1;
                       // window.display();
                    }
                } while (flag != 1);
                */
                    
                    
                } while(!Keyboard::isKeyPressed(Keyboard::Escape));
           }
            if (menuNum == 3)  { window.close(); isMenu = false; }
        }
        window.clear();
        window.draw(menuBG);
        window.draw(menuPlay);
        window.draw(menuRules);
        window.draw(menuExit);
        window.display();
    }
    return 0;

}

