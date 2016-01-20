<?php
/**
 * Created by PhpStorm.
 * User: Administrator
 * Date: 2016/1/20
 * Time: 15:45
 */
include("conf.php");//加载全局的变量配置

require("Common/functions.php"); //加载全站 函数文件
require("MVC/C/_Main.c");//加载control主文件---实现controller控制器
require("MVC/M/_Model.m");//加载Model主文件---实现model管理

//路由判断功能
$get_control=isset($_GET["control"])?trim($_GET["control"]):"index";
$get_action=isset($_GET["action"])?trim($_GET["action"]):"index";

if(file_exists("MVC/C/".$get_control.".c"))
{
    require("MVC/C/".$get_control.".c");
    $control=new $get_control();
    if( method_exists ($control,$get_action))
    {
        $control->$get_action();
        $control->run();
    }
}
