
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

  int M = 20; // высота игрового поля
  int N = 10; // ширина игрового поля
 
  int points {0};
  int points2 {0};
  int field[20][10] = {}; // игровое поле
  int field2[20][10] = {};

  int Сubes [7][4] {
      1,3,5,7, // I
      2,4,5,7, // S
      3,5,4,6, // Z
      3,5,4,7, // T
      2,3,5,7, // L
      3,5,7,6, // J
      2,3,4,5, // O
  };

class Tetramino {
    public:
    
        int M = 20;
        int N = 10;
        int n, m;
      
        int blockCoordinate[4];
        int blockCoordinate2[4];
    
        struct Coordinates {
              int x;
              int y;
        };
    
        Coordinates massivOfCoordinates [4] = {};
        Coordinates massivOfCoordinates2 [4] = {};
        Coordinates massiv2OfCoordinates [4] = {};
        Coordinates massiv2OfCoordinates2 [4] = {};
    
        int Сubes [7][4] {
          1,3,5,7, // I
          2,4,5,7, // S
          3,5,4,6, // Z
          3,5,4,7, // T
          2,3,5,7, // L
          3,5,7,6, // J
          2,3,4,5, // O
        };
    
        bool checkThePosition();
        bool checkThePosition2();
        int checkLastString (int& points);
        int checkLastString2 (int& points2);
        void rotateTetramino();
        void rotateTetramino2();
        void createTetramino();
        void createTetramino2();
        void drawTetramino(RenderWindow& window, Sprite& playCUBE1);
        void drawTetramino2(RenderWindow& window, Sprite& playCUBE1);
        void moveDown(RenderWindow& window, Sprite& playCUBE1);
        void moveDown2(RenderWindow& window, Sprite& playCUBE1);
        void gameRunning(RenderWindow& window,float delay11, float delay12,float delay21, float delay22, bool flaghotlevel,bool flagPair);
        void moveTetraminoLeftOrRight(RenderWindow& window, int vector) ;
        void moveTetraminoLeftOrRight2(RenderWindow& window, int vector) ;
        bool check_finish_game();
    
    
        bool playTetris2(RenderWindow& window,float delay11, float delay12, float delay21, float delay22, bool flaghotlevel, bool flagPair){
        bool isGame = true;
        
        Tetramino tetramino, tetramino2;

        Image texBGimage, texBGimage2, tetrisCubes, Back,Back2;
        texBGimage.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/BG.png");
        texBGimage2.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/BG2.png");
        tetrisCubes.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/tetris.png");
        Back.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/back.png");
        Back2.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/back2.png");
        
        Texture texBG,texBG2, texTetrisCubes, texBack,texBack2;
        texBG.loadFromImage(texBGimage);
        texBG2.loadFromImage(texBGimage2);
        texTetrisCubes.loadFromImage(tetrisCubes);
        texBack.loadFromImage(Back);
        texBack2.loadFromImage(Back2);

        Sprite playBG(texBG),playBG2(texBG2), playTETRISCUBES(texTetrisCubes), playCUBE1(texTetrisCubes),playCUBE2(texTetrisCubes), playBack(texBack),playBack2(texBack2);
        playBG.setPosition(0,0);
        playBG2.setPosition(0,0);
        playTETRISCUBES.setPosition(0,0);
    
        playBack.setPosition(650, 750);
        playBack2.setPosition(910, 920);
        playCUBE1.setTextureRect(IntRect(0, 0, 45, 45));
        playCUBE2.setTextureRect(IntRect(0, 0, 45, 45));
            
        float timer = 0,timer2 = 0, delay1 = delay11, delay2 = delay12;
        
        Music music;
        music.openFromFile("/Users/pk/Desktop/Tetris/tetriss/music/background.ogg");
        music.setLoop(true);
        music.play();
        
        tetramino.createTetramino();
        if (flagPair == 1) tetramino2.createTetramino2();
            
        Clock clock, clock2;
        while (isGame) {
            window.clear();
            if (flagPair == 0) {
                window.draw(playBG);
                window.draw(playBack);
            }
            else {
                window.draw(playBG2);
                window.draw(playBack2);
            }
           
            if (check_finish_game()) {
                Image imgame, imgame1, imgame2;
                
                imgame.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/gameover.png");
                imgame1.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/1stwon.png");
                imgame2.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/2ndwon.png");
                Texture texGameOver,texGameOver1,texGameOver2 ;
                texGameOver.loadFromImage(imgame);
                texGameOver1.loadFromImage(imgame1);
                texGameOver2.loadFromImage(imgame2);
                Sprite playGameOver(texGameOver),playGameOver1(texGameOver1),playGameOver2(texGameOver2);
                delay1 = 1000;
                delay2 = 1000;
                if (flagPair == 0) {
                    playGameOver.setPosition(460,340);
                    window.draw(playGameOver);
                }
                else {
                    playGameOver1.setPosition(150,430);
                    playGameOver2.setPosition(160,119);
                    if (points < points2){
                        window.draw(playGameOver2);}
                    else
                        window.draw(playGameOver1);
                }
            }
            
            double time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            if (flagPair == 1) {
                double time2 = clock2.getElapsedTime().asSeconds();
                clock2.restart();
                timer2 += time2;
            }
            
            Event event;
           
            while (window.pollEvent( event)) {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Left) {
                        tetramino.moveTetraminoLeftOrRight(window, -1);
                    }
                    if (event.key.code == Keyboard::Right) {
                        tetramino.moveTetraminoLeftOrRight(window, 1);
                    }
                    if (event.key.code == Keyboard::Up) {
                            tetramino.rotateTetramino();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Down))
                        delay1 = delay21;
                    if (flagPair == 1) {
                        if (event.key.code == Keyboard::W) {
                            tetramino2.rotateTetramino2();
                    }
                    if (event.key.code == Keyboard::D) {
                        tetramino2.moveTetraminoLeftOrRight2(window, 1);
                    }
                    if (event.key.code == Keyboard::A) {
                        tetramino2.moveTetraminoLeftOrRight2(window, -1);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::S))
                        delay2 = delay22;
                        
                    }
                }
            }

            
            if (timer > delay1) {
                tetramino.moveDown(window, playCUBE1);
                timer = 0;
            }
            if (flagPair == 1) {
                if (timer2 > delay2) {
                    tetramino2.moveDown2(window, playCUBE2);
                    timer2 = 0;
                }
            }
            checkLastString(points);
            delay1 = delay11;
            
            if (flagPair == 1) {
                checkLastString2(points2);
                delay2 = delay12;
            }
            if (!check_finish_game()) {
                tetramino.drawTetramino(window, playCUBE2);
                if ( flagPair == 1) tetramino2.drawTetramino2(window, playCUBE2);
            }
            
            playBack.setColor(Color::White);
            playBack2.setColor(Color::White);

            if (IntRect(910, 920, 96, 90).contains(Mouse::getPosition(window))) {
                playBack2.setColor(Color(249, 131, 101));
            }
            if (IntRect(650, 750, 219, 59).contains(Mouse::getPosition(window))) {
                playBack.setColor(Color(249, 131, 101));
            }
            
            if ((Mouse::isButtonPressed(Mouse::Left)) && ((IntRect(910, 920, 96, 90).contains(Mouse::getPosition(window)))))
                isGame = 0;
            if ((Mouse::isButtonPressed(Mouse::Left)) && ((IntRect(650, 750, 219, 59).contains(Mouse::getPosition(window)))))
                isGame = 0;
            
            if (!check_finish_game()) {
                if (flaghotlevel == 1) {
                    for (int horiz = 0; horiz < M; ++horiz) {
                        for (int vert = 0; vert < N; ++vert) {
                            if (field[horiz][vert] == 0)
                                continue;
                            playCUBE1.setTextureRect(sf::IntRect(field[horiz][vert] * 45,
                        0, 45, 45));
                            playCUBE1.setPosition(vert * 45, horiz * 45);
                            window.draw(playCUBE1);
                        }
                    }
                }
                if (flagPair == 1) {
                    for (int horiz = 0; horiz < M; ++horiz) {
                        for (int vert = 0; vert < N; ++vert) {
                            if (field2[horiz][vert] == 0)
                                continue;
                            playCUBE2.setTextureRect(sf::IntRect(field2[horiz][vert] * 45,
                        0, 45, 45));
                            playCUBE2.setPosition(vert * 45 + 573, horiz * 45);
                            playCUBE2.move(0, 0);
                            window.draw(playCUBE2);
                        }
                    }
                }
            }
            
            
            Font font;
            font.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/Press-Start-2P/pressstart2p/PressStart2P-Regular.ttf");
            Text text, text2;
            text.setFont(font);
            text2.setFont(font);
            string userPointsString = to_string(points);
            string userPointsString2 = to_string(points2);
            text.setString(userPointsString);
            text2.setString(userPointsString2);
            text.setCharacterSize(70);
            text2.setCharacterSize(70);
            text.setFillColor(Color(36,36,36));
            text2.setFillColor(Color(36,36,36));
            
            if (flagPair == 1) {
                text.setPosition(470, 350);
                text2.setPosition(488, 580);
                window.draw(text);
                window.draw(text2);
            }
            else {
                text.setPosition(730, 230);
                window.draw(text);
            }
            window.display();
        }
        return false;
    }
};



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
 //   Field::field[10]
    int menuNum = 0;
    bool isMenu = 1;
    
    RenderWindow window(VideoMode(1024, 1024), "TETRIS");
    
    Image tex1image, tex2image, tex3image, texBackGroundimage, texRulesimage, texExitimage, lev1, lev2, lev3, play2x;
    tex1image.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/play.png");
    texRulesimage.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/texrules.png");
    texExitimage.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/back.png");
    tex2image.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/rules.png");
    tex3image.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/exit.png");
    texBackGroundimage.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/background.png");
    lev1.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/lev1.png");
    lev2.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/lev2.png");
    lev3.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/lev3.png");
    play2x.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/images/play2x.png");
    
    Texture texPlay, tex2, tex3, texBG, texRules, texExitRules,texlev1,texlev2,texlev3, texPlay2x;
    texPlay.loadFromImage(tex1image);
    texRules.loadFromImage(texRulesimage);
    texExitRules.loadFromImage(texExitimage);
    tex2.loadFromImage(tex2image);
    tex3.loadFromImage(tex3image);
    texBG.loadFromImage(texBackGroundimage);
    texlev1.loadFromImage(lev1);
    texlev2.loadFromImage(lev2);
    texlev3.loadFromImage(lev3);
    texPlay2x.loadFromImage(play2x);
    
    Sprite menuPlay(texPlay), menuRulesRules(texRules), menuRules(tex2), menuExit(tex3), menuBG(texBG), menuExitRules(texExitRules), play1(texlev1), play2(texlev2), play3(texlev3), menuPlay2x(texPlay2x);
    menuPlay.setPosition(262,520);
    menuRulesRules.setPosition(0,0);
    menuRules.setPosition(262,700);
    menuExit.setPosition(262,850);
    menuExitRules.setPosition(100,920);
    menuBG.setPosition(0,0);
    play1.setPosition(262,400);
    play2.setPosition(429,400);
    play3.setPosition(596,400);
    menuPlay2x.setPosition(490, 520);
    
    Tetramino tetramino1;
    while (window.isOpen()) {
        menuPlay.setColor(Color::White);
        menuPlay2x.setColor(Color::White);
        menuRules.setColor(Color::White);
        menuExit.setColor(Color::White);
        play1.setColor(Color::White);
        play2.setColor(Color::White);
        play3.setColor(Color::White);
        
        Event event;
        while (window.pollEvent( event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        menuNum = 0;
        
        if (IntRect(262, 520, 232, 169).contains(Mouse::getPosition(window))) {
            menuPlay.setColor(Color(249, 131, 101)); menuNum = 1;
        }
        if (IntRect(490, 520, 232, 169).contains(Mouse::getPosition(window))) {
            menuPlay2x.setColor(Color(249, 131, 101)); menuNum = 222;
        }
        if (IntRect(262, 700, 501, 135).contains(Mouse::getPosition(window))) {
            menuRules.setColor(Color(249, 131, 101)); menuNum = 2;
        }
        if (IntRect(262, 850, 501, 135).contains(Mouse::getPosition(window))) {
            menuExit.setColor(Color(249, 131, 101));
            menuNum = 3;
        }
        if (IntRect(262, 400, 129, 129).contains(Mouse::getPosition(window))) {
            play1.setColor(Color(249, 131, 101));
            menuNum = 11;
        }
        if (IntRect(429, 400, 129, 129).contains(Mouse::getPosition(window))) {
            play2.setColor(Color(249, 131, 101));
            menuNum = 12;
        }
        if (IntRect(596, 400, 129, 129).contains(Mouse::getPosition(window))) {
            play3.setColor(Color(249, 131, 101));
            menuNum = 13;
        }
        
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) {
                isMenu = false;
               tetramino1.gameRunning(window,0.3,0.3, 0.05, 0.05, 0, 0);
            }
            if (menuNum == 222) {
                isMenu = false;
               tetramino1.gameRunning(window,0.3,0.3, 0.05, 0.05, 1, 1);
            }
            if (menuNum == 11) {
                isMenu = false;
               tetramino1.gameRunning(window, 0.3, 0.3, 0.05 ,0.05, 1, 0);
            }
            if (menuNum == 12) {
                isMenu = false;
               tetramino1.gameRunning(window, 0.2, 0.2, 0.05, 0.005, 1, 0);
            }
            if (menuNum == 13) {
                isMenu = false;
               tetramino1.gameRunning(window, 0.1, 0.1, 0.005, 0.0005, 1, 0);
            }
            if (menuNum == 3) {
                window.close();
                isMenu = false;
            }
        }
        if (menuNum == 2 && Mouse::isButtonPressed(Mouse::Left)) {
            if (IntRect(200, 920, 219, 59).contains(Mouse::getPosition(window))) {
                menuExit.setColor(Color(249, 131, 101));
            }
          do  {
                    window.draw(menuRulesRules);
                    window.draw(menuExitRules);
                    
                    window.display();
          } while (!Mouse::isButtonPressed(Mouse::Left));
       }
        window.clear();
        window.draw(menuBG);
        window.draw(menuPlay);
        window.draw(menuRules);
        window.draw(menuExit);
        window.draw(play1);
        window.draw(play2);
        window.draw(play3);
        window.draw(menuPlay2x);
        
        window.display();
    }
    return 0;
}







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Tetramino::checkThePosition() {
  for (int i = 0; i < 4; i++)
    if (massivOfCoordinates[i].x < 0 || massivOfCoordinates[i].x >= 10 || massivOfCoordinates[i].y >= 20 ||massivOfCoordinates[i].y <= 0)
        return 0;
    else if (field[massivOfCoordinates[i].y][massivOfCoordinates[i].x])
        return 0;
  return 1;
};

bool Tetramino::checkThePosition2() {
  for (int i = 0; i < 4; i++)
    if (massivOfCoordinates2[i].x < 0 || massivOfCoordinates2[i].x >= 10 || massivOfCoordinates2[i].y >= 20 ||massivOfCoordinates2[i].y <= 0)
        return 0;
    else if (field2[massivOfCoordinates2[i].y][massivOfCoordinates2[i].x])
        return 0;
  return 1;
};

int Tetramino::checkLastString (int& points) {
    int k = M-1 ;
    for (int i = M-1 ; i > 0; i--) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (field[i][j]) {
                count++;
            }
            field[k][j] = field[i][j];
            //field[k][i].move(45,45);
        }
        if (count < N) {
            k--;
        }
        else {
            points += 1;
        }
    }
    return points;
};
int Tetramino::checkLastString2 (int& points2) {
    int k = M-1 ;
    for (int i = M-1 ; i > 0; i--) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (field2[i][j]) {
                count++;
            }
            field2[k][j] = field2[i][j];
        }
        if (count < N) {
            k--;
        }
        else {
            points2 += 1;
        }
    }
    return points2;
};

void Tetramino::rotateTetramino() {
    int timeCoordinatesX[4] = {};
    int timeCoordinatesY[4] = {};
    
    for (int i = 0; i < 4; i++) {
        timeCoordinatesY[i] = massivOfCoordinates[i].y;
        timeCoordinatesX[i] = massivOfCoordinates[i].x;
    }
    int centrX = massivOfCoordinates[1].x;
    int centrY = massivOfCoordinates[1].y;
                             
    for (int i = 0; i < 4; i++) {
        int y = massivOfCoordinates[i].y - centrY;
        int x = massivOfCoordinates[i].x - centrX;
        massivOfCoordinates[i].y = centrY + x;
        massivOfCoordinates[i].x = centrX - y;
    }
    ///////////////////
    for (int i = 0; i < 4; i++) {
        cout << "massiv1= "<< timeCoordinatesX[i]<< " "<<timeCoordinatesY[i]<< endl;
        cout << "massiv2= "<< massivOfCoordinates[i].x<< " "<<massivOfCoordinates[i].y<< endl;
    }
    ///////////////////
    if (!checkThePosition()) {
        for (int i = 0; i < 4; i++) {
            massivOfCoordinates[i].x = timeCoordinatesX[i];
            massivOfCoordinates[i].y = timeCoordinatesY[i]+1;
        }
    }
};

void Tetramino::rotateTetramino2() {
    int timeCoordinatesX[4] = {};
    int timeCoordinatesY[4] = {};
    
    for (int i = 0; i < 4; i++) {
        timeCoordinatesY[i] = massivOfCoordinates2[i].y;
        timeCoordinatesX[i] = massivOfCoordinates2[i].x;
    }
    int centrX = massivOfCoordinates2[1].x;
    int centrY = massivOfCoordinates2[1].y;
                             
    for (int i = 0; i < 4; i++) {
        int y = massivOfCoordinates2[i].y - centrY;
        int x = massivOfCoordinates2[i].x - centrX;
        massivOfCoordinates2[i].y = centrY + x;
        massivOfCoordinates2[i].x = centrX - y;
    }
    ///////////////////
    for (int i = 0; i < 4; i++) {
        cout << "massiv1= "<< timeCoordinatesX[i]<< " "<<timeCoordinatesY[i]<< endl;
        cout << "massiv2= "<< massivOfCoordinates[i].x<< " "<<massivOfCoordinates[i].y<< endl;
    }
    ///////////////////
    if (!checkThePosition2()) {
        for (int i = 0; i < 4; i++) {
            massivOfCoordinates2[i].x = timeCoordinatesX[i];
            massivOfCoordinates2[i].y = timeCoordinatesY[i]+1;
        }
    }
};

void Tetramino::createTetramino() {
    n = rand()%7 + 1;
    for (int i = 0; i < 4; i++) {
        blockCoordinate[i] = Сubes[n-1][i];
    }
    for (int i = 0; i < 4; i++) {
        massivOfCoordinates[i].x = blockCoordinate[i] % 2 + 4;
        massivOfCoordinates[i].y = blockCoordinate[i] / 2 + 1 ;
    }
};
void Tetramino::createTetramino2() {
    m = rand()%7 + 1;
    for (int i = 0; i < 4; i++) {
        blockCoordinate2[i] = Сubes[m-1][i];
    }
    
    for (int i = 0; i < 4; i++) {
        massivOfCoordinates2[i].x = blockCoordinate2[i] % 2 + 4;
        massivOfCoordinates2[i].y = blockCoordinate2[i] / 2 + 1 ;
    }
};

void Tetramino::gameRunning(RenderWindow& window,float delay11, float delay12, float delay21, float delay22, bool flaghotlevel, bool flagPair) {
    if (playTetris2(window, delay11, delay12,delay21, delay22, flaghotlevel,flagPair)) {
        gameRunning(window, delay11, delay12,delay21, delay22, flaghotlevel,flagPair);
    }
};

void Tetramino::drawTetramino(RenderWindow& window, Sprite& playCUBE1) {
    for (int i = 0; i < 4; i++) {
        playCUBE1.setTextureRect(sf::IntRect(n * 45, 0, 45, 45));
        playCUBE1.setPosition(massivOfCoordinates[i].x * 45, massivOfCoordinates[i].y * 45);
        window.draw(playCUBE1);
    }
};
void Tetramino::drawTetramino2(RenderWindow& window, Sprite& playCUBE2) {
    for (int i = 0; i < 4; i++) {
        playCUBE2.setTextureRect(sf::IntRect(m * 45, 0, 45, 45));
        playCUBE2.setPosition(massivOfCoordinates2[i].x * 45 + 573, massivOfCoordinates2[i].y * 45);
        window.draw(playCUBE2);
    }
};

void Tetramino::moveDown(RenderWindow& window, Sprite& playCUBE1) {
    int timeCoordinatesX[4] = {};
    int timeCoordinatesY[4] = {};
    SoundBuffer finishBuffer;//создаём буфер для звука
   finishBuffer.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/music/falled.ogg");//загружаем в него звук
    Sound finish(finishBuffer);
    
//    finish.play();
    for (int i = 0; i < 4; i++) {
        timeCoordinatesY[i] = massivOfCoordinates[i].y;
        timeCoordinatesX[i] = massivOfCoordinates[i].x;
    }
                            
    for (int i = 0; i < 4; i++) {
        massivOfCoordinates[i].y += 1;
    }
    if (!checkThePosition()) {
        finish.play();
        for (int i = 0; i < 4; i++) {
            massivOfCoordinates[i].y = timeCoordinatesY[i];
            field[timeCoordinatesY[i]][timeCoordinatesX[i]] = n;
        }
        createTetramino();
    }
};

void Tetramino::moveDown2(RenderWindow& window, Sprite& playCUBE2) {
    int timeCoordinatesX[4] = {};
    int timeCoordinatesY[4] = {};
    SoundBuffer finishBuffer;//создаём буфер для звука
   finishBuffer.loadFromFile("/Users/pk/Desktop/Tetris/tetriss/music/falled.ogg");//загружаем в него звук
    Sound finish(finishBuffer);
    
//    finish.play();
    for (int i = 0; i < 4; i++) {
        timeCoordinatesY[i] = massivOfCoordinates2[i].y;
        timeCoordinatesX[i] = massivOfCoordinates2[i].x;
    }
                            
    for (int i = 0; i < 4; i++) {
        massivOfCoordinates2[i].y += 1;
    }
    if (!checkThePosition2()) {
        finish.play();
        for (int i = 0; i < 4; i++) {
            massivOfCoordinates2[i].y = timeCoordinatesY[i];
            field2[timeCoordinatesY[i]][timeCoordinatesX[i]] = m;
        }
        createTetramino2();
    }
};

void Tetramino::moveTetraminoLeftOrRight(RenderWindow& window, int vector) {
    int timeCoordinatesX[4] = {};
    int timeCoordinatesY[4] = {};
                        
    for (int i = 0; i < 4; i++) {
        timeCoordinatesY[i] = massivOfCoordinates[i].y;
        timeCoordinatesX[i] = massivOfCoordinates[i].x;
    }
    for (int i = 0; i < 4; i++) {
        massivOfCoordinates[i].x += vector;
    }
    if (!checkThePosition()) {
        for (int i = 0; i < 4; i++) {
        massivOfCoordinates[i].x = timeCoordinatesX[i];
        }
    }
};
void Tetramino::moveTetraminoLeftOrRight2(RenderWindow& window, int vector) {
    int timeCoordinatesX[4] = {};
    int timeCoordinatesY[4] = {};
                        
    for (int i = 0; i < 4; i++) {
        timeCoordinatesY[i] = massivOfCoordinates2[i].y;
        timeCoordinatesX[i] = massivOfCoordinates2[i].x;
    }
    for (int i = 0; i < 4; i++) {
        massivOfCoordinates2[i].x += vector;
    }
    if (!checkThePosition2()) {
        for (int i = 0; i < 4; i++) {
        massivOfCoordinates2[i].x = timeCoordinatesX[i];
        }
    }
};
bool Tetramino::check_finish_game() {
    for(int i = 0; i < N; ++i) {
        if((field[1][i] != 0)||(field2[1][i] != 0))
            return true;
    }
    return false;
};



