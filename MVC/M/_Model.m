<?php

 class _Model
 {
 	var $_modelName="";
	var $_db=false;
	var $_result=false;
 	function _Model($mName)
	{
		//$mName 暂时代表 数据表名  譬如 传入 user ，不用加前缀
		$this->_modelName=DB_Prefix."_".$mName; // user=> shop_user
		$this->modelInit();//初始化NotOrm  这一步是必须的
	}
	function modelInit()
	{
	load_lib("db","NotORM");
		//m的初始化 
		$structure = new NotORM_Structure_Convention(
		    $primary = 'id',  //这里告诉notorm 我们的主键都是id 这种英文单词
		    $foreign = '%sid',  //同理，外键都是 外表名+id    这个很重要，否则notorm拼接sql的时候会拼错。
		    $table = '%s',
		    $prefix =''
		);
		
		$pdo = new PDO(DB_DSN,DB_User,DB_UserPass);
		$this->_db=new NotORM($pdo,$structure); //初始化
	} 
	function loadall() //加载 。 只会加载一条
	{
			$tbName=$this->_modelName;//表名
		$this->_result=$this->_db->$tbName();
	}
	function load($where) //加载 。 只会加载一条
	{
	
		$tbName=$this->_modelName;//表名
		if(trim($where)=="") return false;//禁止程序员 没有任何条件的 加载全表
		$this->_result=$this->_db->$tbName()->select(" * ")->where($where)->limit(1);
	}
	function __get($pname)
	{
		 
	  if($this->_result && count($this->_result)==1   )
	  {
	  	
	  	$ret=$this->_result->fetch();//取第一行
	  	 return $ret[$pname];
		 
	  }
	  return false;
	}
	function all()
	{
		return 	$this->_result;
	}
 }

?>