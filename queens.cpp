#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

bool isValid(char** board, int N, int row, int col){
    for (int i=0; col-i>=0; i++){
        if (board[row][col-i] == 'Q') return false;
    }
    int i = 1;
    while (row-i>=0 && col-i>=0){
        if (board[row-i][col-i] == 'Q') return false;
        i++;
    }
    i = 1;
    while (row+i<N && col-i>=0){
        if (board[row+i][col-i] == 'Q') return false;
        i++;
    }
    return true;
}

char** makeBoard(int N){
    char** board = new char*[N];
    for(int i=0; i<N; i++){
        board[i] = new char[N];
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            board[i][j] = '+';
        }
    }
    return board;
}

void printBoard(char** board, int N){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

char** placeQueens(char** board, int N){
    stack <int> Qrow;
    stack <int> goback;

    int* nums = new int[N];
    for (int i=0; i<N; i++){
        nums[i] = i;
    }
    int** spots = new int*[N];
    for (int i=0; i<N; i++){
        shuffle(nums, nums+(N), mt19937(random_device()()));
        spots[i] = new int[N];
        for (int j=0; j<N; j++){
            spots[i][j] = nums[j];
        }
    }
    int* spotspot = new int[N];
    for (int i=0; i<N; i++){
        spotspot[i] = 0;
    }

    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            goback.push(i);
        }
        while (!isValid(board, N, spots[i][spotspot[i]], i)){
            goback.pop();
            spotspot[i]++;
            if (spotspot[i]==N){
                spotspot[i] = 0;
                for(int k=i-1; k>=goback.top(); k--){
                    board[Qrow.top()][k] = '+'; // '.' to see checked spots
                    Qrow.pop(); //printBoard(board, N);
                }
                i = goback.top();
                for(int k=N-1; k>i; k--){
                    spotspot[k] = 0;
                }
                spotspot[i]++;
            }
        }
        Qrow.push(spots[i][spotspot[i]]);
        board[spots[i][spotspot[i]]][i] = 'Q'; //printBoard(board, N);
    }
    return board;
}

int main(const int argc, const char *argv[]){
    int N = stoi(argv[1]);
    char** board = makeBoard(N);
    printBoard(placeQueens(board, N), N);

    for (int i = 0; i < N; i++) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
};