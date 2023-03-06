#include "CGame.h"

CGame::CGame(int p_width,int p_height,std::string p_label){
    a_window=new sf::RenderWindow(sf::VideoMode(p_width, p_height),p_label);
    a_window_height=p_height;
    a_window_width=p_width;
    a_node_height=(p_height-(n-1)*5)/n;
    a_node_width=(p_width-(n-1)*5)/n;
    for(int i=0;i<a_matrix.size();i++){
        for(int j=0;j<a_matrix[i].size();j++){
            a_matrix[i][j].setSize(sf::Vector2f(a_node_width,a_node_height));
            a_matrix[i][j].setPosition(j*(a_node_width+5.f),i*(a_node_height+5.f));  
        }
    }

}

void CGame::Clear(){
    a_window->clear();
}

void CGame::Draw(){
   for(auto const&row:a_matrix){
       for(auto const&x:row)a_window->draw(x);
    }
}

void CGame::Dislplay(){
    a_window->display();
}

void CGame::Events(){
    while (a_window->pollEvent(a_event))
    {
        if (a_event.type == sf::Event::Closed)
            a_window->close();

       // if (a_event.type == sf::Event::KeyPressed){
         //   if (a_event.key.code == sf::Keyboard::Enter)state=abs(state-1);
        //}

        if(a_event.type == sf::Event::MouseButtonPressed){
            std::cout << "mouse x: " << a_event.mouseButton.x << std::endl;
            std::cout << "mouse y: " << a_event.mouseButton.y << std::endl;
        }
    }
}

CGame::~CGame(){
    delete a_window;
    a_window=nullptr;
}