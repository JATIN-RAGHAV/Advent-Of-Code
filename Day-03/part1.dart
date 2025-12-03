import 'dart:io';
import 'dart:math';

int solve(String s){
        int tens = 0;
        int ones = 0;
        for(var i = 0;i+1<s.length;i++){
                tens = max(int.parse(s[i]),tens);
        }
        for(var i = 0;i<s.length;i++){
                if(int.parse(s[i]) == tens){
                        i++;
                        for(;i<s.length;i++){
                                ones = max(int.parse(s[i]), ones);
                        }
                }
        }
        return tens*10 + ones;
}

void main(){
        final file = File("./text.txt");

        var data = file.readAsLinesSync();

        int res = 0;
        for(var i = 0;i<data.length;i++){
                res+=solve(data[i]);
        }
        print(res);
}
