#include <iostream>
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
#define x first
#define y second
class SnakeGame
{
private:
    int width,height; // width and height of the game
    char head; // label of the head
    char tail; // label of the tail
    int hx,hy; // coordinates of head
    bool over = false;
    vector<pair<int,int>>tailxy; // coordinates of tail
    int fx,fy; // coordinates of food
    int score;
    char operation;
    char lastOperation;
    char food;
    map<pair<int,int>,string>flags;
public:
    SnakeGame (int w, int h, char hd, char tl)
    {
        width = w;
        height = h;
        head = hd;
        tail = tl;
        hx = w/2;
        hy = h/2;
        fx = -1;
        fy = -1;
        score = 0;
        food='F';
        tailxy.push_back(make_pair(hx-1,hy));
        tailxy.push_back(make_pair(hx-2,hy));
        operation='d';
    }
    void generateFood()
    {
        fx=rand()%(width-2);
        fy=rand()%(height-2);
    }
    void setFlag()
    {
        for(int i=0; i<(int)tailxy.size(); i++)
            flags[ {tailxy[i].x,tailxy[i].y}]="tail";
    }
    void moveTail()
    {
        for (int i=(int)tailxy.size()-1; i>0; i--)
        {
            tailxy[i].x=tailxy[i-1].x;
            tailxy[i].y=tailxy[i-1].y;
        }
        tailxy[0].x=hx;
        tailxy[0].y=hy;
        flags.clear();
        setFlag();
    }
    void move()
    {
        if (kbhit())
        {
            operation=_getch();
            if ((lastOperation=='w'&&operation=='s')||(lastOperation=='s'&&operation=='w')||(lastOperation=='a'&&operation=='d')||(lastOperation=='d'&&operation=='a'))
                operation=lastOperation;
        }
        if (operation=='w')
        {
            lastOperation='w';
            if (hx==fx && hy==fy)
            {
                tailxy.push_back(make_pair(hx,hy));
                score+=5;
                generateFood();
            }
            moveTail();
            hy--;
        }
        else if (operation=='d')
        {
            lastOperation='d';
            if (hx==fx && hy==fy)
            {
                tailxy.push_back(make_pair(hx,hy));
                score+=5;
                generateFood();
            }
            moveTail();
            hx++;
        }
        else if (operation=='a')
        {
            lastOperation='a';
            if (hx==fx && hy==fy)
            {
                tailxy.push_back(make_pair(hx,hy));
                score+=5;
                generateFood();
            }
            moveTail();
            hx--;
        }
        else if (operation=='s')
        {
            lastOperation='s';
            if (hx==fx && hy==fy)
            {
                tailxy.push_back(make_pair(hx,hy));
                score+=5;
                generateFood();
            }
            moveTail();
            hy++;
        }
        if (flags[ {hx,hy}]=="tail")
        {
            over=1; // Game over
        }
    }
    void drawWorld()
    {
        for (int i=0; i<width+2; i++)
        {

            HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute(h, 10);
            cout<<'#';
        }
        cout<<endl;
        for (int i=0; i<height; i++)
        {
            for (int j=0; j<width+2; j++)
            {
                if (j==hx && i==hy)
                {
                    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
                    SetConsoleTextAttribute(h, 14);
                    cout<<head;
                }
                else if (flags[ {j,i}]=="tail")
                {
                    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
                    SetConsoleTextAttribute(h, 14);
                    cout<<tail;
                }
                else if (j==fx && i==fy)
                {
                    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
                    SetConsoleTextAttribute(h, 12);
                    cout<<food;
                }
                else if(j==0 || j==width+1)
                {
                    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
                    SetConsoleTextAttribute(h, 10);
                    cout<<"#";
                }
                else
                    cout<<' ';
            }
            cout<<endl;
        }
        for (int i=0; i<width+2; i++)
        {
            HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
            SetConsoleTextAttribute(h, 10);
            cout<<'#';
        }
        cout<<endl;
        cout<<"Score = "<<score<<endl;
    }
    void run()
    {
        srand(time(0));
        setFlag();
        generateFood();
        while(!over)
        {
            system("cls");
            drawWorld();
            move();
            if (hx<0 || hy<0 || hx==width || hy==height)
            {
                over=1; // Game over
            }
        }
        system("cls");
        drawWorld();
    }
};
int main()
{
    int height,width;
    char head,tail;
    cout<<"Enter Height of the Game : ";
    cin>>height;
    cout<<"Enter Width of the Game : ";
    cin>>width;
    cout<<"Enter Label of the Head : ";
    cin>>head;
    cout<<"Enter Label of the Tail : ";
    cin>>tail;
    system("cls");
    SnakeGame SG(height,width,head,tail);
    SG.run();
}
