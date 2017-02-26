#include<stdio.h>
/*
 manojkumargupta@gmail.com

Description:
-----------------
  1) Program to check if there is a way out of a maze.
  2) It take input of 100 characters, and makes a maze(grid) of 10x10.
  3) Entrance to the maze is (0,0) and the exit is at point (9,9)
  4) Character O(Alphabet O) is considered as pass/path/allow, all other characters are considered as blockage.
  5) Allowed moves : (1) Left Right, (2) Forward Backward. Not allowed : (1) Cross Move
  6) Return of 0 means, no path through maze.
  7) Return of 1 means, there is path through maze.

Few sample input strings:
--------------------------
 OOOOOOOOOOXXXXXXXXXXOOOOOOOOOOXXXXXXXXXXOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
 OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
 OOOOOOOOOOOOOOOOOOOXOOOOOOOOXOOOOOOOOXOOOOOOOOXOOOOOOOOXOOOOOOOOXOOOOOXXXXXOOOOOOOOOOOOOOOOOOOOOOOOO
 OOOOOOOOOOOOOOOOOOOXOOOOOOOOOOOOOOOOOXOOOOOOOOXOOOOOOOOXOOOOOOOOXOOOOOXXXXXOOOOOOOOOOOOOOOOOOOOOOOOO
 OOOOOOOOOOOOOOOOOOOXOOOOOOOOOOOOOOOOOXXOOOOOOOXOOOOOOOOXOOOOOOOOXOOXXXXXXXXOOOOOOOOOOOOOOOOOOOOOOOOO
 OOOOOOOOOOOOOOOOOOOXOOOOOOOOOOOOOOOOOXXOOOOOOOXOOOOOOOOXOOOOOOOOXOXXXXXXXXXOOOOOOOOOOOOOOOOOOOOOOOOO

Sample Run:
--------------------------------------------------------------------------------------------------------------------------
Input 1): OOOOOOOOOOXXXXXXXXXXOOOOOOOOOOXXXXXXXXXXOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

InputGiven: PathTravered:
OOOOOOOOOO	1111111111
XXXXXXXXXX	0000000000
OOOOOOOOOO	0000000000
XXXXXXXXXX	0000000000
OOOOOOOOOO	0000000000
OOOOOOOOOO	0000000000
OOOOOOOOOO	0000000000
OOOOOOOOOO	0000000000
OOOOOOOOOO	0000000000
OOOOOOOOOO	0000000000

Answer: 0

--------------------------------------------------------------------------------------------------------------------------
Input 2): OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

InputGiven: PathTravered:
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1000000000
OOOOOOOOOO	1111111111

Answer: 1 

--------------------------------------------------------------------------------------------------------------------------
*/

int maze[10][10];
int pathVisited[10][10];

int main(){
    int rowIndex,colIndex,ret;
    char input[100];
    ret=0;
    printf("Enter the string: ");
    scanf("%100c",input);
    for(rowIndex=0;rowIndex<10;rowIndex++){
        for(colIndex=0;colIndex<10;colIndex++){
            maze[rowIndex][colIndex]=input[rowIndex*10+colIndex] == 'O'?'O':'X';
            pathVisited[rowIndex][colIndex]=0;
            //fprintf(stderr,"%s\n",maze[rowIndex]);
        }
    }

    if(maze[0][0] == 'O' && maze[9][9] == 'O'){
        ret=mazeUp(0,0);
    } 

    fprintf(stderr,"InputGiven: \t PathTravered:\n");
    for(rowIndex=0;rowIndex<10;rowIndex++){
        for(colIndex=0;colIndex<10;colIndex++)
            fprintf(stderr,"%c",maze[rowIndex][colIndex]);
        fprintf(stderr,"\t");
        for(colIndex=0;colIndex<10;colIndex++)
            fprintf(stderr,"%d",(pathVisited[rowIndex][colIndex]>0?1:0));
        fprintf(stderr,"\n");
    }

    if(ret >= 1){
        fprintf(stdout,"1\n");
        return 0;
    }else{
        fprintf(stdout,"0\n");
        return 1;
    }
    return 1;
}


int mazeUp(int rowIndex,int colEntryPosition){
    int colCurrentPosition;
    int ret;
    colCurrentPosition=colEntryPosition;
    if(rowIndex == 9 && colEntryPosition == 9){
        return 1;
    }

    if(pathVisited[rowIndex][colEntryPosition]){
        pathVisited[rowIndex][colEntryPosition]++;
        return 0;
    }else{
        pathVisited[rowIndex][colEntryPosition]++;
    }
    if(rowIndex < 9){
        for(;colCurrentPosition>=0;){
            //fprintf(stderr,"rowIndex=%d,colIndex=%d\n",rowIndex,colCurrentPosition);
            if(maze[rowIndex+1][colCurrentPosition]=='O') {
                fprintf(stderr,"Movingup to rowIndex=%d,colIndex=%d\n",rowIndex+1,colCurrentPosition);
                ret=mazeUp(rowIndex+1,colCurrentPosition);
                if(ret >= 1){
                    return ret;
                }
            }
            if(colCurrentPosition>0 && maze[rowIndex][colCurrentPosition-1] == 'O'){
                colCurrentPosition=colCurrentPosition-1;
                pathVisited[rowIndex][colCurrentPosition]++;
            }else{
                break;
            }
            //sleep(1);
        }
        if(colEntryPosition<9 && maze[rowIndex][colEntryPosition+1] == 'O'){
            colCurrentPosition=colEntryPosition+1;
            pathVisited[rowIndex][colCurrentPosition]++;
        }else{ 
            return 0;
        }

        for(;colCurrentPosition<10;){
            if(maze[rowIndex+1][colCurrentPosition]=='O') {
                fprintf(stderr,"MovingUp to rowIndex=%d,colIndex=%d\n",rowIndex+1,colCurrentPosition);
                ret=mazeUp(rowIndex+1,colCurrentPosition);
                if(ret >= 1){
                    return ret;
                }
            }      
            if(colCurrentPosition<9 && maze[rowIndex][colCurrentPosition+1] == 'O'){
                colCurrentPosition=colCurrentPosition+1;
                pathVisited[rowIndex][colCurrentPosition]++;
            }else{
                return 0;
            }
            //sleep(1);
        }
    }
    if(rowIndex == 9){
        for(;colCurrentPosition<9;){
            //fprintf(stderr,"rowIndex=%d,colIndex=%d\n",rowIndex,colCurrentPosition);
            if(maze[rowIndex][colCurrentPosition+1] == 'O'){
                colCurrentPosition=colCurrentPosition+1;
                pathVisited[rowIndex][colCurrentPosition]++;
            }else{
                return 0;
            }
        }
        if(colCurrentPosition==9){
            return 1;
        }
    }
    return 0;
}

