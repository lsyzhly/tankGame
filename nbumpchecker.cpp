#include "nbumpchecker.h"
#include <list>
#include <algorithm>
using std::list;
using std::vector;
using std::max;
using std::min;
using std::unique;
using std::pair;
using std::make_pair;
using namespace item;
namespace bump{
bool bumphandle(mpointer a,pointer b,bumpchecker *){
    static int n=1;
    printf("%d\n",n++);
    return true;
}

Mcmd::Mcmd(){
}

Cmd::Cmd(mpointer target){
    this->target=target;
    this->drt=wrong;
    this->size=0;
    isVaild=false;
}

inline void Cmd::run(){
    target->moveDirect(drt,rsize);
}

#define addPos(target,x,y,z)\
    int x=target->x;\
    int y=target->y;\
    int size=target->size;\
    pos p(x,y);\
    for(i=0;i<msize+size;i++){\
        p.x z;\
        for(int ii=max(0,i-size);ii<i && ii<msize;ii++){\
            (*this)[ii].push_back(p);\
            p.y+=size;\
            (*this)[ii].push_back(p);\
            p.y=y;\
        }\
    }\
    p.x=x;\
    for(i=0;i<msize;i++){\
        (*this)[i].index=i;\
        (*this)[i].fatherCmd=this;\
        p.x z;\
        p.y=y;\
        for(int j=2;j<size;j++){\
            p.y++;\
            (*this)[i].push_back(p);\
            p.x+=size;\
            (*this)[i].push_back(p);\
            p.x-=size;\
        }\
    }\

void Cmd::complie(){
    rsize=msize;
    reSize(msize);
    int i;
    if(drt==up){
        addPos(target,y,x,--);
    }else if(drt==down){
        addPos(target,y,x,++);
    }else if(drt==left){
        addPos(target,x,y,--);
    }else if(drt==right){
        addPos(target,x,y,++);
    }
}

Cmd &bumpchecker::operator[](mpointer pointer){
    cmds[pointer->cmdIndex].isVaild=false;
    return cmds[pointer->cmdIndex];
}
void bumpchecker::complie(){
    printf("%d,%d\n",cmds[0].msize,cmds[1].msize);
    for(int i=0;i<cmds.size();i++){
        cmds[i].complie();
    }
}
void bumpchecker::RunMcmd(){
    int vsize=cmds.size();
    for(int z=0;z<vsize;z++){
        Cmd &cmd=cmds[z];
        int vcsize=cmd.msize;
        for(int i=0;i<vcsize;i++){
            Mcmd &mcmd=cmd[i];
            int vmsize=mcmd.size();
            for(int j=0;j<vmsize;j++){
                if(blockmap[mcmd[j]]){
                    bool &n=bumpdata[make_pair(cmd.target,blockmap[mcmd[j]])];
                    if(n==false){
                        n=true;
                        if(bumphandle(cmd.target,blockmap[mcmd[j]],this)){
                            cmd.rsize=min(cmd.rsize,mcmd.index);
                        }
                    }
                }
                if(movemap[mcmd[j]]){
                    Mcmd &omcmd=*movemap[mcmd[j]];
                    Cmd &ocmd=*omcmd.fatherCmd;
                    if(ocmd.target!=cmd.target){
                        bool &n=bumpdata[make_pair(cmd.target,ocmd.target)];
                        if(n==false){
                            n=true;
                            if(bumphandle(cmd.target,ocmd.target,this)){
                                if(cmd.drt==wrong){
                                    ocmd.rsize=min(ocmd.rsize,omcmd.index);
                                }else if(cmd.drt==wrong){
                                    cmd.rsize=min(cmd.rsize,mcmd.index);
                                }
                                //同一方向,有bug
                                if(cmd.drt==ocmd.drt){
                                    if(mcmd.index<omcmd.index){
                                        ocmd.rsize=min(ocmd.rsize,cmd.msize);
                                    }else{
                                        cmd.rsize=min(cmd.rsize,ocmd.msize);
                                    }
                                //相反方向 不完美
                                }else if((cmd.drt&0x1)==(ocmd.drt&0x1)){
                                    int len=mcmd.index+omcmd.index;
                                    int allsize=cmd.msize+ocmd.msize;
                                    unsigned int mlen=len*(cmd.msize)/allsize;
                                    unsigned int omlen=len*(ocmd.msize)/allsize;
                                    cmd.rsize=min((unsigned int)cmd.rsize,mlen);
                                    ocmd.rsize=min((unsigned int)ocmd.rsize,omlen);
                                }else{
                                    cmd.rsize=min((unsigned int)cmd.rsize,mcmd.index);
                                    ocmd.rsize=min((unsigned int)ocmd.rsize,omcmd.index);
                                }
                            }
                        }
                    }
                }else{
                    movemap[mcmd[j]]=&mcmd;
                }
            }
        }
    }
    bumpdata.clear();
}

void bumpchecker::runCmd(){
    for(int i=0;i<cmds.size();i++){
        cmds[i].run();
        cmds[i].drt=wrong;
    }
}

bumpchecker::bumpchecker(int width,int length):blockmap(width,length),movemap(width,length){
}

void bumpchecker::add(pointer a){
    posSet *b=a->getRange();
    for(posSet::iterator c=b->begin();c!=b->end();c++){
        blockmap[*c]=a;
    }
    delete b;
}
void bumpchecker::remove(pointer a){
    posSet *b=a->getRange();
    for(posSet::iterator a=b->begin();a!=b->end();a++){
        blockmap[*a]=0;
    }
    delete b;
}
void bumpchecker::remove(mpointer a){
    cmds[a->cmdIndex]=cmds.back();
    cmds.pop_back();
    cmds[a->cmdIndex].target->cmdIndex=a->cmdIndex;
}
}
