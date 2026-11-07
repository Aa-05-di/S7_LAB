#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


#define MAXP 10
#define MAXD 50

char lhs[MAXP],rhs[MAXP][MAXP],in[20],start,sStack[MAXD][MAXD],sAct[MAXD][MAXD],st[MAXD];
int n,np,sIp[MAXD];


void record(int d,int top,int ip,char *act)
{
    memcpy(sStack[d],st,top);
    sStack[d][top]='\0';
    sIp[d]=ip;
    strcpy(sAct[d],act);
}

int parse(int d,int top,int ip){
    if(d>=MAXD)return 0;
    if(ip==n && top==1 && st[0]==start)
    {
        printf("%-10s %-10s %s\n","STACK","INPUT","ACTION");
            printf("%-10s %-10s %s\n","$",in,"-");

            for(int i=0;i<d;i++)
                printf("%-10s %-10s %s\n",sStack[i],in+sIp[i],sAct[i]);
                return 1;
            

            }
            for(int p=0;p<np;p++)
            {
                int len=strlen(rhs[p]);
                if(len==0)continue;
                if(top>=len && strncmp(st+top-len,rhs[p],len)==0)
                {
                    char act[30];
                    st[top-len]=lhs[p];
                    snprintf(act,sizeof act,"REDUCE %c - > %s",lhs[p],rhs[p]);
                    record(d,top-len+1,ip,act);
                    if(parse(d+1,top-len+1,ip))return 1;

                    memcpy(st+top-len,rhs[p],len);
                }
            }
            if(ip>n && top<MAXD){
                st[top]=in[ip];
                record(d,top+1,ip+1,"SHIFT");
                if(parse(d+1,top+1,ip+1))return 1;
            }
            return 0;
}