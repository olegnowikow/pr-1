#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>


namespace std {
    template<typename T>
    std::string to_string(const T &n) {
        std::ostringstream s;
        s << n;
        return s.str();
    }
}


int main()
{
    enum{LEFT,RIGHT,DOWN,UP,MENU,PAUSE,PLAYING,GAMEOVER};

    const int gameWidth = 800;
    const int gameHeight = 600;

    const int szW = 40;
    const int szH = 30;

    float mulW = float(gameWidth)/float(szW);
    float mulH = float(gameHeight)/float(szH);
    sf::Vector2f segment_size(mulW, mulH);

    sf::Vector2f *snake = new sf::Vector2f[int(mulW*mulH)];
    //sf::Vector2f snake[1000];
    int snake_size;
    int snake_go, new_go;
    int bestScore = 0;
    sf::Vector2f apple;

    float frame_time;

    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SNAKE");
    window.setVerticalSyncEnabled(true);

    // Load the text font
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf"))
        return EXIT_FAILURE;

    sf::Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(30);
    pauseMessage.setPosition(170.f, 150.f);
    pauseMessage.setFillColor(sf::Color::White);

    sf::Clock clock;
    clock.restart();

    int gameState = MENU;
    pauseMessage.setString("S   N   A   K   E\n\n1.  Newbie\n2. Amateur\n3. Profi\n0. Exit");

    // main cycle
    while (window.isOpen())
    {
        // --- events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            if (event.type == sf::Event::KeyPressed){
                if (gameState == MENU) {
                    if (event.key.code == sf::Keyboard::Num0){
                        window.close();
                        break;
                    }
                    if ((event.key.code == sf::Keyboard::Num1)
                     || (event.key.code == sf::Keyboard::Num2)
                     || (event.key.code == sf::Keyboard::Num3)){
                        if (event.key.code == sf::Keyboard::Num1) frame_time = 0.3;
                        if (event.key.code == sf::Keyboard::Num2) frame_time = 0.2;
                        if (event.key.code == sf::Keyboard::Num3) frame_time = 0.1;
                        snake_size = 1;
                        snake[0].x = szW / 2;
                        snake[0].y = szH / 2;
                        snake_go = RIGHT;
                        new_go = RIGHT;
                        apple.x = szW / 4;
                        apple.y = szH / 4;
                        gameState = PLAYING;
                        break;
                    }
                }
                if (gameState == PLAYING) {
                    if (event.key.code == sf::Keyboard::Space) {
                        gameState = PAUSE;
                        pauseMessage.setString("PAUSE\nPress <Space> to Continue");
                        break;
                    }
                }
                if (gameState == PAUSE) {
                    if (event.key.code == sf::Keyboard::Space) {
                        gameState = PLAYING;
                        break;
                    }
                }
                if (gameState == GAMEOVER) {
                    if (event.key.code == sf::Keyboard::Space) {
                        gameState = MENU;
                        pauseMessage.setString("S   N   A   K   E\n\n1.  Newbie\n2. Amateur\n3. Profi\n0. Exit");
                        break;
                    }
                }
            }
        } //while (window.pollEvent(event))

        if (gameState == PLAYING) {
            // --- check keyboard
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) {
                if(snake_go != DOWN) new_go = UP;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) {
                if (snake_go != UP) new_go = DOWN;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) {
                if (snake_go != RIGHT) new_go = LEFT;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
                if (snake_go != LEFT) new_go = RIGHT;
            }
            // --- render
            float deltaTime = clock.getElapsedTime().asSeconds();
            bool new_apple = false;
            if (deltaTime >= frame_time) {
                clock.restart();
                sf::Vector2f head = snake[0];
                if (new_go == DOWN) head.y++;
                if (new_go == UP) head.y--;
                if (new_go == RIGHT) head.x++;
                if (new_go == LEFT) head.x--;
                snake_go = new_go;
                // check head to go
                if (head == apple) { // eat apple
                    snake_size ++;
                    new_apple = true;
                }
                bool isCross = false;
                for (int i = 1; i < snake_size; i++) { // self cross
                    if (head == snake[i]) {
                        isCross = true;
                        break;
                    }
                }
                // check collision
                if (isCross || head.x > szW-1 || head.x < 0 || head.y > szH-1 || head.y < 0) {
                        gameState = GAMEOVER;
                        if (bestScore < snake_size) bestScore = snake_size;
                        sf::String str = "G A M E    O V E R"
                            + sf::String("\nYour Score: ")
                            + sf::String(std::to_string(snake_size))
                            + sf::String("\nBest Score: ")
                            + sf::String(std::to_string(bestScore))
                            + "\nPress <Space> to Menu";
                        pauseMessage.setString(str);
                }
                // snake new position
                for (int i = snake_size-1; i > 0; i--){
                    snake[i] = snake[i-1];
                }
                snake[0] = head;
                if (new_apple) {
                    for(;;){
                        bool ex = true;
                        apple.x = rand() % szW;
                        apple.y = rand() % szH;
                        for (int i = 0; i < snake_size; i++) {
                            if (apple == snake[i]) {
                                ex = false;
                                break;
                            }
                        }
                        if (ex) break;
                    }
                    new_apple = false;
                    frame_time *=0.9; // get faster
                }

            } //if (deltaTime >= frame_time)
        } //if (isPlaying)
        // --- clear
        window.clear();
        // --- draw frame
        if (gameState == PLAYING) {
            for (int i = 0; i < snake_size; i++) {
                sf::RectangleShape segment;
                segment.setSize(segment_size - sf::Vector2f(2, 2));
                segment.setFillColor(sf::Color(100, 100, 200));
                sf::Vector2f pos(snake[i].x*mulW, snake[i].y*mulH);
                segment.setPosition(pos);
                window.draw(segment);
            }
            sf::RectangleShape segment;
            segment.setSize(segment_size - sf::Vector2f(2, 2));
            segment.setFillColor(sf::Color(0, 200, 0));
            sf::Vector2f pos(apple.x*mulW, apple.y*mulH);
            segment.setPosition(pos);
            window.draw(segment);
        }
        else {
            window.draw(pauseMessage);
        }
        // --- display
        window.display();
    } // while (window.isOpen())
    delete[] snake;
    return 0;
}
