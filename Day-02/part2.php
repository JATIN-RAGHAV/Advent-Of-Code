<?php

$data = file_get_contents("./text.txt");
$data = trim($data);
$ranges = explode(',',$data);
$response = 0;

// n is not included [0-n)
function give_ans($s, $e){
        $res = 0;
        for($x = $s ;$x<=$e;$x++){
                for($i = 2;$i<=strlen($x);$i++){
                        if((strlen($x) % $i) == 0){
                                $poss = true;
                                $len = (int)(strlen($x) / $i);
                                for($j = 1;$j<$i;$j++){
                                        if(substr($x,0,$len) != substr($x,$len*$j,$len)){
                                                $poss = false;
                                                break;
                                        }
                                }
                                if($poss){
                                        $res += $x;
                                        break;
                                }
                        }
                }
        }
        return $res;
}
foreach($ranges as $i => $v){
        list($start, $end) = explode('-',$v);
        $start = (int)$start;
        $end = (int)$end;
        $response += give_ans($start,$end);
}
printf("Response as it turns out is: %d\n",$response);
