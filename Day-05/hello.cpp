

#include <iostream>
int state_less_func(int x){
        return 2*x;
}

int state_full_func(int x){
        static int z{1};
        z++;
        std::cout<<z<<'\n';
        return x*z;
}

int main(){
        for(int i = 0;i<10;i++){
                std::cout<<state_less_func(1)<<'\n';
        }

}
