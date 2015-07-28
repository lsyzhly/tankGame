#include "Control.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <istream>
#include "main.h"
#include <iterator>
#include <fstream>
#include "maincontrol.h"
#include "view.h"
#include "item.h"
#include <Windows.h>
#include  <list>
UINT player1tank[5]= {VK_UP,VK_RIGHT,VK_DOWN,VK_LEFT,76}; //表示player1的上下左右的虚拟键值up=0, down=2, left=3, right=1,L(fire)
UINT player2tank[5]= {87,68,83,65,VK_SPACE}; //表示player2的上下左右的虚拟键值 w,s,a,d,space
namespace Controler
{
    Control::Control(int maxcount)
    {
        this->maxcount=maxcount;
        this->count=maxcount;
    }
    Control::~Control()
    {
    }

    autoTankControl::autoTankControl(Tank *tank):Control(tank->speed)
    {
        this->tank = tank;
        tank->control = this;
        printf("starting run%p,%p\n", this,this->tank);
    }

    bool autoTankControl::run()
    {
        while(count--)
        {
            srand(clock());
            unsigned int a = rand()%4;
            unsigned int b = rand() % 50;
            int c = checker->move(tank, tank->drt);
            if (c&bumpType::astop || b==0)
            {
                c=checker->move(tank, (direct)a);
                if (c&bumpType::astop)
                {
                    tank->reDirect((direct)a);
                }
                else
                {
                    tank->moveDirect((direct)a);
                }
            }
            else
            {
                tank->moveDirect(tank->drt);
            }
            if(c&bumpType::abandonded)
            {
                count=maxcount;
                return true;
            }
        }
        count=maxcount;
        return false;
    }
    playTankControl::playTankControl(item::Tank *tank,int type):Control(tank->speed)
    {
        this->tank=tank;
        this->type=type;
    }
    bool playTankControl::run()
    {
        int dir=-1;
        count=maxcount;
        bool re=false;
        while(count--)
        {
            if(0==type)
            {
                if(isKeyDown[player1tank[up]])
                {
                    tank->reDirect(up);
                    dir=up;
                }
                else if(isKeyDown[player1tank[down]])
                {
                    tank->reDirect(down);
                    dir=down;
                }
                else if(isKeyDown[player1tank[left]])
                {
                    tank->reDirect(left);
                    dir= left;
                }
                else if(isKeyDown[player1tank[right]])
                {
                    tank->reDirect(right);
                    dir=right;
                }
                else if(isKeyDown[player1tank[4]])

                {
                    tank->fire();
                    re= false;
                }
                if(-1!=dir)
                {
                    int sta=checker->move(tank,tank->drt);
                    if(!(sta&bumpType::astop))
                        tank->draw->move(-1,-1,MOVEDIRECT|dir);
                    if(sta&bumpType::abandonded)
                    {
                        re= true;
                    }
                }
            }
            else
            {
                if(isKeyDown[player2tank[up]])
                {
                    tank->reDirect(up);
                    dir=up;
                }
                else if(isKeyDown[player2tank[down]])
                {
                    tank->reDirect(down);
                    dir=down;
                }
                else if(isKeyDown[player2tank[left]])
                {
                    tank->reDirect(left);
                    dir= left;
                }
                else if(isKeyDown[player2tank[right]])
                {
                    tank->reDirect(right);
                    dir=right;
                }
                else if(isKeyDown[player2tank[4]])

                {
                    tank->fire();
                    re= false;
                }
                if(-1!=dir)
                {
                    int sta=checker->move(tank,tank->drt);
                    if(!(sta&bumpType::astop))
                        tank->draw->move(-1,-1,MOVEDIRECT|dir);
                    if(sta&bumpType::abandonded)
                    {
                        re= true;
                    }
                }


            }
        }
        return re;
    }
}
