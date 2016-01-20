<?php
 class index extends _Main
 {
 	
	 
	 function getindex()
	 {
	 	//模板加载 在这个函数里
	 	$this->setViewName("prod");
		
	/*	$this->setCacheEnabled(60);

		if(!$this->inCache())
		{
			  $this->addObject("prod","我的第一个商品");
		}*/
		
	 $m=load_model("user"); //加载用户 表
		$m->loadall();
		
		$this->addObject("users",$m->all()); 
		$this->addObject("username","我的名字");
		
		$this->isFileCache=true;//保存到文件中
		 
		 
	 }
 }
?>