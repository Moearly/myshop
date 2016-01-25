<?php

    //1.测试错误抑制操作符
    $a = @(57/0);
    echo $php_errormsg;
    echo '<br />';
    //2.使用可变函数
    $var = 56;
    echo gettype($var);
    settype($var, 'double');
    echo gettype($var);
    echo is_double($var);
    echo '<br />';

//    echo isset($var);
//    echo isset($var);
    echo isset($var);
    unset($var);

    echo empty($var);
