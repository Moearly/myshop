<?php 

// 通用web函数

function GET($pname,$method="get")
{
	$plist=$method=="get"?$_GET:$_POST;
	if(isset($plist[$pname]))
	{
		$getValue=trim($plist[$pname]);
		$getValue=str_replace(array("gcd"),"",$getValue);
	 
		return $getValue;
	}
	else
		return false;
}

function IP()
{
 
		if(!empty($_SERVER["HTTP_CLIENT_IP"])){
		  $cip = $_SERVER["HTTP_CLIENT_IP"];
		}
		elseif(!empty($_SERVER["HTTP_X_FORWARDED_FOR"])){
		  $cip = $_SERVER["HTTP_X_FORWARDED_FOR"];
		}
		elseif(!empty($_SERVER["REMOTE_ADDR"])){
		  $cip = $_SERVER["REMOTE_ADDR"];
		}
		else{
		  $cip = "";
		}
		return $cip;
	 
		 
 
}
function set_cache($key,$value,$expire)
{
	$m=new Memcache();
	$m->connect(Cache_IP,Cache_Port);
	$m->set($key,$value,0,$expire);
	
}
function get_cache($key)
{
	 //获取缓存
	$m=new Memcache();
	$m->connect(Cache_IP,Cache_Port);
	return $m->get($key);
}
function load_model($mName)
{
	//加载一个模块
	return new _Model($mName);
}

function load_lib($lib,$libName)
{
	//后缀必须是php
	require("Lib/".$lib."/".$libName.".php");
}


?>