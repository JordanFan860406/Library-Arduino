void setup()
{
  Serial.begin(9600); //指定串口通讯比特率为9600
  pinMode(13, OUTPUT);
}
void loop()
{
  int v = analogRead(A0);  //从A0口读取电压，模拟端口电压测量范围为0-5V，返回的值为0-1024
  float volt = v * (5.0 / 1024); //将返回值换算成电压
  if(volt > 1.4){
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
  Serial.print(volt);  //串口输出电压值
  Serial.println(" V");  //输出单位，并且换行
  delay(1000);  //输出后等待1s，降低刷新速度
}
