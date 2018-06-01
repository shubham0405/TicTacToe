  #include<stdio.h>
#include<stdlib.h>
struct move
{
    int row;
    int col;
};
int more(int a,int b)
{
    return (a>b)?a:b;
}
int less(int a,int b)
{
    return a+b-more(a,b);
}
char me='X';
char you='O';
int end(char** arr)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(arr[i][j]=='-')
                return 0;
        }
    }
    return 1;
}
void print(char** arr)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("   %c",arr[i][j]);
        }
        printf("\n");
    }
    return;
}
int evaluate(char** arr)
{
    for(int i=0;i<3;i++)
    {
        if(arr[i][0]==arr[i][1] && arr[i][2]==arr[i][0])
        {
            if(arr[i][0]==me)
                return 100;
            if(arr[i][0]==you)
                return -100;
        }
    }
    for(int i=0;i<3;i++)
    {
        if(arr[0][i]==arr[1][i] && arr[2][i]==arr[0][i])
        {
            if(arr[0][i]==me)
                return 100;
            if(arr[0][i]==you)
                return -100;
        }
    }
    if(arr[0][0]==arr[1][1] && arr[0][0]==arr[2][2])
    {
        if(arr[0][0]==me)
            return 100;
        if(arr[0][0]==you)
            return -100;
    }
    if(arr[0][2]==arr[1][1] && arr[2][0]==arr[0][2])
    {
        if(arr[0][2]==me)
            return 100;
        if(arr[0][2]==you)
            return -100;
    }
    return 0;
}
int minmax(char** arr,int depth,int turn)
{
    int score=evaluate(arr);
    //printf("%d\n",score);
    if(score!=0)  return score;
    if(end(arr)==1)  return 0;
    if(depth==0)  return 0;
    if(turn%2==1)
    {
        int max=-1111;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(arr[i][j]=='-')
                {
                    arr[i][j]=me;
                    max=more(max,minmax(arr,depth-1,turn+1));
                    arr[i][j]='-';
                }
            }
        }
        return max+depth;
    }
    else
    {
        int max=1111;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(arr[i][j]=='-')
                {
                    arr[i][j]=you;
                    max=less(max,minmax(arr,depth-1,turn+1));
                    arr[i][j]='-';
                }
            }
        }
        return max+depth;
    }
}
struct move chance(char** arr)
{
    int best=-1000;
    struct move bestmove={-1,-1};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {

            //printf("%d",i);
            if(arr[i][j]=='-')
            {
                arr[i][j]=me;
                int curr=minmax(arr,9,0);
                printf("%d ",curr);
                if(curr>best)
                {
                    best=curr;
                    bestmove.row=i;
                    bestmove.col=j;
                }
                arr[i][j]='-';
            }
        }
    }
    printf("\n");
    return bestmove;
}
int isend(char** arr)
{
    for(int i=0;i<3;i++)
    {
        if(arr[i][0]==arr[i][1] && arr[i][2]==arr[i][0])
        {
            if(arr[i][0]==me)
                return 1;
            if(arr[i][0]==you)
                return 0;
        }
    }
    for(int i=0;i<3;i++)
    {
        if(arr[0][i]==arr[1][i] && arr[2][i]==arr[0][i])
        {
            if(arr[0][i]==me)
                return 1;
            if(arr[0][i]==you)
                return -0;
        }
    }
    if(arr[0][0]==arr[1][1] && arr[0][0]==arr[2][2])
    {
        if(arr[0][0]==me)
            return 1;
        if(arr[0][0]==you)
            return 0;
    }
    if(arr[0][2]==arr[1][1] && arr[2][0]==arr[0][2])
    {
        if(arr[0][2]==me)
            return 1;
        if(arr[0][2]==you)
            return 0;
    }
    return -1;
}
int main()
{
    printf("LETS START\n");
     char** arr=(char**)malloc(sizeof(char*)*3);
     for(int i=0;i<3;i++)
     {
         arr[i]=(char*)malloc(sizeof(char)*3);
     }
     for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        arr[i][j]='-';
    char your;
    int depth=0;
    print(arr);
     printf("CHOOSE YOUR IDENTITY(O or X):");
     scanf("%c",&your);
     printf("\n");
     if(your=='X' || your=='x')
     {
         me='O';
         you='X';
     }
     //printf("j");
     if(me=='X')
     {
         struct move winm=chance(arr);
         arr[winm.row][winm.col]='X';
         print(arr);
         depth++;
     }
     while(depth<10)
     {
         int x,y;
         printf("Make your move: ");
         scanf("%d %d",&x,&y);
         printf("\n");

         if(arr[x-1][y-1]!='-')
         {
             printf("YOU CHEATER");
             return 0;
         }
                  arr[x-1][y-1]=you;
         print(arr);
         int con=isend(arr);
         if(con==0)
         {
             printf("YOU WON\n");
             return 0;
         }
         else if(con==1)
         {
             printf("YOU LOSE\n");
             return 0;
         }
         if(end(arr)==1)
         {
             printf("DRAW\n");
             return 0;
         }
         depth++;
         struct move winm=chance(arr);
         arr[winm.row][winm.col]=me;
         printf("MY MOVE\n");
         print(arr);
         con=isend(arr);
         if(con==0)
         {
             printf("YOU WON\n");
             return 0;
         }
         else if(con==1)
         {
             printf("YOU LOSE\n");
             return 0;
         }
         if(end(arr)==1)
         {
             printf("DRAW\n");
             return 0;
         }
         depth++;
     }
     return 0;
}
