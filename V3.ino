#define BLINKER_WIFI
#define BLINKER_PRINT Serial
#define BLINKER_DUEROS_LIGHT
#include <Blinker.h>
#define LED_BUILTIN 2 //LED连接的引脚

 
int val; //用来存储湿度值
int ys;
int s ;
int zy;
int qh;
int counter = 0;
char auth[] = "b06eb982a879";
char ssid[] = "MERCURY_3736";
char pswd[] = "huyatao123";
bool oState = false;

// 新建组件对象
BlinkerButton Button1("btn-1");//补光镜开关
BlinkerButton Button2("btn-2");//向前
BlinkerButton Button3("btn-3");//向后
BlinkerButton Button4("btn-4");//向左
BlinkerButton Button5("btn-5");//向右
BlinkerSlider Slider1("ran-1");//左右调节滑块
BlinkerSlider Slider2("ran-2");//前后调节滑块

BlinkerNumber Number1("num-1");//光照
BlinkerNumber Number2("num-2");//雨水




void heartbeat() //心跳包使得我们每次打开APP都可以看到实时的最新湿度数据
{
    Number1.print(val);         //同步光照数据
    Number2.print(ys);         //同步雨水数据
}

void slider1_callback(int32_t value)
{
    
    zy = value;
    Serial.print(zy);
    
}
void slider2_callback(int32_t value)
{
    
    qh = value;
    Serial.print(qh);
    
}
// 按下按键即会执行该函数
void button1_callback(const String &state)
{
    BLINKER_LOG("get button state: ", state);
    if (state=="on") {
        digitalWrite(LED_BUILTIN, LOW);
         Serial.print("ledon");
         Button1.print("on");// 反馈开关状态
        
    } 
    else if(state=="off"){
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.print("ledoff");
        Button1.print("off"); // 反馈开关状态
    } 
}
void button2_callback(const String &state)
  {
    
      Serial.print("q");
      Button2.print("q");// 反馈开关状态
    
  }
void button3_callback(const String &state)
  {
      Serial.print("h");
      Button3.print("h");// 反馈开关状态
  }
void button4_callback(const String &state)
  {
      Serial.print("z");
      Button4.print("z");// 反馈开关状态
  }
void button5_callback(const String &state)
  {
      Serial.print("y");
      Button5.print("y");// 反馈开关状态
  }

void flip()
{
    

}

void duerPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        digitalWrite(LED_BUILTIN, LOW);

        BlinkerDuerOS.powerState("on");
        BlinkerDuerOS.print();

        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(LED_BUILTIN, HIGH);

        BlinkerDuerOS.powerState("off");
        BlinkerDuerOS.print();

        oState = false;
    }
}
void duerMode(const String & mode)
{
    BLINKER_LOG("need set mode: ", mode);

    if (mode == BLINKER_CMD_READING) {
        digitalWrite(LED_BUILTIN, LOW);// Your mode function
        Serial.print("q");
        delay(3000);
        digitalWrite(LED_BUILTIN,HIGH);
        
    }
    else if (mode == BLINKER_CMD_MOVIE) {
        digitalWrite(LED_BUILTIN, HIGH);// Your mode function
        Serial.print("h");
        delay(3000);
        digitalWrite(LED_BUILTIN,LOW);// Your mode function
    }
    else if (mode == BLINKER_CMD_SLEEP) {
        // Your mode function
    }
    else if (mode == BLINKER_CMD_HOLIDAY) {
        // Your mode function
    }
    else if (mode == BLINKER_CMD_MUSIC) {
        // Your mode function
    }
    else if (mode == BLINKER_CMD_COMMON) {
        // Your mode function
    }

    //wsMode = mode;

    BlinkerDuerOS.mode(mode);
    BlinkerDuerOS.print();
}




// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}

void setup()
{
    // 初始化串口
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
 
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    Button4.attach(button4_callback);
    Button5.attach(button5_callback);
    Slider1.attach(slider1_callback);
    Slider2.attach(slider2_callback);
    Blinker.attachHeartbeat(heartbeat);
    BlinkerDuerOS.attachPowerState(duerPowerState);
    BlinkerDuerOS.attachMode(duerMode);


}
 
void loop()
{
    Blinker.run();
    if (Serial.available() > 0)//串口接收到数据
  {
    s = Serial.read();//获取串口接收到的数据
    if (s =='s')
    {ys = 1;
    BLINKER_LOG(ys);
    }
    if (s == 'f'){
    ys = 0;
    BLINKER_LOG(ys);
    }
    else{
    val = char(s);
     BLINKER_LOG(val);
     }
    }
   
  }             
   
