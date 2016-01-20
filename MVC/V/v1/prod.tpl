 
  
<div style="">

    {include   "abc.html"      }
    	 
    {foreach:users name="user"}
      		用户名是:{len(red('user.user_name'))} {blue(username)}   <br/>
      		
      		 
	{/endforeach}
	
	{foreach:users name="user"}
      		注册时间是: {red(username)} {user.user_regtime} {red(username)}<br/>
	{/endforeach}
	 <br/>
	
	   
</div>
	

	
 