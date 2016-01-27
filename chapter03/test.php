<?php
/**
 * Created by PhpStorm.
 * User: Administrator
 * Date: 2016/1/27
 * Time: 16:50
 */

$odd = range(1,10,2);
echo $odd[2]."<br/>";

$productsv = array('Tires', 'oil', 'spark');

$productsv[3] = 'Fues';
//echo $productsv[4];

//echo  "$productsv[4]";

for ($i = 0; $i < 4; $i++) {
    echo $productsv[$i].' ';
}


foreach ($productsv as $item) {
    echo $item." ";
}

echo '<br/>';
$price = array('a'=>100,'b'=>200,'c'=>40);
$price['b'] = 2;

echo $price['b'];

foreach ($price as $key => $value) {
    echo $key.' - '.$value.'<br/>';
}