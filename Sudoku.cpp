#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class subSquare{
private:
    int fNum;
    vector<int> pNums;
public:
    void assignFNum(int const& num){
        pNums.clear();
        fNum=num;
    }
    void assignPNum(int const& num){
        pNums.push_back(num);
    }
    int getFNum(){
        return fNum;
    }
    vector<int> getPNums(){
        return pNums;
    }
    void removePNum(int const& num){
        int pos = (distance(pNums.begin(), find(pNums.begin(), pNums.end(), num)));
        pNums.erase(pNums.begin() + pos);
    }
    bool PNumsContain(int const& num){
        return(find(pNums.begin(), pNums.end(), num) < pNums.end());
    }
};

bool isNumeric(string const& input){
    for(int itr=0; itr<input.length(); itr++){
        if(!isdigit(input.at(itr))){
            return false;
        }
    }
    return true;
}

void strToUpper(string& input){
    for(int itr=0; itr<input.length(); itr++){
        input[itr]=toupper(input[itr]);
    }
}

void readGrid(subSquare input[9][9]){
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            printf("%d ", input[row][col].getFNum());
        }
        printf("\n");
    }
}

void createGrid(subSquare input[9][9]){
    string currentRow;
    printf("Please enter the grid below\n");
    int row=0;
    while(row<9){
        currentRow="";
        printf("Enter row %d:\n", row+1);
        getline(cin, currentRow);
        strToUpper(currentRow);
        if(isNumeric(currentRow)){
            if(currentRow.length()==9){
                for(int col=0; col<9; col++){
                    input[row][col].assignFNum(currentRow.at(col) - '0');
                }
                row++;
            }else if(currentRow.length() < 9){
                printf("ERROR: entry must be 9 numbers\n");
            }else{
                printf("ERROR: entry must be 9 numbers\n");
            }
        }else{
            if(currentRow=="BACK"){
                switch(row){
                    case 0: printf("Cannot go back further\n"); break;
                    default: row--; break;
                }
            }else{
                printf("ERROR: entry not valid\n");
            }
        }
    }
}


void cpyGrid(subSquare dst[9][9], subSquare src[9][9]){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            dst[row][col] = src[row][col];
        }
    }
}


void cpyGrid2(subSquare TD[9][9][9], subSquare arr[9][9], int const& TDIndx, string const& mode){
    if(mode == "TO_3D"){
        for(int row = 0; row < 9; row++){
            for(int col = 0; col < 9; col++){
                TD[TDIndx][row][col] = arr[row][col];
            }
        }
    }else if(mode == "TO_2D"){
        for(int row = 0; row < 9; row++){
            for(int col = 0; col < 9; col++){
                arr[row][col] = TD[TDIndx][row][col];
            }
        }
    }
}


bool gridUnsolved(subSquare input[9][9]){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(input[row][col].getFNum() == 0){
                return true;
            }
        }
    }
    return false;
}

void mkSqrVars(int const& rowIndx, int const& colIndx, int& rowPH, int& colPH){
    switch(rowIndx){
        case 0: case 1: case 2:
            rowPH=0;
            break;
        case 3: case 4: case 5:
            rowPH=3;
            break;
        case 6: case 7: case 8:
            rowPH=6;
            break;
        default: break;
    }
    switch(colIndx){
        case 0: case 1: case 2:
            colPH=0;
            break;
        case 3: case 4: case 5:
            colPH=3;
            break;
        case 6: case 7: case 8:
            colPH=6;
            break;
        default: break;
    }
}


bool squareContainsNum(subSquare input[9][9], int const& rowIndx, int const& colIndx, int const& num, string const& checkingFor){
    int instances = 0;

    int row;
    int rowPH;
    int col;
    int colPH;
    mkSqrVars(rowIndx, colIndx, rowPH, colPH);
    
    int stopRow=rowPH+3;
    int stopCol=colPH+3;
    if(checkingFor == "fNums"){
        for(row=rowPH; row<stopRow; row++){
            for(col=colPH; col<stopCol; col++){
                if(input[row][col].getFNum() == num){
                    return true;
                }
            }
        }
        return false;
    }else if(checkingFor == "pNums"){
        for(row = rowPH; row < stopRow; row++){
            for(col = colPH; col < stopCol; col++){
                if(input[row][col].PNumsContain(num)){
                    instances++;
                    if(instances > 1){
                        return true;
                    }
                }
            }
        }
        return false;
    }
}


bool rowContainsNum(subSquare input[9][9], int const& rowIndx, int const& num, string const& checkingFor){
    int instances = 0;
    if(checkingFor == "fNums"){
        for(int col = 0; col < 9; col++){
            if(input[rowIndx][col].getFNum() == num){
                return true;
            }
        }
        return false;
    }else if(checkingFor == "pNums"){
        for(int col = 0; col < 9; col++){
            if(input[rowIndx][col].PNumsContain(num)){
                instances++;
                if(instances>1){
                    return true;
                }
            }
        }
        return false;
    }
}


bool colContainsNum(subSquare input[9][9], int const& colIndx, int const& num, string const& checkingFor){
    int instances = 0;
    if(checkingFor == "fNums"){
        for(int row = 0; row < 9; row++){
            if(input[row][colIndx].getFNum() == num){
                return true;
            }
        }
        return false;
    }else if(checkingFor == "pNums"){
        for(int row = 0; row < 9; row++){
            if(input[row][colIndx].PNumsContain(num)){
                switch(instances){
                    case 0: instances++; break;
                    default: return true; break;
                }
            }
        }
        return false;
    }
}


void fullAssign(subSquare input[9][9], int const& rowIndx, int const& colIndx, int const& num){
    input[rowIndx][colIndx].assignFNum(num);

 
    for(int c = 0; c < 9; c++){
        if(input[rowIndx][c].PNumsContain(num)){
            input[rowIndx][c].removePNum(num);
        }
    }
   
    for(int r = 0; r < 9; r++){
        if(input[r][colIndx].PNumsContain(num)){
            input[r][colIndx].removePNum(num);
        }
    }

    int row;
    int rowPH;
    int col;
    int colPH;
    mkSqrVars(rowIndx, colIndx, rowPH, colPH);
    int stopRow = rowPH+3;
    int stopCol = colPH+3;
    for(row = rowPH; row < stopRow; row++){
        for(col = colPH; col < stopCol; col++){
            if(input[row][col].PNumsContain(num)){
                input[row][col].removePNum(num);
            }
        }
    }
}


void phase1(subSquare input[9][9]){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            for(int num = 1; num < 10; num++){
                
                if(input[row][col].getFNum() == 0){
                    if(!squareContainsNum(input, row, col, num, "fNums") &&
                     !rowContainsNum(input, row, num, "fNums") &&
                     !colContainsNum(input, col, num, "fNums")){
                       input[row][col].assignPNum(num);
                    }
                }
            }
        }
    }
}

void phase2(subSquare input[9][9]){
    int numbersAssigned = 0;
    do{
        numbersAssigned = 0;
        for(int row = 0; row < 9; row++){
            for(int col = 0; col < 9; col++){
                for(int num = 1; num < 10; num++){
                    if(input[row][col].getFNum() == 0 && input[row][col].PNumsContain(num)){
                        if( (input[row][col].getPNums().size() == 1) ||
                            (!squareContainsNum(input, row, col, num, "pNums") || 
                             !rowContainsNum(input, row, num, "pNums") || 
                             !colContainsNum(input, col, num, "pNums"))){
                                fullAssign(input, row, col, num);
                                numbersAssigned++;
                        }
                    }
                }
            }
        }
    }while(numbersAssigned);
}


void phase3(subSquare input[9][9]){
   
    subSquare savedState[9][9];
    cpyGrid(savedState, input);

    int guessRow;
    int guessCol;

    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(input[row][col].getFNum() == 0){
                guessRow = row;
                guessCol = col;
                row = 10;
                col = 10;
            }
        }   
    }

   
    int guesses = savedState[guessRow][guessCol].getPNums().size();

    
    int guessNum;
    
    int guessNumIndx = 0;
   
    subSquare TD[9][9][9];
   
    int numGuessGrids = 0;

    if(input[guessRow][guessCol].getPNums().size() > 0){
        while(guessNumIndx < guesses && gridUnsolved(input)){
            cpyGrid(input, savedState);
            guessNum = input[guessRow][guessCol].getPNums()[guessNumIndx];
            fullAssign(input, guessRow, guessCol, guessNum);
            phase2(input);
            if(gridUnsolved(input)){
             
                cpyGrid2(TD, input, guessNumIndx, "TO_3D");
                numGuessGrids++;
                guessNumIndx++;
            }else{
                guessNumIndx = guesses+1;
            }
            if(guessNumIndx == guesses){
               
                int i = 0;
                subSquare ss[9][9];
                cpyGrid(ss, savedState);
                while(gridUnsolved(ss) && i < numGuessGrids){
                    cpyGrid2(TD, ss, i, "TO_2D");
                    phase3(ss);
                    i++;
                }
                cpyGrid(input, ss);
            }
        }
    }
}

void solve(subSquare grid[9][9]){
    printf("Before solving: \n");
    readGrid(grid);
    phase1(grid);
    phase2(grid);
    if(gridUnsolved(grid)){
        phase3(grid);
    }
    if(!gridUnsolved(grid)){
        printf("Answer:\n");
        readGrid(grid);
    }else{
        printf("ERROR:Closest possible answer:\n");
        readGrid(grid);
    }
}

int main(){
    printf("Enter 'solve'\n");
    string str;
    cin >> str;
    cin.ignore();
    strToUpper(str);
    if(str=="SOLVE"){
        subSquare grid[9][9];
        createGrid(grid);
        solve(grid);
        return 1;
    }
    return 0;
}
