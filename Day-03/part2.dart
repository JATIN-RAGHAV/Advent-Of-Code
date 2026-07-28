import 'dart:io';
import 'dart:math';

int solve12(String s){
        int start = 0;
        int res = 0;
        for(var i = 11;i>=0;i--){
                int curr = 0;
                for(var j = start;j<s.length-i;j++){
                        curr = max(curr, int.parse(s[j]));
                }
                for(var j = start;j<s.length;j++){
                        if(int.parse(s[j]) == curr){
                                start = j+1;
                                break;
                        }
                }
                res += curr*pow(10, i).toInt();
        }
        return res;
}

void main(){
        final file = File("./text.txt");

        var data = file.readAsLinesSync();

        int res = 0;
        for(var i = 0;i<data.length;i++){
                res+=solve12(data[i]);
        }
        print(res);
}
