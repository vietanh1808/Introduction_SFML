#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Game
{
    public:
                Game();
        void    run();

    private:
        void    processEvents();
        void    update(sf::Time);
        void    render();
        void    handlePlayerInput();

    private:
        sf::RenderWindow    mWindow;
        sf::Texture         mTexture;
        sf::Sprite          mPlayer;

    private:
        bool                mIsMovingRight, mIsMovingUp, mIsMovingDown, mIsMovingLeft;
};

Game::Game():
    mWindow(sf::VideoMode(sf::Vector2u( 640, 480)), "SFML Application"),
    mTexture(),
    mPlayer(mTexture)
    {
        sf::Texture tempTexture;
        std::string path = "D:\\Outsources\\Sprunki_Game\\Assets\\Game\\Texture2D\\Message Prank\\hcn.png";
        if(!tempTexture.loadFromFile(path)){
            // Handle loading error
            std::cout << "File NOT Found at Path: " <<  path  << std::endl;
            return;
        }
        mPlayer(tempTexture);
        mPlayer.setPosition(sf::Vector2f(0.f, 0.f));

        std::cout << "Assign Completed! " << std::endl;
    }

void Game::run()
{
    sf::Clock clock;
    while(mWindow.isOpen())
    {
        sf::Time deltaTime = clock.reset();
        processEvents();
        update(deltaTime);
        render();
    }
}
void Game::processEvents()
{
    while (const std::optional event = mWindow.pollEvent())
    {
        // Window closed or escape key pressed: exit
        if (event->is<sf::Event::Closed>() ||
            (event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
            mWindow.close();

        handlePlayerInput();
    }
}
void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if(mIsMovingUp) { movement.y += 1.f; std::cout << "Moving Right !" << std::endl;}
    if(mIsMovingDown){ movement.y -= 1.f; std::cout << "Moving Down !" << std::endl;}
    if(mIsMovingLeft) { movement.x -= 1.f; std::cout << "Moving Left !" << std::endl;}
    if(mIsMovingRight) { movement.x += 1.f; std::cout << "Moving Right !" << std::endl;}

    mPlayer.move(movement * deltaTime.asSeconds());
}
void Game::handlePlayerInput()
{
    mIsMovingDown = mIsMovingLeft = mIsMovingRight = mIsMovingUp = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        mIsMovingUp = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        mIsMovingDown = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        mIsMovingLeft = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        mIsMovingRight = true;
    }
}
void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

int main()
{
    Game game;
    game.run();
}
