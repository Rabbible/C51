/*
   以微秒级的高电平再转为低电平信号来控制舵机转到指定角度..模拟舵机要持继发信号直到目标角度..
   1000逆时针方向，2000顺时针方向，1500在中间。舵机通常响应500到2500间的值
    500微秒----------0度；   1秒=1000毫秒，1毫秒=1000微秒
   1000微秒---------45度；
   1500微秒---------90度；
   2000微秒--------135度；
   2500微秒--------180度；

   SG90  空载速度：0.12秒/60度(4.8V) = 120毫秒60度 = 2毫秒1度 = 2000微秒1度
   TS90A 空载速度：0.09秒/60度(4.8V)
   TS90D 
   MG90S 空载速度：0.11秒/60度(4.8V)
   MG90M

   注意:电脑USB3.0输出5V900ma电流，，USB2.0输出5V500ma电流....
   建议插在电脑USB3.0口调试代码
   SG90 工作电压4.8V~6V  待机5ma,工作电流300ma..    堵转扭矩:1.2~1.4公斤/厘米(4.8V)
   TS90A工作电压4.8V~6V  待机5ma,空载60ma,堵转750ma,堵转扭矩:1.6~1.8公斤/厘米(4.8V)
   MG90S工作电压4.8V~6V  待机8ma,工作电流300ma..    堵转扭矩:1.8~2.0公斤/厘米(4.8V)  

   舵机三根电线  黄线->接信号(D0~D8),红线->接正极(5V),褐线->接负极(G)
//--------------------------------------------
   360度舵机与180度舵机不同,180度舵机是给一个特定的PWM信号,舵机会转到相应的角度.
   360度舵机不能控制角度旋转,只能够控制方向和旋转转速,所以360度舵机给定一个PWM,会以特定的速度和方向转动。
   PWM信号与360舵机转速的关系：
   0.5ms----------------正向最大转速；
   1.5ms----------------速度为0；
   2.5ms----------------反向最大转速；

淘宝店铺 创客与编程            https://shop104415339.taobao.com/
4轴机械臂 https://item.taobao.com/item.htm?ft=t&id=634846120104
5轴机械臂 https://item.taobao.com/item.htm?ft=t&id=638328575007
6轴机械臂 https://item.taobao.com/item.htm?ft=t&id=637592400765
TIANKONGRC舵机 https://item.taobao.com/item.htm?ft=t&id=637949946243
*/
int servopin= D8;            //把舵机信号线接到开发板D8数字口
int oldkok =  90;            //保存每次转动舵机后的角度值
int olddms =1500;            //保存每次转动舵机后的脉宽值

//-----------------------------------------------------------------------
//舵机对信号是单向处理的,可以发命令给舵机要求转到某个角度.
//但舵机有没有转到那个位置和目前的状态是不会返回给我们的..
//所以需要自已用变量保存上次的角度与现在要转到的角度..
//----------------------函数 Servo180( )----用脉宽的方式控制舵机转动---------
void Servo180(int pin,int Value) {  //脉宽可由0.5ms 到2.5ms 之间，脉宽和舵机的转角0°～180°相对应
  int kok=0;                           //转到角度
  int dms=0;                           //脉宽微秒,,微秒与角度映射对应..

  if(Value>300) {                      //Value>300视作脉宽.<300视作角度
     dms=constrain(Value,500,2500);    //返回限制的 脉宽 值为500与2500范围之间
     kok=map(dms,500,2500,0,180);      //数值映射 500=0度,1500=90度,2500=180度
  } else {
     kok=constrain(Value,0,180);       //返回限制的 角度 值为0与180范围之间的值
     dms=map(kok,0,180,500,2500);      //数值映射 0度=500,90度=1500,180度=2500
  }
  
  //------------以脉宽方式平滑转动舵机--------------------------------------
  int Step = 8;                        //每次步进8个信号,值越大舵机转得越快,值越小转动越慢越平滑.
  while(abs(olddms-dms)>Step){         //用循环递增递减 高低电平 ms 信号,平滑伺服电机转动到目标角度.减少抖动
    if(olddms>dms){
      olddms=olddms-Step;
    }
    if(olddms<dms){
      olddms=olddms+Step;
    }
    digitalWrite(pin,HIGH);             //高电平信号
    delayMicroseconds(olddms);          //微秒  等待
    digitalWrite(pin, LOW);             //低电平信号
    delayMicroseconds(20000-olddms);    //微秒  等待 PWM脉冲信号(高电平+低电平)周期为20000微秒=20毫秒=0.02秒
    delay(0);                           //yield()=delay(0)延时可避免长时间循环触发看门狗重启开发板.Soft WDT reset
    //循环超过500MS易触发看门狗重启开发板..重置看门狗计数 ESP.wdtFeed();禁止看门狗 ESP.wdtDisable() 超过5秒触发硬件看门狗
  }

  //--------------绝对定位-----------------------------------
  for(int i=6;i;i--){                   //循环发送6次高低电平方波信号给电机,注意:次数少则电机可能捕获不到信号
    digitalWrite(pin,HIGH);             //高电平信号
    delayMicroseconds(dms);             //微秒  等待
    digitalWrite(pin, LOW);             //低电平信号
    delayMicroseconds(20000-dms);       //微秒  等待
    delay(0);
  }
  
  //Serial.printf("角度:%d  微秒:%d  角度差:%d\n",kok,dms,kok-oldkok);
  oldkok=kok;                           //保存新的角度
  olddms=dms;                           //保存新的脉宽
}


//-----------------------------------------------------------------------
//
//
//
//------------------开发板通电后初始函数 setup()----------------------------
void setup() {  //setup 在开发板通电后最先被调用一次.这里可以初始化一些功能或数据
    Serial.begin(115200);                   //初始化串口 波特率115200或9600
    Serial.println("\nEsp8266.setup"); 
    
    pinMode(LED_BUILTIN , OUTPUT);          //初始化Mini ESP8266开发板有LED的GPIO口
    digitalWrite(LED_BUILTIN,LOW);          //Mini ESP8266板LED_BUILTIN=D4=GPIO 2,LOW=亮灯,HIGH=灭灯

    //---------------------舵机控制代码-----------------------------------
    pinMode(servopin,OUTPUT);               //设置舵机所接的针脚为输出模式

    for(int i=0;i<=180;i++){                //角度方式控制舵机从0度转到180度
      Servo180(servopin,i);                 //发送角度值转动舵机
    }
    for(int i=180;i>0;i--){                 //再次让舵机从180度转到0度
      Servo180(servopin,i);
    }
    Servo180(servopin,90);                  //直接指定90度,让舵机快速转过来...

/*
  //用高低电平脉冲微秒时间宽度方式控制舵机.比角度更精确平滑.每1角度约等于11.11微秒脉宽
    for(int i=500;i<=2500;i++){           //500脉宽=0度,1500=90度,2500=180度
      Servo180(servopin,i);               //发送脉冲微秒值转动舵机到180度
    }
    for(int i=2500;i>500;i--){         
      Servo180(servopin,i);               //发送脉冲微秒值转动舵机到0度
    }
    Servo180(servopin,1500);              //发送脉冲微秒值转动舵机回到90度
*/


  //设置数字针脚D6(GPIO 12),D7(GPIO 13)输入按键信号....供 loop  检测按键开关用..
  //注意:开发板数字接口 D? = 芯片GPIO ? 请查看自已手里开发板的pin接口说明
    pinMode(D6,INPUT_PULLUP); //若按下时输入高电平则用 INPUT=输入
    pinMode(D7,INPUT_PULLUP); //若按下时输入低电平则用 INPUT_PULLUP=输入上拉

    Serial.println("Esp8266.end");
}




//-----------------------------------------------------------------
// 双轴按键摇杆 PS2游戏摇杆控制杆传感器JoyStick. 针脚向下时:X上加下减,Y左减右加..针脚向右时:X左加右减,Y上加下减..
// VRX,接模拟口
// VRY,接模拟口.
//  SW,接数字口.轻按输入=1,弹起=0,按到底=0
//------------------开发板循环调用函数 loop()------------------------
void loop() {                   //loop 开发板会一直循环调用这个loop...

  //Serial.print("old:");
  //Serial.println(oldkok, DEC);//串口输出之前写入舵机的角度值

  //---------------------双轴摇杆控制舵机转向-----------------
/*
  int X=analogRead(0);                   //读取A0模拟值..先把摇杆信号线插到A0接口
  Serial.print("X:");
  Serial.println(X, DEC);
  if(X<300 && oldkok>0){                 //摇杆向左..3.3V居中时:X=517,Y:557
      Servo180(servopin,oldkok-1);       //左转1度
  }if(X>700 && oldkok<180){              //摇杆向右..3.3V居中时:X=517,Y:557
      Servo180(servopin,oldkok+1);       //右转1度
  }*/


  //---------------------检测数字 D7=GPIO 13,D6=GPIO 12有无按钮开关输入低电平信号----------
/*
  Serial.print("D6=GPIO 12:");
  Serial.println(digitalRead(D6), DEC);
  Serial.print("  ,D7=GPIO 13:");             //注意:数字接口 D? = GPIO ? 请查看自已手里开发板接口说明
  Serial.print(digitalRead(D7), DEC);

  if(!digitalRead(D6) && oldkok>0){           //D6号针脚输入低电平,摇杆向左.若判断高电平,删掉!感叹号即可
       Servo180(servopin,oldkok-1);           //左转1度      
  }
  if(!digitalRead(D7) && oldkok<180){         //D7号针脚输入低电平,摇杆向右.若判断高电平,删掉!感叹号即可
       Servo180(servopin,oldkok+1);           //右转1度
  }
*/

   //---------------监听电脑串口输入指令-------------------
  if(Serial.available()>0){                   //有指令数据>0字节
    String t=Serial.readString();             //? X
    Command(t);                               //解析拼执行命令
  }
  //-----------------------------------------------------------------
}


//------------------------------------------------------------------------
//
//
//
//-----------------解析拼执行命令 已定义常用命令 ? X----------------
void Command(String t)  {              

    t.trim();                               //删首尾空格换行
    t.toUpperCase();                        //指令转为大写
    Serial.println(t);                      //显口输出指令

    if('?'==t.charAt(0)){                           //解析第一个字符为 ? 指令
        Serial.println("X++ 执行后X电机角度+1度");    //Y++ Z++ E++
        Serial.println("X-- 执行后X电机角度-1度");    //Y-- Z-- E--
        Serial.println("X+? 执行后X电机相对+N度");    //Y+1 Z+3 E+8
        Serial.println("X-? 执行后X电机相对-N度");    //Y-2 Z-5 E-9
        Serial.println("X?? 执行后X电机绝对到N度");   //Y10 Z30 E90
    } else if('X'==t.charAt(0)){              //解析第一个字符为X指令
        int   v=0;                            //v变量保存新角度值
        if(t.charAt(2)=='-'){                 //X--    第3个字符
          v=oldkok-1;                         //新角度=旧角度-1度
        } else if (t.charAt(2)=='+'){         //X++    第3个字符
          v=oldkok+1;                         //新角度=旧角度+1度
        } else if (t.charAt(1)=='-'){         //X-?    第2个字符
          t=t.substring(2);                   //提取第3个字符与后面的数字内容
          v=oldkok-t.toInt();                 //新角度=旧角度-N度
        } else if (t.charAt(1)=='+'){         //X+?    第2个字符
          t=t.substring(2);                   //提取第3个字符与后面的数字内容
          v=oldkok+t.toInt();                 //新角度=旧角度+N度
        } else {                              //X??? 绝对定位
          t=t.substring(1);                   //提取第2个字符与后面的数字内容
          v=t.toInt();                        //新角度=数字内容值
        }
       Servo180(servopin,v);                  //给舵机发送转到新角度命令
    }
}
