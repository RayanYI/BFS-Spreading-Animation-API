#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include<vector>

class CGame{
    private:
        int a_window_height=0,a_window_width=0;
        float a_node_height=0.0f,a_node_width=0.0f;
        const int n=10;
        sf::RenderWindow* a_window=nullptr;
        std::vector<std::vector<sf::RectangleShape> >a_matrix= std::vector<std::vector<sf::RectangleShape> >(n,std::vector<sf::RectangleShape>(n));
        sf::Event a_event;

    public:
        CGame(int p_width,int p_height,std::string p_label);
        void Events();
        void Clear();
        void Draw();
        void Dislplay();
        bool IsOpen(void)const{return(a_window->isOpen());};
        ~CGame();
};