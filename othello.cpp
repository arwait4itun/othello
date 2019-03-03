#include<iostream>
#include <list>
#include <iterator>
#include <array>
#include<vector>
#include <typeinfo>

using namespace std;

struct Move_struct{
    int arr[2];
};

void dup(int a[8][8],int b[8][8]){
    //deep copy a into b
    for(int i=0;i<8;i++){
        copy(a[i],a[i]+8,b[i]);
    }
}


class OthelloBoard{

    public:
        int board[8][8];
        int w=2;
        int b=1;

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

        double score(); //score

        int doMove(int,int,int); //returns 0 on success and -1 on failure and checks for trap

        bool gameOver(); //game over


};


//get valid moves(player)
//do move,return 0 valid move return -1 if invalid
//score
//game over
//trapped.
//minimax

bool OthelloBoard::gameOver(){

    bool flag=true;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[i][j]== 0){
                flag=false;
                break;
            }
        }
    }
    return flag;
}

double OthelloBoard::score(){

    double p_coins=0.0,op_coins=0.0;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(board[i][j]==1)p_coins++;
            else if(board[i][j]==2)op_coins++;
        }
    }

    if(gameOver()){
        if(p_coins>op_coins) return (1.0/0.0);
        else if(p_coins<op_coins) return -(1.0/0.0);
        else return 0;
    }
    else{
        return (float)(p_coins/op_coins);
    }
}


int OthelloBoard::doMove(int row,int col,int disc){
	int num_flipped = 0;

	if (board[row][col] != 0)
		return -1;

	board[row][col] = disc;

	int opposing_disc;
	if (disc == 1)
		opposing_disc = 2;
	else
		opposing_disc = 1;

	// Do we have discs to the right to flip?
	int disc_pos = -1;
	for (int c = col + 1; c < 8 && board[row][c] != 0 && disc_pos == -1; c++)
	{
		if (board[row][c] == disc)
			disc_pos = c;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos > col + 1)
	{
		// Flip discs to the right
		for (int c = col + 1; c < disc_pos; c++)
		{
			board[row][c] = disc;
			num_flipped++;
		}
	}

	// Do we have discs to the left to flip?
	disc_pos = -1;
	for (int c = col - 1; c >= 0 && board[row][c] != 0 && disc_pos == -1; c--)
	{
		if (board[row][c] == disc)
			disc_pos = c;
	}

	//if (disc_pos > -1) cout << "left disc_pos = " << disc_pos << endl;

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos < col - 1)
	{
		// Flip discs to the left
		for (int c = col - 1; c > disc_pos; c--)
		{
			board[row][c] = disc;
			num_flipped++;
		}
	}

	// Do we have discs above to flip?
	disc_pos = -1;
	for (int r = row - 1; r >= 0 && board[r][col] != 0 && disc_pos == -1; r--)
	{
		if (board[r][col] == disc)
			disc_pos = r;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos < row - 1)
	{
		// Flip discs above
		for (int r = row - 1; r > disc_pos; r--)
		{
			board[r][col] = disc;
			num_flipped++;
		}
	}

	// Do we have discs below to flip?
	disc_pos = -1;
	for (int r = row + 1; r < 8 && board[r][col] != 0 && disc_pos == -1; r++)
	{
		if (board[r][col] == disc)
			disc_pos = r;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos > row + 1)
	{
		// Flip discs below
		for (int r = row + 1; r < disc_pos; r++)
		{
			board[r][col] = disc;
			num_flipped++;
		}
	}

	// Do we have discs diagnally up-left to flip?
	disc_pos = -1;
	int c = col - 1;
	for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != 0 && disc_pos == -1; r--)
	{
		if (board[r][c] == disc)
			disc_pos = r;
		c--;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos < row - 1)
	{
		c = col - 1;
		for (int r = row - 1; r > disc_pos; r--)
		{
			board[r][c] = disc;
			num_flipped++;
			c--;
		}
	}

	// Do we have discs diagnally up-right to flip?
	disc_pos = -1;
	c = col + 1;
	for (int r = row - 1; c < 8 && r >= 0 && board[r][c] != 0 && disc_pos == -1; r--)
	{
		if (board[r][c] == disc)
			disc_pos = r;
		c++;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos < row - 1)
	{
		c = col + 1;
		for (int r = row - 1; r > disc_pos; r--)
		{
			board[r][c] = disc;
			num_flipped++;
			c++;
		}
	}

	// Do we have discs diagnally down-left to flip?
	disc_pos = -1;
	c = col - 1;
	for (int r = row + 1; c >= 0 && r < 8 && board[r][c] != 0 && disc_pos == -1; r++)
	{
		if (board[r][c] == disc)
			disc_pos = r;
		c--;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos > row + 1)
	{
		c = col - 1;
		for (int r = row + 1; r < disc_pos; r++)
		{
			board[r][c] = disc;
			num_flipped++;
			c--;
		}
	}

	// Do we have discs diagnally down-right to flip?
	disc_pos = -1;
	c = col + 1;
	for (int r = row + 1; c < 8 && r < 8 && board[r][c] != 0 && disc_pos == -1; r++)
	{
		if (board[r][c] == disc)
			disc_pos = r;
		c++;
	}

	// Make sure we found a disc and that it is at least 2 spots away
	if (disc_pos != -1 && disc_pos > row + 1)
	{
		c = col + 1;
		for (int r = row + 1; r < disc_pos; r++)
		{
			board[r][c] = disc;
			num_flipped++;
			c++;
		}
	}

	// Reset board if nothing was flipped... illegal move
    return 0;
}


vector<Move_struct> getValidMoves(int board[8][8]){

    vector<Move_struct> arry;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

            if(board[i][j]==0){
                Move_struct a;
                a.arr[0]=i;
                a.arr[1]=j;
                arry.push_back(a);
            }
        }
    }

    return arry;
}


double alphabeta(OthelloBoard brd,int depth,double alpha,double beta,int player){

    if(brd.gameOver() || depth == 0){
        return brd.score();
    }

    if(player==1){

        double value = -(1.0/0.0);
        OthelloBoard new_brd;

        dup(brd.board,new_brd.board);

        vector<Move_struct> moves = getValidMoves(brd.board);

        for(int i=0;i< moves.size();i++){

            new_brd.doMove(moves[i].arr[0],moves[i].arr[1],player);

            double vl=alphabeta(new_brd,depth-1,alpha,beta,2);

            if(vl>value) value = vl;
            if(value>alpha) alpha = value;

            if(alpha>=beta) break;
        }
        return value;
    }
    else if(player==2){

        double value = (1.0/0.0);
        OthelloBoard new_brd;

        dup(brd.board,new_brd.board);

        vector<Move_struct> moves = getValidMoves(brd.board);

        for(int i=0;i< moves.size();i++){

            new_brd.doMove(moves[i].arr[0],moves[i].arr[1],player);

            double vl=alphabeta(new_brd,depth-1,alpha,beta,1);

            if(vl<value) value = vl;
            if(value<beta) beta = value;

            if(alpha>=beta) break;
        }
        return value;
    }
}

void cpu_move(OthelloBoard brd){

        vector<Move_struct> moves = getValidMoves(brd.board);

        double depth = 4,alpha=-(1.0/0.0),beta=(1.0/0.0);

        double sc=-1.0/0.0;
        Move_struct mv;
        OthelloBoard new_brd;

        dup(brd.board,new_brd.board);


        for(int i=0;i< moves.size();i++){
            new_brd.doMove(moves[i].arr[0],moves[i].arr[1],1);

            double vl=alphabeta(new_brd,depth,alpha,beta,2);

            if(vl>sc){
                sc=vl;
                mv.arr[0]=moves[i].arr[0];
                mv.arr[1]=moves[i].arr[1];
            }
        }

        //brd.doMove(mv.arr[0],mv.arr[1],1); NOT working
        cout<<"(i,j) = ("<<mv.arr[0]<<","<<mv.arr[1]<<")\n";
}


int main(){


    OthelloBoard brd;
    int i,j;




    brd.display();
    while(!brd.gameOver()){
        cout<<"cpu turn:\n";
        cpu_move(brd);
        cin>>i>>j;
        brd.doMove(i,j,1);

        brd.display();

        while(true){
            cout<<"\nplayer turn:\nEnter valid move(i,j)\n";
            cin>>i>>j;

            if(brd.board[i][j]==0) break;
            else cout<<"invalid move\n";
        }
        brd.doMove(i,j,2);
        brd.display();
    }

    if(brd.score()==1.0/0.0) cout<<"\nCPU WON!\n";
    else if(brd.score()==1.0/0.0) cout<<"\nYOU WON!\n";
    else cout<<"\nIT'S A DRAW!\n";

    return 0;
}
