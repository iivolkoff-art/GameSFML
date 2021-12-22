#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
using namespace std;
using namespace sf;

class Player
{
public:
    float x, y, w, h, dx, dy, speed = 0;//Координаты x,y; Высота w,h; Ускорение dx, dy; Скорость Speed
    int dir = 0;// Направление движения игрока
    String File; // файл с расширением
    Image image;// изображение
    Texture texture;
    Sprite sprite;

    Player(String F, int X, int Y, float W, float H)
    {
        File = F;
        w = W; h = H;
        image.loadFromFile("images/" + File); 
        image.createMaskFromColor(Color(41, 33, 59));// маска по цвету
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;// координаты появления спрайта
        sprite.setTextureRect(IntRect(w, h, w, h));// задаем спрайту один прямойгольник
    }

    void update(float time)
    {
        switch (dir) // задается направление движение
        {
        case 0:
            dx = speed;
            dy = 0;
            break;

        case 1:
            dx = -speed;
            dy = 0;
            break;

        case 2:
            dx = 0;
            dy = speed;
            break;

        case 3:
            dx = 0;
            dy = -speed;
            break;
        }

        x += dx * time;// аналоги движения
        y += dy * time;// аналоги движения

        speed = 0;// когда отпускаешь клавишу персонаж стоит
        sprite.setPosition(x, y);
    }  
};

int Hero()
{
        RenderWindow window(VideoMode(1400, 960), "Nigger");

        Image Map_image;
        Map_image.loadFromFile("images/map.png");
        Texture Map;
        Map.loadFromImage(Map_image);
        Sprite s_Map;
        s_Map.setTexture(Map);


        Player p("hero.png", 250, 250, 96.0, 96.0); // создаем персонажа

        float CurrentFrame = 0;
        Clock clock;

        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asMicroseconds(); // дать прошедшее время в микросекундах
            

            clock.restart();// перезагружает время
            time = time / 400;// Cкорость игры
            
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                p.dir = 1; p.speed = 0.1;

                CurrentFrame += 0.005 * time;// Задает скорость анимации
       
                if(CurrentFrame > 3) 
                {
                    CurrentFrame -= 3;// 3 это количество кадров(картинок) анимации
                }
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
               
            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                p.dir = 0; p.speed = 0.1;

                CurrentFrame += 0.005 * time;// Задает скорость анимации

                if (CurrentFrame > 3)
                {
                    CurrentFrame -= 3;// 3 это количество кадров(картинок) анимации
                }
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
            }

            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                p.dir = 3; p.speed = 0.1;

                CurrentFrame += 0.005 * time;// Задает скорость анимации

                if (CurrentFrame > 3)
                {
                    CurrentFrame -= 3;// 3 это количество кадров(картинок) анимации
                }
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));        
            }

            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                p.dir = 2; p.speed = 0.1;

                CurrentFrame += 0.005 * time;// Задает скорость анимации

                if (CurrentFrame > 3)
                {
                    CurrentFrame -= 3;// 3 это количество кадров(картинок) анимации
                }
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
            }

            p.update(time);// показывает движение

            window.clear();

            for (int i = 0; i < HEIGHT_MAP; i++)
            {
                for (int j = 0; j < WIDTH_MAP; j++)
                {
                    if (TileMap[i][j] == ' ')// если встречаем пробел- рисуем квадратик
                    {
                        s_Map.setTextureRect(IntRect(0, 0, 32, 32));
                    }

                    if (TileMap[i][j] == 's') // если встречаем s - 2-ой квадратик
                    {
                        s_Map.setTextureRect(IntRect(32, 0, 32, 32));
                    }

                    if (TileMap[i][j] == '0') // если встречаем 0 - 3-ий квадрат
                    {
                        s_Map.setTextureRect(IntRect(64, 0, 32, 32));
                    }

                    s_Map.setPosition(j * 32, i * 32); // задаем позицию квадратам

                    window.draw(s_Map);// риуем квадратики
                }
            }
              

            window.draw(p.sprite);
            window.display();
        }
        return 0;
}
    
int main()
{
    setlocale(LC_ALL, "ru");
         Hero();
}