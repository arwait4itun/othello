#include<iostream>

using namespace std;

class OthelloBoard{

    public:
        int board[8][8];
        int w=1;
        int b=2;

        OthelloBoard(){

            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    board[i][j]=0;
                }
            }

            board[3][3] = w;
            board[4][4] = w;
            board[3][4] = b;
            board[4][3] = b;
        }

        void display(){

            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    if(board[i][j]==1){
                        cout<<"W"<<" ";
                    }
                    else if(board[i][j]==2){
                        cout<<"Z"<<" ";
                    }
                    else{
                        cout<<board[i][j]<<" ";
                    }
                }
                cout<<"\n";
            }
        }
};


//get valid moves(player)
//do move,return 0 valid move return -1 if invalid
//score
//trapped.
//minimax

int main(){


    OthelloBoard brd;

    brd.display();

    return 0;
}
