<?php
/**
 * Created by PhpStorm.
 * User: Administrator
 * Date: 2016/1/21
 * Time: 18:07
 */

$raw = '12. 8. 1992';
$start = DateTime::createFromFormat('d. m. Y',$raw);
echo 'start date:'.$start->format('Y-M-d')."\n";//这里的M--m(英文，还是数字)也是会有区别的--详情查看format函数
echo "<br/>";

$end = clone $start;
$end->add(new DateInterval('P1Y1M6D'));//定义一个时间距离--P + (D多少天)(Y多少年)(M多少月)
$diff = $end->diff($start); //两个时间做差值

echo 'Difference'.$diff->format('%y year, %m month, %d days (total: %a days)') . "\n"; //a--表示总共的天数---注意大小写得区别Y--01 ,y--1(其他同理--格式化的区别)

echo "<br/>";
//3.DateTime对象之间的直接比较
if ($start < $end) {
    echo "start Time more litter";
}

//4.DatePeriod--循环的事件进行迭代--传入开始时间、结束时间和间隔区间--得到--这其中所有的事件
$periodInt = DateInterval::createFromDateString("first thursday");
$periodIterator = new DatePeriod($start,$periodInt,$end,DatePeriod::EXCLUDE_START_DATE);//去除开始时间
foreach ($periodIterator as $item) {
    echo $item->format('Y-m-d') . ' ';//输入1992-8-13到1993-09-16//
}

