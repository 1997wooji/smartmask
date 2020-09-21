#define RED_LED A1
#define GREEN_LED 12
#define BLUE_LED 11
void setup()
{
 pinMode(RED_LED, OUTPUT);
 pinMode(GREEN_LED, OUTPUT);
 pinMode(BLUE_LED, OUTPUT);
}
void loop()
{
 digitalWrite(RED_LED, HIGH);     digitalWrite(GREEN_LED, LOW);   digitalWrite(BLUE_LED, LOW); // R=ON, G=OFF, B=OFF –> 빨강(Red)
 delay(1000);
 digitalWrite(RED_LED, LOW);     digitalWrite(GREEN_LED, HIGH);   digitalWrite(BLUE_LED, LOW); // R=OFF, G=ON, B=OFF –> 녹색(Green)
 delay(1000);
 digitalWrite(RED_LED, LOW);     digitalWrite(GREEN_LED, LOW);   digitalWrite(BLUE_LED, HIGH); // R=OFF, G=OFF, B=ON –> 파랑(Blue)
 delay(1000);
 digitalWrite(RED_LED, HIGH);     digitalWrite(GREEN_LED, HIGH);   digitalWrite(BLUE_LED, LOW); // R=ON, G=ON, B=OFF –> 노랑(Yellow)
 delay(1000);
digitalWrite(RED_LED, LOW);     digitalWrite(GREEN_LED, HIGH);   digitalWrite(BLUE_LED, HIGH); // R=OFF, G=ON, B=ON –> 청록(Cyan)
 delay(1000);
digitalWrite(RED_LED, HIGH);     digitalWrite(GREEN_LED, LOW);   digitalWrite(BLUE_LED, HIGH); // R=ON, G=OFF, B=ON –> 다홍(Magenta)
 delay(1000);
digitalWrite(RED_LED, HIGH);   digitalWrite(GREEN_LED, HIGH);    digitalWrite(BLUE_LED, HIGH); // R=ON, G=ON, B=ON –> 흰색(White)
 delay(5000);
}
