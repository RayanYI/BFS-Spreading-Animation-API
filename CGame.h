#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>

class CGame{
    private:
        int a_window_height=0,a_window_width=0,a_nbNode=0,a_nbWall=0;
        float a_node_height=0.0f,a_node_width=0.0f;
        bool a_started=false,a_paused=false;
        const int n=50;
        sf::RenderWindow* a_window=nullptr;
        sf::Event a_event;
        std::vector<std::vector<sf::RectangleShape>>a_matrix= std::vector<std::vector<sf::RectangleShape>>(n,std::vector<sf::RectangleShape>(n));
        std::vector<std::vector<char>>flag= std::vector<std::vector<char>>(n,std::vector<char>(n,0));
        std::vector<std::pair<int,int>>moves={{1,0},{-1,0},{0,1},{0,-1}};
        std::unordered_map<char,sf::Color>color_map={{0,sf::Color::White},{1,sf::Color::Red},{2,sf::Color(128,128,128)}};
        std::queue<std::pair<int,int>>q;

        void Events();
        void Clear();
        void Draw();
        void Dislplay();
        void Start();
        void Reset();
        void Bfs();
        void ChangeColor(int i,int j,sf::Color p_color);
        bool GetState(void)const{return(a_started && !a_paused);};
        bool IsOpen(void)const{return(a_window->isOpen());};

    public:
        CGame(int p_width,int p_height,std::string p_label);
        void Play();
        ~CGame();
};