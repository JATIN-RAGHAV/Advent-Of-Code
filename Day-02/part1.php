<?php

$data = file_get_contents("./text.txt");
$data = trim($data);
$ranges = explode(',',$data);
$response = 0;

// n is not included [0-n)
function give_ans($n){
        $res = 0;
        $curr = 9;
        for($i = 1;$i<strlen($n)/2;$i++){
                $num = "";
                for($j = 0;$j<$i;$j++){
                        $num = $num . "9";
                }
                $num = (int)$num;
                $x = ($num*($num+1))/2;
                $num = (int)($num/10);
                $x -= ($num*($num+1))/2;
                $res += $x * (pow(10,$i) +1 );
        }
        if(strlen($n) % 2 == 0){
                for($i = 1*pow(10,(strlen($n)/2)-1);$i.$i<$n;$i++){
                        $res += $i*(1+pow(10,strlen($i)));
                }
        }
        return $res;
}
foreach($ranges as $i => $v){
        list($start, $end) = explode('-',$v);
        $start = (int)$start;
        $end = (int)$end;
        $response += give_ans($end+1) - give_ans($start);
}
printf("Response as it turns out is: %d\n",$response);
