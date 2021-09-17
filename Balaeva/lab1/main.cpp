#include <vector>
#include <ctime>
#include <iostream>

int bestNum = 0;


class Table // исходный квадрат
        {
    int size;
    std::vector<std::vector<int>> table;
    int count;

        public:
            Table(int size): size(size), table(size, std::vector<int>(size, 0)), count(0) {
                if(size != 0) {
                    constTable();
                }
            }
            Table(Table const &other): size(other.size), table(other.size, std::vector<int>(other.size, 0)), count(other.count) {
                for (int i = 0; i < size; i++)
                    for (int j = 0; j < size; j++)
                        table[i][j] = other.table[i][j];
            }
            Table& operator=(Table const &other){
                if(&other != this){
                    Table tmp(other);
                    count = tmp.count;
                    size = tmp.size;
                    table.swap(tmp.table);
                }
                return *this;
            }
            ~Table(){}
            void best_(int k){

                if( k==2){
                    bestNum = 4;
                }
                else if (  k==3)
                {
                    bestNum = 6;
                }
            }

            void constTable(){
                int temp = size/2;
                if(size%2==0){
                    best_(2);
                }
                else if(size%3==0){
                    best_(3);
                } else{
                    insertTable(0, 0, temp + 1);
                    insertTable(0, temp + 1, temp);
                    insertTable(temp + 1, 0, temp);

                }
            }

            int getnumber(){
                return count;
            }
            int getsize(){
                return size;
            }

            bool isPossible(int i, int j, int n){
                if((i + n) > size || (j + n) > size){
                    return false;
                }
                for(int y = i; y < i + n; y++)
                    for (int x = j; x < j + n; x++)
                        if(table[y][x] != 0){
                            return false;
                        }
                return true;
            }
            void insertTable(int i, int j, int n){
                for(int y = i; y < i + n; y++){
                    for (int x = j; x < j + n; x++){
                        table[y][x] = n;
                    }
                }
                ++count;
                std::cout<<"Current best partition:"<<count<<std::endl;
            }
            bool checkSpace(int i){
                for(int y = i; y < size; y++)
                    for (int x = 0; x < size; x++)
                        if(table[y][x] == 0)
                            return true;
                        return false;
            }
            int findi(int i){
                for (int y = i; y < size; y++)
                    for (int x = 0; x < size; x++)
                        if (table[y][x] == 0){
                            return y;
                        }
            }
            int findj(int i){
                for (int y = i; y < size; y++)
                    for (int x = 0; x < size; x++)
                        if (table[y][x] == 0){
                            return x;
                        }
            }
            void deleteTable(int i, int j){
                int val = table[i][j];
                for (int y = i; y < i + val; y++)
                    for (int x = j; x < j + val; x++)
                        table[y][x] = 0;
            }
            void result(){
                for(int i = 0; i < size; i++){
                    for(int j = 0; j < size; j++){
                        if(table[i][j] != 0){
                            std::cout << i + 1 << " " << j + 1 << " " << table[i][j] << std::endl;

                        }
                    }
                }
            }
            void shower_table(){
                if(size%2==0){
                    insertTable(0,0, size/2);
                    insertTable(0,size/2, size/2);
                    insertTable(size/2,size/2, size/2);
                    insertTable(size/2,0, size/2);
                }
                else if(size%3==0){
                    insertTable(0,0, (2*size)/3);
                    insertTable((2*size)/3, 0 , size/3);
                    insertTable(0, (2*size)/3, size/3);
                    insertTable((2*size)/3, (2*size)/3, size/3);
                    insertTable(size/3, (2*size)/3, size/3);
                    insertTable((2*size)/3, size/3, size/3);

                }

                for (int i = 0; i < size; ++i) {
                    std::cout<<"\n";
                    for (int j = 0; j < size; ++j) {
                        std::cout<<table[i][j]<<" ";
                    }
                }
                std::cout<<"\n";
            }
        };

Table best(0);

Table backTracking(Table table, int i, int j, int pr){
    for(int n = table.getsize() / 2; n > 0; n--){
        for(int l=0; l < pr; l++)
            std::cout << " ";
        std::cout<<"The considered length of the square ="<<n<<std::endl;
        if(table.getnumber() > bestNum){
            for(int l=0; l < pr; l++)
                std::cout << " ";
            std::cout<<"The current option is not minimal"<<std::endl;
            return table;
        }
        Table shape = table;
        if(shape.isPossible(i, j, n)){
            for(int l=0; l < pr; l++)
                std::cout << " ";
            std::cout<<"established square:"<< n <<std::endl;
            shape.insertTable(i, j, n);
            if(shape.checkSpace(i)){
                for(int l=0; l < pr; l++)
                    std::cout << " ";
                std::cout<<"Entering recursion"<<std::endl;
                shape = backTracking(shape, shape.findi(i), shape.findj(i),pr+1);
                shape.shower_table();
                for(int l=0; l < pr; l++)
                    std::cout << " ";
                std::cout<<"Exiting recursion"<<std::endl;
            }
            else if(bestNum >= shape.getnumber()){
                best = shape;
                bestNum = shape.getnumber();
            } else{
            }
        }
    }
    return table;
}

void res (int size, int k){

    if(k==2){
        int temp = size/2;
        std::cout << "4" << std::endl;
        std::cout << "1 1 " << temp << std::endl;
        std::cout << temp+1 << " 1 " << temp << std::endl;
        std::cout << "1 " << temp+1 << " " << temp << std::endl;
        std::cout << temp+1 << " " << temp+1 << " "<< temp << std::endl;
    }
    else if(k==3){
        int temp = size/3;
        std::cout << "6" << std::endl;
        std::cout << "1" << " 1 " << temp*2 <<  std::endl;
        std::cout << "1 " << 1+temp*2 << " " << temp <<  std::endl;
        std::cout << 1+temp << " " << 1+temp*2 << " " << temp <<  std::endl;
        std::cout << 1+temp*2 << " 1 "  << temp <<  std::endl;
        std::cout << 1+temp*2 << " " << 1+temp << " "  << temp <<  std::endl;
        std::cout << 1+temp*2 << " " << 1+temp*2 << " " << temp << std::endl;
    }

}




int main(){
    int size = 0;
    std::cin >> size;
    clock_t start = clock();
    bestNum = size * size;
    Table A(size);
    A = backTracking(A, A.findi(0), A.findj(0),0);
    clock_t end = clock();
    if(size%2==0){
        res(size, 2);
    } else if(size%3==0){
        res(size, 3);
    } else {
        std::cout << "Best partition:"<< bestNum << std::endl;
        best.result();
    }
    if(size%2==0 || size%3==0 ){
        A.shower_table();
    }
    else
        best.shower_table();
    std::cout << "Lead time: " << (double )(end - start) / CLOCKS_PER_SEC << "\n";
    return 0;
}
