#include "app.hpp"

App::App() {
    backGroundTexture.loadFromFile("cartoonWater.jpg");
    background.setTexture(backGroundTexture);
}

//Main run game function
void App::runGame() {
	srand((unsigned int)time(NULL)); //For Rand()
    int mouseX, mouseY, boardX, boardY;
    sf::Event event;
    sf::Vector2f boardPos;

    bool round = false;
    
    playerHitCount = 0;
    enemyHitCount = 0;

    hitMissSum = 0;

    Coordinate coord={-1,-1};
    
    boatCollectionTex.loadFromFile("BattleshipBoatCollection.png");
    boatCollection.setTexture(boatCollectionTex);
    boatCollection.setPosition({ 500,50 });
    bool gameSetup = false;
    bool gameActive = true;
    
    font.loadFromFile("minecraftFont.ttf");
   
    LHStext.setString("Enemy board");
    LHStext.setFont(font);
    RHStext.setString("Your board");
    RHStext.setFont(font);
    buildTitle(LHStext, 1350, 25);
    buildTitle(RHStext, 300, 25);
    buildBoard(playerBoard.buttonGameBoard, 150, 125);
    buildBoard(enemyBoard.buttonGameBoard, 1200, 125);

    initBoard(playerBoard.charGameBoard, 10, 10);
    initBoard(enemyBoard.charGameBoard, 10, 10);

    initBoolPlacement();
    
    setBoatCollectionText(boatCollectionText);

    runStartMenu();

    window.create(sf::VideoMode(1920, 728), "Battleship");
    
    //Game setup
    putShipsDown();
    
    
    
  
    
    

    //Game play
    while (window.isOpen() && gameActive)
    {
   
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
            //Get user input until considered valid round
                getClickPosition(mouseX, mouseY, window);
                boardPos.x = mouseX;
                boardPos.y = mouseY;
                getClickPos(enemyBoard.buttonGameBoard, boardPos, boardX, boardY);
                coord.column = boardY;
                coord.row = boardX;
                round=playerRound(coord);

            //simulate opponent round
                if (round) {
                    simulateBotRound();
                }

            //Check if game is over
                if (playerHitCount >= 17) {
                //Display player won
                    gameActive = false;
                }
                else if (enemyHitCount >= 17) {
                    gameActive = false;
                }

            }
        }

        window.clear();
        
        window.draw(background);
        window.draw(LHStext);
        window.draw(RHStext);
        drawBoard(window,playerBoard.buttonGameBoard);
        drawBoard(window,enemyBoard.buttonGameBoard);
        drawShips();
        drawMarkers();
        window.display();
    }

    if (playerHitCount >= 17) {
        drawWin();
    while (window.isOpen()) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(winBackground);
        window.display();
       
       
    }
    }

    if (enemyHitCount >= 17) {
        drawLoss();
       
        while (window.isOpen()) {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
           
            window.clear();
            window.draw(lossBackground);
            window.display();

        }
    }
}

//Returns the mouse position relative to a given window via two integer values
void App::getClickPosition(int& x, int& y, sf::RenderWindow& window) {
    sf::Event event;
    sf::Vector2i mousePos;

    do {
        window.pollEvent(event);

        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }
        
    } while (event.type != sf::Event::MouseButtonPressed);

    mousePos=sf::Mouse::getPosition(window);
    x = mousePos.x;
    y = mousePos.y;
}

//Runs loop to display startMenu until play is clicked or window is closed
void App::runStartMenu() {
    sf::RenderWindow startMenu(sf::VideoMode(1000, 400), "Battleship");
    sf::Event event;
    sf::Sprite startMenuBackground;
    sf::Texture backgroundTex;
    StartButton startbutton;
    sf::Font font;
    sf::Sprite instructionBackground;
    sf::Texture instructionTexture;
    

    int x;
    int y;

    instructionTexture.loadFromFile("instructions.png");
    instructionBackground.setTexture(instructionTexture);
    instructionBackground.setPosition({ 0,0 });

    font.loadFromFile("minecraftFont.ttf");
    sf::Text text("PLAY!", font);
    text.setCharacterSize(30);
    text.setPosition(465, 202);
    sf::Text title("BATTLESHIP", font);
    title.setCharacterSize(60);
    title.setPosition(335, 50);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(3);
    backgroundTex.loadFromFile("StartMenu.png");
    startMenuBackground.setTexture(backgroundTex);
    startbutton.setPosition(400, 200);

    while (startMenu.isOpen()) {
        while (startMenu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                startMenu.close();
            startMenu.draw(startMenuBackground);
            startbutton.drawTo(startMenu);
            startMenu.draw(instructionBackground);
            startMenu.draw(title);
            startMenu.draw(text);
            startMenu.display();
            getClickPosition(x, y, startMenu);
            if (startbutton.isClicked(x,y) ){
            startMenu.close();
            }
        }
    
    }
    
}

//Makes text to make title ready to be drawn
void App::buildTitle(sf::Text& text, int x, int y) {
    text.setCharacterSize(40);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(3);
    text.setPosition(x,y);
}

//Used to draw board 
void App::drawBoard(sf::RenderWindow& window, BoardButton board[][10]) {
    for (int i = 0; i < 10; i++) {
        for (int n = 0; n < 10; n++) {
            window.draw(board[n][i]);
        }
    }
}

//Used to return the corresponding column and row of the box that got clicked
void App::getClickPos(BoardButton board[][10], sf::Vector2f clickPos, int& x, int &y) {
    bool found = false;
    for (int i = 0; i < 10; i++) {
        for (int n = 0; n < 10; n++) {
            if (board[n][i].isClicked(clickPos.x, clickPos.y)) {
                x = i;
                y = n;

                i = 10;
                found = true;
                break;
            }
        }
    }

    if (found == false) {
        x = -1;
        y = -1;
    }
}

//Sets up startMenu text label for boats
void App::setBoatCollectionText(sf::Text textCollection[]) {
    int startX=1250, startY=100;
    for (int i = 0; i < 5; i++) {
        textCollection[i].setFont(font);
        textCollection[i].setCharacterSize(30);
        textCollection[i].setOutlineColor(sf::Color::Black);
        textCollection[i].setOutlineThickness(3);
        textCollection[i].setPosition(startX, startY);
        startY += 125;
    }

    textCollection[0].setString("Battleship: 4");
    textCollection[1].setString("Cruiser: 2");
    textCollection[2].setString("Submarine: 3");
    textCollection[3].setString("Destroyer: 3");
    textCollection[4].setString("Carrier: 3");
}

void App::drawBoatCollectionText(sf::Text textCollection[], sf::RenderWindow& window) {
    for (int i = 0; i < 5; i++) {
        window.draw(textCollection[i]);
    }

}

//Used to create board grid
void App::buildBoard(BoardButton board[][10], int startX, int startY) {
    int xPos = startX;
    int yPos = startY;
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            board[y][x].setButtonPosition(xPos, yPos);
            xPos += 50;
        }
        xPos = startX;
        yPos += 50;
    }
}

//Used to place ship on both the boards for the character and the visual display
void App::placeShipPack(Ship &ship, Board& board, sf::RenderWindow& window, Coordinate coord, Direction dir) {
    std::string type = ship.getType();

    //Rotation
    if (dir == HORIZ) {
        ship.setPosition(board.buttonGameBoard[coord.row][coord.column].getPosition());
    }
    else if (dir == VERT) {
        ship.setRotation(90);
        ship.setPosition(board.buttonGameBoard[coord.row][coord.column].getPosition());
        ship.setPosition(ship.getPosition().x + 50, ship.getPosition().y);
    }
    
    sf::Vector2f test = board.buttonGameBoard[coord.row][coord.column].getPosition();
    

    //Boat selection
    if (type == "Cruiser") {
            for (int i = 0; i < ship.getSize();i++) {
                board.buttonGameBoard[coord.row][coord.column + i].setType('c');
            }
            placeShip(board.charGameBoard, 10, 10, 'c', 2, dir, coord);
            isPlaced[1] = true;
    }
    else if (type == "Submarine" || type == "Destroyer") {
            if (type == "Submarine") {
                placeShip(board.charGameBoard, 10, 10, 's', 3, dir, coord);
                for (int i = 0; i < ship.getSize(); i++) {
                    board.buttonGameBoard[coord.row][coord.column + i].setType('s');
                }
                isPlaced[2] = true;
            }

            else if (type == "Destroyer") {
                placeShip(board.charGameBoard, 10, 10, 'd', 3, dir, coord);
                for (int i = 0; i < ship.getSize(); i++) {
                    board.buttonGameBoard[coord.row][coord.column + i].setType('d');
                }
                isPlaced[3] = true;
            }
            
    }
    else if (type == "Battleship") {
            placeShip(board.charGameBoard, 10, 10, 'b', 4, dir, coord);
            for (int i = 0; i < ship.getSize(); i++) {
                board.buttonGameBoard[coord.row][coord.column + i].setType('b');   
            }
            isPlaced[0] = true;
    }
    else if (type == "Carrier") {
            placeShip(board.charGameBoard, 10, 10, 'C', 5, dir, coord);
            for (int i = 0; i < ship.getSize(); i++) {
                board.buttonGameBoard[coord.row][coord.column + i].setType('C');
            }
            isPlaced[4] = true;
    }
    else {
        std::cout << "Invalid ship type" << std::endl;
    }
    
  

   
}

//Place a hit on both the character and visual display boards
void App::placeHit(Board &board, int x, int y) {
    //Button Board
    Marker hitMark;
    sf::Texture hitMarkTex;
    hitMarkTex.loadFromFile("hitMark.png");
    hitMark.setTexture(hitMarkTex);
    hitMark.setPosition(board.buttonGameBoard[x][y].getPosition());
    hitMissCollection[hitMissSum]=hitMark;
    hitMissSum++;

    //Char Board
    board.charGameBoard[x][y]='X';

    
    

}

//Place a hit on both the character and visual display boards
void App::placeMiss(Board& board, int x, int y) {
    //Button Board
    Marker missMark;
    sf::Texture missMarkTex;
    missMarkTex.loadFromFile("missShot.png");
    missMark.setTexture(missMarkTex);
    missMark.setPosition(board.buttonGameBoard[x][y].getPosition());
    hitMissCollection[hitMissSum] = missMark;
    hitMissSum++;
    


    //Char Board
    board.charGameBoard[x][y] = 'O';
}

//NOT IN USE
void App::createWarning() {
    sf::Sprite warning;
    sf::Texture warningTexture;
    warningTexture.loadFromFile("Warning.jpg");
    warning.setTexture(warningTexture);
    warning.setPosition(800, 400);
    window.draw(warning);
}

//Gets user input to place one ship
void App::getUserBoatPlacement(Board &board, Ship& ship) {
    bool validation = false;
    Direction dir;
    Coordinate coord={-1,-1};
    sf::Event event;
    int mouseX, mouseY, boardX, boardY;
    sf::Vector2f boardPos;
    int check = 0;


   
    while (window.isOpen() && validation==false) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                getClickPosition(mouseX, mouseY, window);
                boardPos.x = mouseX;
                boardPos.y = mouseY;
                getClickPos(playerBoard.buttonGameBoard, boardPos, boardX, boardY);
                coord.column = boardX;
                coord.row = boardY;
                if (rand() % 2 == 0) {
                    dir = VERT;
                }
                else {
                    dir = HORIZ;
                }

                validation = validatePlacement(board.charGameBoard, ship.getSize(), dir, coord);
                check = 1;
            }
            window.clear();
            window.draw(background);
            window.draw(RHStext);
            drawBoard(window, playerBoard.buttonGameBoard);
            window.draw(boatCollection);
            drawBoatCollectionText(boatCollectionText, window);
            drawShips();
            window.display();
            

        }

    }

    placeShipPack(ship, board, window, coord, dir);
}

void App::generateEnemyBoard()
{
    //Character Board
    initBoard(this->enemyBoard.charGameBoard, 10, 10);
    placeShipsRandomly(this->enemyBoard.charGameBoard);

    
}

//Returns true if successful round
bool App::playerRound(Coordinate coord)
{
    char check;
    check = checkHit(enemyBoard, coord.column, coord.row);
    
    switch (check) {
    case 'O':{
        
        }

    case '-': {
        placeMiss(enemyBoard, coord.column, coord.row);
        return true;
    }
    case 'X': {
        
    }
    case 'A': {
        placeHit(enemyBoard, coord.column, coord.row);
        playerHitCount++;
        return true;
    }
    case 'E': {
    
    }
    default: {
        std::cout << "Invalid input" << std::endl;
    }
    
    }
    return false;
}

//Simulates one round being run for the enemy bot
//Called in response to a valid user round
void App::simulateBotRound()
{
    Coordinate coord = {-1,-1};
    bool hitMiss = false;
    int* redoPtr = new int(1);

    do 
    {
        coord = genAttackCoord();
        hitMiss = attackAndUpdate(playerBoard.charGameBoard, playerBoard.charGameBoard, coord, redoPtr);
    } while (*redoPtr == 1);
    
    if (hitMiss == true)
    {
        // Put hit onto sprite board at "coord" location
        placeHit(playerBoard, coord.column, coord.row);
        enemyHitCount++;
    }
    else
    {
        // Put miss onto sprite board
        placeMiss(playerBoard, coord.column, coord.row);
    }
}

//Peeks the character board and returns a character representative of what is on the board
char App::checkHit(Board &board, int x, int y) {
    if (board.charGameBoard[x][y] == 'O') {
        return 'O';
    }
    else if (board.charGameBoard[x][y] == '-') {
        return '-';
    }
    else if (board.charGameBoard[x][y] == 'X') {
        return 'X';
    }
    else if (board.charGameBoard[x][y] == 'c'|| board.charGameBoard[x][y] == 'D'|| board.charGameBoard[x][y] == 'C'|| board.charGameBoard[x][y] == 'B'|| board.charGameBoard[x][y] == 'S') {
        return 'A';
    }
    else {
        return 'E';
    }
    
}


void App::putShipsDown() {
    initShips();
    //Battleship
    getUserBoatPlacement(playerBoard, *ships[0]);
    //Cruiser
    getUserBoatPlacement(playerBoard, *ships[1]);
    //Submarine
    getUserBoatPlacement(playerBoard, *ships[2]);
    //Destroyer
    getUserBoatPlacement(playerBoard, *ships[3]);
    //Carrier
    getUserBoatPlacement(playerBoard, *ships[4]);

    //Enemy Board
    generateEnemyBoard();
}





void App::initShips() {
    Ship* battleship = new Battleship();
    Ship* cruiser = new Cruiser();
    Ship* submarine = new Submarine();
    Ship* destroyer = new Destroyer();
    Ship* carrier = new Carrier();
    ships[0] = battleship;
    ships[1] = cruiser;
    ships[2] = submarine;
    ships[3] = destroyer;
    ships[4] = carrier;

}


void App::drawShips() {
    if (isPlaced[0]) {
        window.draw(*ships[0]);
    }
    if (isPlaced[1]) {
        window.draw(*ships[1]);
    }
    if (isPlaced[2]) {
        window.draw(*ships[2]);
    }
    if (isPlaced[3]) {
        window.draw(*ships[3]);
    }
    if (isPlaced[4]) {
        window.draw(*ships[4]);
    }
}

void App::initBoolPlacement() {
    for (int i=0;i<5;i++){
    isPlaced[i] = false;
    }
}

void App::drawMarkers() {
    for (int i = 0; i < hitMissSum; i++) {
        window.draw(hitMissCollection[i]);
    }

}

void App::drawWin() {
    winTex.loadFromFile("winBackground.png");
    winBackground.setTexture(winTex);
    winBackground.setPosition(0, 0);
    window.draw(winBackground);
}

void App::drawLoss() {
    lossTex.loadFromFile("lossBackground.png");
    lossBackground.setTexture(lossTex);
    lossBackground.setPosition(0, 0);
    window.draw(lossBackground);
}