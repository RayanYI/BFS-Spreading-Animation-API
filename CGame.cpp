#include "CGame.h"

CGame::CGame(int p_width,int p_height,std::string p_label){
    a_window=new sf::RenderWindow(sf::VideoMode(p_width, p_height),p_label);
    a_window_height=p_height;
    a_window_width=p_width;
    a_node_height=(p_height-(n-1)*5+5.f/n)/n;
    a_node_width=(p_width-(n-1)*5+5.f/n)/n;
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
        if (a_event.type == sf::Event::Closed ||a_event.key.code == sf::Keyboard::Escape) a_window->close();
        
        if (a_event.type == sf::Event::KeyPressed){
            if (a_event.key.code == sf::Keyboard::Enter)Start();
            else if(a_event.key.code == sf::Keyboard::BackSpace)Reset();
            else if(a_event.key.code == sf::Keyboard::Space && a_started)a_paused=abs(a_paused-1);
        }

        if(a_event.type == sf::Event::MouseButtonPressed && !a_started){
            int i=a_event.mouseButton.y/(a_node_height+5),j=a_event.mouseButton.x/(a_node_width+5); 
            if (a_event.mouseButton.button == sf::Mouse::Left){
                if(flag[i][j]==1)flag[i][j]=0,a_nbNode--;
                else{
                    if(flag[i][j]==2)a_nbWall--;
                    flag[i][j]=1;
                    a_nbNode++;
                }
            }else{
                if(flag[i][j]==2)flag[i][j]=0,a_nbWall--;
                else{
                    if(flag[i][j]==1)a_nbNode--;
                    flag[i][j]=2;
                    a_nbWall++;
                }
            }
            ChangeColor(i,j,color_map[flag[i][j]]);
        }          
    }
}

void CGame::ChangeColor(int i,int j,sf::Color p_color){
    a_matrix[i][j].setFillColor(p_color);
}

void CGame::Start(){
    if(q.empty() && a_nbNode && a_nbNode+a_nbWall<n*n && !a_started){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(flag[i][j]==1)q.push({i,j});
            }
        }
        a_started=true;
    }
}

void CGame::Reset(){
    if(a_nbNode || a_nbWall){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(flag[i][j]){
                    flag[i][j]=0;
                    ChangeColor(i,j,color_map[flag[i][j]]);
                }
            }
        }
        if(!q.empty()){
            std::queue<std::pair<int,int>> empty;
            std::swap(q,empty );
        }
        a_started=false;
        a_paused=false;
        a_nbNode=0;
        a_nbWall=0;
    }
}

void CGame::Bfs(){
    int s=q.size();
    while(s--){
        for(auto const&x:moves){
            int i=q.front().first+x.first,j=q.front().second+x.second;
            if(i>=0 && i<n && j>=0 && j<n && flag[i][j]==0)flag[i][j]=1,q.push({i,j});
        }
        ChangeColor(q.front().first,q.front().second,color_map[flag[q.front().first][q.front().second]]);
        q.pop();
    }
}

void CGame::Play(){
    sf::Clock clock;
    while(IsOpen()){
        Events();
        if(clock.getElapsedTime().asSeconds()>=0.1618f && GetState())Bfs(),clock.restart();
        Clear();
        Draw();
        Dislplay();
    }
}

CGame::~CGame(){
    delete a_window;
    a_window=nullptr;
}