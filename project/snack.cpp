#include<SFML/Graphics.hpp>
#include<time.h>
#include<iostream>
#include<sstream>
#include<vector>

using namespace sf;

int A = 40, B = 30;
int gsize = 14;
int w = gsize * A;
int h = gsize * B;
float timer = 0, delay = 0.1;
int dir, snakeSize = 2, score = 0, highestScore = 0;

struct Snake
{
    int x, y;

} s[100];


struct Fruit 
{
    int x, y;
}   f;

struct BonusFood 
{
    int x, y;
    bool isActive;
    
}bonusFood;


struct Obstacle 
{
    int x, y;
};

std::vector<Obstacle> obstacles;

std::string to_string(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

bool isCollisionWithObstacle(int x, int y)
{
    for (int i = 0; i < obstacles.size(); i++) 
    {
        if (obstacles[i].x == x && obstacles[i].y == y) 
        {
            return true;
        }
    }
    return false;
}

void update() 
{
    for (int i = snakeSize; i > 0; i--) 
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    if ((s[0].x == f.x) && (s[0].y == f.y)) 
    {
        snakeSize++;
        score++;
        if (score > highestScore) highestScore = score;
        if (score % 5 == 0 && score != 0) delay -= 0.01;
        do {
            f.x = rand() % (A - 1);
            f.y = rand() % (B - 1);
        } while (isCollisionWithObstacle(f.x, f.y));
        if (f.x >= 0 && f.x <= 3) f.x = 4;
        if (f.y >= 0 && f.y <= 4) f.y = 4;

    }

    if (bonusFood.isActive && (s[0].x == bonusFood.x) && (s[0].y == bonusFood.y)) 
    {
        score += 3;
        bonusFood.isActive = false;
    }

    if (score >= 5 && score % 5 == 0 && !bonusFood.isActive) 
    {

        do {
            bonusFood.x = rand() % (A - 1);
            bonusFood.y = rand() % (B - 1);
        } while (isCollisionWithObstacle(bonusFood.x, bonusFood.y));
        if (score == 0) 
        {
            bonusFood.isActive = false;
        }
        bonusFood.isActive = true;        
    }


    for (int i = 0; i < obstacles.size(); i++)
    {
        if (s[0].x == obstacles[i].x && s[0].y == obstacles[i].y)
        {
            snakeSize = 2;
            score = 0;
            delay = 0.1;
            dir = 0;
            break;
        }
    }

    for (int i = 1; i < snakeSize; i++) {
        if (s[0].x == s[i].x && s[0].y == s[i].y)
        {
            snakeSize = 2;
            score = 0;
            delay = 0.1;
            break;
        }
    }
    if (s[0].x < 0 || s[0].x >= A || s[0].y >= B || s[0].y < 0) {
        snakeSize = 2;
        score = 0;
        delay = 0.1;
        dir = 0;
        s[0].x = A / 2;
        s[0].y = B / 2;
        for (int i = snakeSize; i >0; i--) 
        {
            s[i].x = s[i-1].x;
            s[i].y = s[i-1].y;
        }
    }
}

int main() 
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "SNAKE WORLD");

    Texture t1, t2, t3, t4, t5;
    t1.loadFromFile("images/white.png");
    t2.loadFromFile("images/red.png");
    t3.loadFromFile("images/food.png");
    t4.loadFromFile("images/purple.png");
    t5.loadFromFile("images/background4.0.png");
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    Sprite sprite4(t4);
    Sprite sprite5(t5);

    Font font;
    font.loadFromFile("images/arial.ttf");

    Text scoreText, HighestScoreText;
    scoreText.setFont(font);
    scoreText.setFillColor(Color::Blue);
    scoreText.setPosition(10, 10);
    scoreText.setCharacterSize(18);
    scoreText.setString("Current Score: 0");
    scoreText.setStyle(Text::Bold);
    scoreText.setStyle(Text::Italic);

    HighestScoreText.setFont(font);
    HighestScoreText.setFillColor(Color::Red);
    HighestScoreText.setPosition(400, 10);
    HighestScoreText.setCharacterSize(18);
    HighestScoreText.setString("Highest Score: 0");
    HighestScoreText.setStyle(Text::Bold);
    HighestScoreText.setStyle(Text::Italic);

    Clock clock;

    f.x =rand()%(A- 1);
    f.y =rand()%(B- 1);

    bonusFood.isActive =false;


    obstacles.push_back(Obstacle{ 26, 9 });
    obstacles.push_back(Obstacle{ 9, 26 });
    obstacles.push_back(Obstacle{ 35, 20 });
    obstacles.push_back(Obstacle{ 35, 21 });
    obstacles.push_back(Obstacle{ 35, 22 });
    obstacles.push_back(Obstacle{ 26, 18 });
    obstacles.push_back(Obstacle{ 26, 19 });
    obstacles.push_back(Obstacle{ 26, 20 });
    obstacles.push_back(Obstacle{ 26, 10 });
    obstacles.push_back(Obstacle{ 10, 26 });
    obstacles.push_back(Obstacle{ 5, 10 });
    obstacles.push_back(Obstacle{ 5, 11 });
    obstacles.push_back(Obstacle{ 5, 12 });
    obstacles.push_back(Obstacle{ 15, 15 });
    obstacles.push_back(Obstacle{ 16, 15 });

    while (window.isOpen()) 
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
            }

            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3) dir = 0;

        if (timer > delay) 
        {
            timer = 0;
            update();
        }

        scoreText.setString("Current Score: " + to_string(score));
        HighestScoreText.setString("Highest Score: " + to_string(highestScore));


        window.clear();

        for (int i = 0; i < A; i++) 
        {
            for (int j = 0; j < B; j++) 
            {
                sprite1.setPosition(i * gsize, j * gsize);
                window.draw(sprite1);
            }
        }

        for (int i = 0; i < snakeSize; i++) 
        {
            sprite2.setPosition(s[i].x * gsize, s[i].y * gsize);
            window.draw(sprite2);
        }

        window.draw(scoreText);
        window.draw(HighestScoreText);

        sprite3.setPosition(f.x * gsize, f.y * gsize);
        window.draw(sprite3);


        for (size_t i = 0; i < obstacles.size(); i++) 
        {
            sprite5.setPosition(obstacles[i].x * gsize, obstacles[i].y * gsize);
            window.draw(sprite5);
        }


        if (bonusFood.isActive)
        {
            sprite4.setPosition(bonusFood.x * gsize, bonusFood.y * gsize);
            window.draw(sprite4);
        }

        window.display();
    }
    return 0;
}
