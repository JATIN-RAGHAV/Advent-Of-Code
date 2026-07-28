#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

using shape = vector<vector<bool>>;
int shape_dimen = 3;

struct row {
        int x;
        int y;
        vector<int> req;
};

template<typename T>
ostream& operator<<(ostream& os,vector<T> a){
        if(!a.size()){
                os<<"[]";
        }
        else{
                os<<'['<<a[0];
                for(int i = 1;i<a.size();i++){
                        os<<','<<a[i];
                }
                os<<"]\n";
        }
        return os;
}

void print_shape(shape s){
        for(int i = 0;i<s.size();i++){
                for(int j = 0;j<s[0].size();j++){
                        putchar(s[i][j]? '#':'.');
                }
                putchar('\n');
        }
}

int find_size(shape s){
        int res = 0;
        for(int i = 0;i<shape_dimen;i++){
                for(int j = 0;j<shape_dimen;j++){
                        if(s[i][j])res++;
                }
        }
        return res;
}

void print_grid(row r){
        printf("%d * %d\n",r.x,r.y);
        fflush(stdout);
        std::cout << r.req;
}

int main(){
        ifstream file("./text.txt");
        string s;
        vector<shape> shapes;
        vector<row> rows;
        while(std::getline(file,s)){
                if(s.find("x") == string::npos){
                        shape curr{};
                        string ss;
                        for(int i=0;i<shape_dimen;i++){
                                vector<bool> row;
                                std::getline(file,ss);
                                for(int j = 0;j<shape_dimen;j++){
                                        row.push_back(ss[j] == '#');
                                }
                                curr.push_back(row);
                        }
                        shapes.push_back(curr);
                        std::getline(file,s);
                }
                else{
                        stringstream ss{s};
                        row curr{};
                        char c;
                        ss>>curr.x>>c>>curr.y>>c;
                        int z;
                        for(int i = 0;i<shapes.size();i++){
                                ss>>z;
                                curr.req.push_back(z);
                        }
                        rows.push_back(curr);
                }
        }
        int res = 0;
        for(auto r:rows){
                int required_area = 0;
                for(int i = 0;i<shapes.size();i++){
                        required_area += find_size(shapes[i])*r.req[i];
                }
                if(required_area < r.x*r.y){
                        res++;
                }
        }
        cout<<"Answer is: " << res<<'\n';
}
