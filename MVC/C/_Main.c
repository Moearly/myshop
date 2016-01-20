<?php
function red($str)
{
	return "<font color='red'>".$str."</font>";
}
function blue($str)
{
	return "<font color='blue'>".$str."</font>";
}
function len($str)
{
	return $str."的长度是".strlen($str);
}
$foreach_id=array();
 function foreach_callback($match)
 {
 	$id=md5(uniqid());
	global $foreach_id;
	$foreach_id[]=$id;
 	return "{".$match[1].":".$match[2].":".$id;
 }
 class  _Main
 {
 	var $_viewName="index";
	var $_objectList=array();//变量数组
	var $_cacheTime=0;//假设是0 的话 没有缓存处理
	var $isFileCache=false;//是否保存文件缓存
	
	function setCacheEnabled($cachetime=60)
	{
		if($cachetime>0)
		  $this->_cacheTime=$cachetime;// 设置缓存时间
	}
	function inCache()//当前缓存是否生效
	{
		if(get_cache($this->_viewName))
		 return true;
		return false;
	}
 	function addObject($objName,$objValue)
 	{
 	  $this->_objectList[$objName]=$objValue;
 	}
	function setViewName($vname)
	{
		//设置 view的名称
		$this->_viewName=$vname;
	}
	
	function run()
	{
		
		if($this->_cacheTime>0)  //代表要从缓存里面获取内容
		{
			 
			$getVars=get_cache($this->_viewName);
			if($getVars)
			{
				//echo "使用了缓存";
				$this->_objectList=$getVars;
				extract($getVars);
			}
			else{
				set_cache($this->_viewName, $this->_objectList, $this->_cacheTime);
				extract($this->_objectList);
			}
		}
		else
		 {
				extract($this->_objectList);//.解包变量
		 }
		
		 
		 ob_start();
		
		include("MVC/V/".Current_ViewPath."/head.tpl");//加载头模板
		
		include("MVC/V/".Current_ViewPath."/".$this->_viewName.".tpl"); //加载业务模板 
		
		include("MVC/V/".Current_ViewPath."/footer.tpl");//加载尾模板
	 
	   $getCnt=ob_get_contents();
	   ob_clean();
		 
		  
		   
		   if($this->isFileCache) //静态文件缓存标识 开启
		   {
		   	  //第一步， 判断 文件缓存中是否有该文件
		   	  $fileName=md5($_SERVER["REQUEST_URI"]);
			  if(file_exists(Cache_Path.$fileName))
			  {
			  	echo "使用了文件缓存";
			  	include(Cache_Path.$fileName);// 直接加载 文件缓存
			  }
			  else
			  	{
			  		$getCnt=$this->genTpl($getCnt);
			  		file_put_contents(Cache_Path.$fileName, $getCnt);
					
					echo $getCnt;
			  	}
		   }
		   else
		   echo $this->genTpl($getCnt);
	}
 
 	 function genTpl($getCnt) //解析最终模板
	 {
	 	$getCnt=$this->genInclude($getCnt);//解析include 方法
	  
	  $getCnt=$this->genForeach($getCnt);//首先解析循环
	  
	   $getCnt=$this->genSimpleVars($getCnt);//然后解析简单变量
	   return $getCnt;
	 }
	 function genInclude($getCnt)//解析include 方法
	 {
	 	$pattern="/{include\s+\"([\w\.]{1,30})\"\s*}/is";
	 	if(preg_match_all($pattern,$getCnt,$result))
		{
			 
			$result=$result[1];
			foreach($result as $r)
			{
			 
				if(file_exists(Include_Path.$r))
				{
				 
					//include(Include_Path.$r);
					$getFile=file_get_contents(Include_Path.$r);
				 
				    $pattern="/{include\s+\"".$r."\"\s*}/is";
				 
					$getCnt=preg_replace("/{include\s+\"".$r."\"\s*}/is", $getFile, $getCnt);
				}
			}
			
		}
		return $getCnt;
		
	 }
	 function replaceForeachVar($cnt,$varName,$row)
	 {
	 	//替换循环 内部内容
	  
	 	if(preg_match_all("/{([^{]*?".$varName."\.(?<varValue>\w{1,30})[^}]*?)}/is", $cnt,$result))
		{
			 
			 $varValue=$result["varValue"][0];
			 $result=$result[1]; 
			
		 
			 foreach($result as $r)
			 {
			  
			 	if($row[$varValue])
				{
					
					if($varName.".".$varValue==trim($r))  //代表没有函数
					{
						$cnt=preg_replace("/{".$varName."\.".$varValue."}/is",
					 $row[$varValue], $cnt);
					}
					else{//代表有函数
					
						$newr=preg_replace("/".$varName."\.".$varValue."/is",
						 $row[$varValue], $r);
					 
						eval('$last='.$newr.";");
						if($last){
							 
							$cnt=str_replace("{".$r."}",
					 $last, $cnt);
						}
					}
					
				}
				 
			 }
		}
		return $cnt;
	 }
	 function genForeach($tplCnt)
	 {
	 	global $foreach_id;
		//对每一个foreach 加上一个唯一标示符
		 
		$tplCnt=preg_replace_callback("/{(foreach):([a-zA-Z]{1,30})/is","foreach_callback",$tplCnt);
	  	foreach($foreach_id as $fid)
		{
			if(preg_match_all("/{foreach:(?<varObject>[a-zA-Z]{1,30}?):".$fid."\s+name=\"(?<varName>[a-zA-Z]{1,30}?)\"}/is", $tplCnt,$result))
			{
				$finalResult="";
				$varObject=$result["varObject"][0];
				$varName=$result["varName"][0];
				
				if(array_key_exists($varObject, $this->_objectList)) 
				{
					$pattern="/{foreach:".$varObject.":"
						.$fid."\s+.*?}(?<replaceCnt>.*?){\/endforeach}/is";
					 
						preg_match($pattern, $tplCnt,$cntReuslt);
					 
						$cntReuslt=$cntReuslt["replaceCnt"];//需要被替换的内容
						
					foreach($this->_objectList[$varObject] as $row)
					{    
					 	 $tmp=$this->replaceForeachVar($cntReuslt,$varName,$row);
						 $finalResult.=$tmp;
						 
					}
				}
				 //echo $finalResult;exit();
				//替换最终的某个 foreach的值
				$tplCnt=preg_replace('/{foreach:'.$varObject.':'
				.$fid.'\s+.*?}.*?{\/endforeach}/is', $finalResult, $tplCnt); 
			 
			} 
		}
	 
	//	var_export($foreach_id);
	 	return  $tplCnt;
	 }
	function genSimpleVars($tplCnt)//解析简单变量
	{
		if(preg_match_all("/{(?<varObject0>[^\{]*?\((?<varObject1>\w{1,30})\)[^\}]*?)}|\{(?<varObject2>\w{1,30})\}/is", $tplCnt,$result))
		{
		 
			$varObject0=$result["varObject0"];
			 $varObject1=$result["varObject1"];
			 $varObject2=$result["varObject2"];
			 
			$result=$result[0];
			 foreach($result as $r)
			 {
			 	$var0=current($varObject0);
			    $var1=current($varObject1);
				$var2=current($varObject2);
				$getVar=$var1==""?$var2:$var1;
				if($getVar=="") $getVar=$var0;
			 
				if("{".$getVar."}"==$r)
				{
				
					if(array_key_exists($getVar, $this->_objectList))
					{
						$tplCnt=preg_replace("/".$r."/is", $this->_objectList[$getVar], $tplCnt);
						
					}
				}
				else
					{
						if(array_key_exists($getVar, $this->_objectList))
						{
							$newr=str_replace($getVar,$this->_objectList[$getVar],$r);
						    $newr=str_replace(array("{","}"),"",$newr);
							eval('$last='.$newr.";");
							if($last)
							{
								$tplCnt=str_replace($r,$last,$tplCnt);
							}
						}
					}
			 	next($varObject0);
				next($varObject1);
				next($varObject2);
			 }
			 return  $tplCnt;
		}
		else
			return $tplCnt;
		
	}
	 
 }
?>