#include "nbumpchecker.h"
#include <list>
#include <algorithm>
using namespace std;

pos::pos(int x,int y){
    this->x=x;
    this->y=x;
}
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
    if(isVaild) return;
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
    isVaild=true;
}

void bumpchecker::run_deque(){
    deleteIndex.clear();
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
                                if(cmd.drt==ocmd.drt){
                                    if(mcmd.index<omcmd.index){
                                        ocmd.rsize=min(ocmd.rsize,cmd.msize);
                                    }else{
                                        cmd.rsize=min(cmd.rsize,ocmd.msize);
                                    }
                                }else if((cmd.drt&0x2)==(ocmd.drt&0x2)){
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
        sort(deleteIndex.begin(),deleteIndex.end());
        vector<int>::iterator end=unique(deleteIndex.begin(),deleteIndex.end());
        for(vector<int>::iterator it=deleteIndex.begin();it<end;it++){
            cmds[*it]=cmds.back();
            cmds[*it].target->cmdIndex=*it;
            cmds.pop_back();
        }
        for(int i=0;i<blockList.size();i++){

        }
    }
    bumpdata.clear();
}



void bumpchecker::add_to_deque(mpointer a){
    a->cmdIndex=cmds.size();
    cmds.push_back(Cmd(a));
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
bumpchecker::bumpchecker(int width,int length):blockmap(width,length),movemap(width,length){
}
