#include <Plate.h>
#include <Servo.h>
#include <PS2X_lib.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

PS2X ps2x;
uint8_t max_bright = 50;

#define port_clock 48     //p4
#define port_command 46   //p6
#define port_attention 47 //p5
#define port_data 45      //p7

#define YP A14  // must be an analog pin, use "An" notation!
#define XM A13  // must be an analog pin, use "An" notation!
#define YM 23   // can be a digital pin
#define XP 22   // can be a digital pin

int TS_MINX =110;
int TS_MINY =110;
int TS_MAXX =953;
int TS_MAXY =920;

#define TS_MINX_ADDR 200
#define TS_MINY_ADDR 201
#define TS_MAXX_ADDR 202
#define TS_MAXY_ADDR 203

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A14
#define LCD_CD A13
#define LCD_WR A12
#define LCD_RD A11
#define LCD_RESET A15

// Assign human-readable names to some common delay(50)16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define HUI     0xadda

#define MINPRESSURE 5  
#define MAXPRESSURE 1000 
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 40
#define PENRADIUS 3
int oldflag, currentflag;
char digital_pin[8]={6,7,8,49,48,47,46,45}; 	
char analog_pin[8]={0,1,2,3,4,5,6,7}; 		
void green();
void red();
void pink();
void blue();
void up();
void down();
void left();
void right();
void r1();
void r2();
void r3();
void l1();
void l2();
void l3();
void msleep(unsigned int time)
{
	delay(time);
}

int analog(int s) 
{
	int a;
	a=analogRead(analog_pin[s]);
	return a;
}

bool digital(int s)
{
	bool d;
	d=digitalRead(digital_pin[s]);
	return d;
}
bool button(int s)
{
	bool d;
	d=digitalRead(s+29);
	return d;
}
double seconds()
{
	return (double)(millis()/1000);
}

void set_servo_position(char pin, int val) 
{ 
   if(pin==0)
   {
     myservo1.write(val);
   }
   else if(pin==1)
   {
    myservo2.write(val);
   }
   else if(pin==2)
   {
    myservo3.write(val);
   }
   else if(pin==3)
   {
    myservo4.write(val);
   }   
}

void motor(char pin ,int Speed)
{
	if(Speed>100)
		Speed=100;
	else if(Speed<-100)
	Speed=-100;
	Speed=map(Speed,-100,100,-255,255);
	if(pin==0)
	{
		if(Speed<=0)
		{
			analogWrite(9,-Speed);
			digitalWrite(34,0);
		}
		else
		{
			analogWrite(9,Speed);
			digitalWrite(34,1);
        }
	}
	else if(pin==1)
	{
		if(Speed<=0)
		{
			analogWrite(10,-Speed);
			digitalWrite(35,0);
		}
		else
		{
			analogWrite(10,Speed);
			digitalWrite(35,1);
        
		}
	}
	else if(pin==2)
	{
		if(Speed<=0)
		{
			analogWrite(11,-Speed);
			digitalWrite(36,0);
		}
		else
		{
			analogWrite(11,Speed);
			digitalWrite(36,1);
		}
	}
	else if(pin==3)
	{
		if(Speed<=0)
		{
			analogWrite(12,-Speed);
			digitalWrite(37,0);
		}
		else
		{
			analogWrite(12,Speed);
			digitalWrite(37,1);
        
		}
	}
}

void move(int s1,int s2,int t)
{
	motor(1,s1);
	motor(2,s2);
	msleep(t);
	motor(1,0);
	motor(2,0); 
}

void print_int(int y,int tp_value)  
{
	if(y==1)
	{
		tft.printNUM(214, 60,tp_value, YELLOW,  BLACK,8); 
	}
	if(y==2)
	{
		tft.printNUM(214, 90,tp_value, YELLOW,  BLACK,8); 
	}
	if(y==3)
	{
		tft.printNUM(214, 120,tp_value, YELLOW,  BLACK,8); 
	}
	if(y==4)
	{
		tft.printNUM(214, 150,tp_value, YELLOW,  BLACK,8); 
	 }
	 if(y==5)
	 {
		tft.printNUM(214, 180,tp_value, YELLOW,  BLACK,8); 
	 }
	 if(y==6)
	 {
		tft.printNUM(214, 210,tp_value, YELLOW,  BLACK,8); 
	 }
}

void print_string(int y,String tp_name) 
{
	if(y==1)
	{
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.setCursor(102, 58);
	tft.println(tp_name);  
	}
	if(y==2)
	{
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.setCursor(102, 88);
	tft.println(tp_name);  
	}	 
	if(y==3)
	{
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.setCursor(102, 118);
	tft.println(tp_name);  
	}
	if(y==4)
	{
	tft.setTextColor(WHITE);//
	tft.setTextSize(2);
	tft.setCursor(102,148);
	tft.println(tp_name);  
	}	 
	if(y==5)
	{
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.setCursor(102,178);
	tft.println(tp_name);  
	}
	 if(y==6)
	{
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.setCursor(102,208);
	tft.println(tp_name);  
	}
}

void Screen_Calibration()
{
	int t_x,t_y;
	unsigned int a_flag=0;
	
	int x_flag=0;
	//tft.reset();
	Serial.begin(9600);
	uint16_t identifier = tft.readID();
	if(identifier==0x0101)
		identifier=0x9341;
	if(identifier == 0x9341) 
	{
		Serial.println(F("Found ILI9341 LCD driver"));
	} 
	else 
	{
		Serial.print(F("Unknown LCD driver chip: "));
		Serial.println(identifier, HEX);
		return;
	}
	
	
	tft.begin(identifier);
	tft.fillScreen(BLACK); 
	tft.setRotation(3); 
	
	tft.fillRect(5, 5, 310, 10, HUI);
	tft.fillRect(5, 5, 10, 230, HUI);
	tft.fillRect(5, 225, 305, 10, HUI);
	tft.fillRect(305, 5, 10, 230, HUI);
	
	tft.LCD_sleep(1);
	currentflag = 1;
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(60, 20);
    tft.println("Screen Correction");
	tft.setTextColor(YELLOW);
	tft.setCursor(23, 75);
	tft.println("Please Click + In Order");
	tft.setTextColor(WHITE);
	tft.setCursor(52, 55);
    tft.fillRect(50, 55, 14, 14, HUI);
    tft.println("+");
	TSPoint p;
	pinMode(52, OUTPUT);
	int touch[8][2];  
	int touch_num=0; 
	TS_MINX=EEPROM.read(TS_MINX_ADDR)*4; 
	TS_MINY=EEPROM.read(TS_MINY_ADDR)*4;
	TS_MAXX=EEPROM.read(TS_MAXX_ADDR)*4;
	TS_MAXY=EEPROM.read(TS_MAXY_ADDR)*4;
	Serial.print("x=");
	Serial.println(t_x);
	Serial.print("y=");
	Serial.println(t_y);
           
		while(touch_num<8)
		{
		
			digitalWrite(52, HIGH);
            p = ts.getPoint();
            digitalWrite(52, LOW);
            pinMode(XM, OUTPUT);
            pinMode(YP, OUTPUT);
			
           // Serial.println(p.z);
			if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
			{
				t_y = map(p.x, TS_MINY, TS_MAXY, 0,tft.height());
				t_x = map(p.y, TS_MINX, TS_MAXX,0,tft.width());
				Serial.print("x=");
				Serial.println(t_x);
				Serial.print("y=");
				Serial.println(t_y);
				if (touch_num%4==0)
				{
					tft.fillRect(50, 55, 14, 14, BLACK);
					tft.setTextSize(2);
					tft.setCursor(257, 55);//����
					tft.fillRect(255, 55, 14, 14, HUI);
					tft.println("+");
					touch[touch_num][0]=p.y;
					touch[touch_num][1]=p.x;
				} 
				else if (touch_num%4==1) 
				{
					tft.fillRect(255, 55, 14, 14, BLACK);
					tft.setTextSize(2);
					tft.setCursor(52, 190);
					tft.fillRect(50, 190, 14, 14, HUI);
					tft.println("+");
					touch[touch_num][0]=p.y;
					touch[touch_num][1]=p.x;
				}
				else if (touch_num%4==2) 
				{
					tft.fillRect(50, 190, 14, 14, BLACK);	
					tft.setTextSize(2);
					tft.setCursor(257, 190);
					tft.fillRect(255, 190, 14, 14, HUI);
					tft.println("+");	
					touch[touch_num][0]=p.y;
					touch[touch_num][1]=p.x;
				}
				else if (touch_num%4==3) 
				{
					tft.fillRect(255, 190, 14, 14, BLACK);	
					tft.setTextSize(2);
					tft.setCursor(52, 55);
    				tft.fillRect(50, 55, 14, 14, HUI);
					tft.println("+");
					touch[touch_num][0]=p.y;
					touch[touch_num][1]=p.x;			
				}
				touch_num+=1;
				delay(200);
				
			
			}
		
		}
		
		for (int j=0;j<4;j++) //�������ΰ�ѹ��ƽ��ֵ 
		{
			touch[j][0]=(touch[j][0]+touch[j+4][0])/2;
			touch[j][1]=(touch[j][1]+touch[j+4][1])/2;
		}
		float x_min,y_min,x_max,y_max;
		x_min=(touch[0][0]+touch[2][0])/2;
		Serial.print("touch[0][0]=");
		Serial.println(touch[0][0]);
		Serial.print("touch[2][0]=");
		Serial.println(touch[2][0]);
		y_min=(touch[0][1]+touch[1][1])/2;
		x_max=(touch[1][0]+touch[3][0])/2;
		y_max=(touch[2][1]+touch[3][1])/2;
		Serial.print("x_min=");
		Serial.println(x_min);
		Serial.print("x_max=");
		Serial.println(x_max);

		float k_x=(262-57)/(x_max-x_min); 
		float k_y=(197-62)/(y_max-y_min);
		Serial.print("k_x=");
		Serial.println(k_x);
		TS_MINX=x_min-57/k_x; 
		TS_MINY=y_min-52/k_y;
		TS_MAXX=x_max+57/k_x;
		TS_MAXY=y_max+33/k_y;
		Serial.print("TS_MINX=");
		Serial.println(TS_MINX);
		Serial.print("TS_MAXX=");
		Serial.println(TS_MAXX);
		
		
		EEPROM.write(TS_MINX_ADDR,TS_MINX/4); 
		delay(100);
		EEPROM.write(TS_MINY_ADDR,TS_MINY/4);
		delay(100);
		EEPROM.write(TS_MAXX_ADDR,TS_MAXX/4);
		delay(100);
		EEPROM.write(TS_MAXY_ADDR,TS_MAXY/4);
		delay(100);
		
		
		
	}


void ROM_Setup()
{
	for(int i=99;i<104;i++)
	{
		EEPROM.write(i,15);
	}
	for(int i=104;i<109;i++)
	{
		EEPROM.write(i,50);
	}
	for(int i=109;i<114;i++)
	{
		EEPROM.write(i,90);
	}
	for(int i=114;i<119;i++)
	{
		EEPROM.write(i,15);
	}
	for(int i=119;i<124;i++)
	{
		EEPROM.write(i,50);
	}
	for(int i=124;i<129;i++)
	{
		EEPROM.write(i,90);
	}
}


void Main_Interface()
{
	int t_x,t_y;
	char sd[4]={0,0,0,0};
	int servo_angle[4];
	unsigned int a_flag=0;
	int x_flag=0;
 
	pinMode(34,OUTPUT); 
	pinMode(35,OUTPUT);
	pinMode(36,OUTPUT);
	pinMode(37,OUTPUT);
  
	tft.reset();
	Serial.begin(9600);
	pinMode(45,INPUT);
	pinMode(46,INPUT);
	pinMode(47,INPUT);
	pinMode(48,INPUT);
	pinMode(6,INPUT);
	pinMode(7,INPUT);
	pinMode(8,INPUT);
	pinMode(49,INPUT);
  

	for(int i=50;i<54;i++)
	{
		servo_angle[i-50]= EEPROM.read(i); 
		delay(50);
		set_servo_position(i-50, servo_angle[i-50]); 
	}
	  
	TS_MAXX=EEPROM.read(TS_MINX_ADDR)*4; 
	TS_MINY=EEPROM.read(TS_MINY_ADDR)*4;
	TS_MINX=EEPROM.read(TS_MAXX_ADDR)*4;
	TS_MAXY=EEPROM.read(TS_MAXY_ADDR)*4;

	myservo1.attach(2);
	myservo2.attach(3);
	myservo3.attach(4);
	myservo4.attach(5);
	
	uint16_t identifier;
	for(int iii=0;iii<10;iii++)
	{
	identifier = tft.readID();
	}
	if(identifier==0x0101)
		identifier=0x9341;
	if(identifier == 0x9341) 
	{
		Serial.println(F("Found ILI9341 LCD driver"));
	} 
	else 
	{
		Serial.print(F("Unknown LCD driver chip: "));
		Serial.println(identifier, HEX);
		return;
	}
	

	tft.begin(identifier);
	tft.fillScreen(BLACK); 
	tft.setRotation(3); 
	tft.fillRect(5, 11, 85, 40, HUI); 
	tft.drawRect(5, 11, 85, 40, WHITE); 
	tft.fillRect(95, 5, 220, 20, HUI);
	tft.fillRect(5, 56, 85, 40, HUI);
	tft.fillRect(5, 101, 85, 40, HUI);
	tft.fillRect(5, 146, 85, 40, HUI);
	tft.fillRect(5, 191, 85, 40, HUI);
	tft.drawRect(95, 26, 220, 210, WHITE);
	//tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
	tft.LCD_sleep(1);
	currentflag = 1;
	tft.setTextColor(WHITE);
	tft.setTextSize(2);
	tft.setCursor(8, 23);
	tft.println("Analog");
	tft.setCursor(8, 68);
	tft.println("Digital");
	tft.setCursor(8,113);
	tft.println("Motor");
	tft.setCursor(8, 158);
	tft.println("Servo");
	tft.setCursor(8, 203);
	tft.println("Run");


	pinMode(52, OUTPUT);
	TSPoint p;
	int testTime=0;
	double notSleep=millis();
	while(1)
	{
		if(millis()-notSleep>10000)
		{
			testTime++;
			Serial.println(testTime);
			ps2x.read_gamepad(false, 0xff); 
			delay(1000);
			ps2x.read_gamepad(false, 0x00); 
			notSleep=millis();
		}

		for(int i=0;i<10;i++)
		{
			digitalWrite(52, HIGH);
			p = ts.getPoint();
			digitalWrite(52, LOW);
			pinMode(XM, OUTPUT);
			pinMode(YP, OUTPUT);
			if(button(1))
			{
				currentflag = 7;
				x_flag=0;
				tft.drawRect(5, 191, 85, 40, WHITE);
				tft.fillRect(97, 30, 215, 200 , BLACK);
				tft.setTextColor(WHITE);
				tft.setTextSize(2);
				tft.fillRect(5, 191, 85, 40, HUI);
				tft.setCursor(8, 203);
				tft.println("Run");
			}
			if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
			{
				t_y = map(p.x, TS_MAXX, TS_MINX, 0,tft.height());
				t_x = map(p.y, TS_MINY, TS_MAXY,0,tft.width());
				Serial.print("x=");
				Serial.println(t_x);
				Serial.print("y=");
				Serial.println(t_y);
				if (t_x<80) 
				{
					oldflag = currentflag;
					x_flag=0;
					if ( t_y > 10 &&t_y < 52) 
					{ 
						currentflag = 1; 
						tft.drawRect(5, 11, 85, 40, WHITE);
					} 
					else if (t_y > 55 && t_y < 97) 
					{
						currentflag = 2;
						tft.drawRect(5, 56, 85, 40, WHITE);
					}
					else if ( t_y > 100 && t_y < 142) 
					{
						currentflag = 3;
						tft.drawRect(5, 101, 85, 40, WHITE);
					} 
					else if ( t_y > 145 && t_y < 187) 
					{
						currentflag = 4;
						tft.drawRect(5, 146, 85, 40, WHITE);
					} 

					else if ( t_y > 190 && t_y<231 ) 
					{
						currentflag = 7;
						tft.drawRect(5, 191, 85, 40, WHITE);
					}
		
					if (oldflag != currentflag) 
					{
						tft.fillRect(97, 30, 215, 200 , BLACK);
						tft.setTextColor(WHITE);
						tft.setTextSize(2);
						if (oldflag == 1)
						{
							
							tft.fillRect(5, 11, 85, 40, HUI);
							tft.setCursor(8, 23);
							tft.println("Analog");
						}
						else  if (oldflag == 2)
						{
							
							tft.fillRect(5, 56, 85, 40, HUI);
							tft.setCursor(8, 68);
							tft.println("Digital");
						}
						else if (oldflag == 3)
						{
							
							tft.fillRect(5, 101, 85, 40, HUI);
							tft.setCursor(8,113);
							tft.println("Motor");
						}
						else if (oldflag == 4)
						{
							
							tft.fillRect(5, 146, 85, 40, HUI);
							tft.setCursor(8, 158);
							tft.println("Servo");
						
						}
						else if (oldflag == 7) 
						{
							
							tft.fillRect(5, 191, 85, 40, HUI);
							tft.setCursor(8, 203);
							tft.println("Run");
						}
					}
				}
				break;
			}
		}

		switch(currentflag)
        {
			case 1: 
			{  
				if(x_flag==0) 
                {
					tft.setTextColor(YELLOW);
                    tft.setTextSize(2);
                    tft.setCursor(115, 40);
                    tft.print("A0=");
                    tft.setCursor(115, 70);
                    tft.print("A1=");
                    tft.setCursor(115, 100);
                    tft.print("A2=");
                    tft.setCursor(115, 130);
                    tft.print("A3=");
                    tft.setCursor(215, 40);
                    tft.print("A4=");
                    tft.setCursor(215, 70);
                    tft.print("A5=");      
                    tft.setCursor(215, 100);
                    tft.print("A6=");
                    tft.setCursor(215, 130);
                    tft.print("A7=");
                }
                a_flag++;
                if(a_flag>=8) a_flag=0;
                tft.printNUM(152+(a_flag/4)*100, 40+(a_flag%4)*30, analogRead(analog_pin[a_flag]), YELLOW,  BLACK, 4); 
                x_flag=1;
				break;
            }   
			case 2: 
			{
				tft.setTextColor(YELLOW);
				tft.setTextSize(2);
                if(x_flag==0)
                {
					tft.setCursor(115, 40);
					tft.print("D0=");
					tft.setCursor(115, 70);
					tft.print("D1=");
					tft.setCursor(115, 100);
					tft.print("D2=");
					tft.setCursor(115, 130);
					tft.print("D3=");
					tft.setCursor(215, 40);
					tft.print("D4=");
					tft.setCursor(215, 70);
					tft.print("D5=");
					tft.setCursor(215, 100);
					tft.print("D6=");
					tft.setCursor(215, 130);
					tft.print("D7=");
				}
				a_flag++;
				if(a_flag>=8) a_flag=0;
				tft.printNUM(152+(a_flag/4)*100, 40+(a_flag%4)*30, digitalRead(digital_pin[a_flag]), YELLOW,  BLACK, 1);
                x_flag=1;
                break;
            }   
			case 3:  
			{
                if(x_flag==0)
                {
					tft.setTextColor(WHITE);
					tft.setTextSize(2);
					tft.setCursor(122, 35);
					tft.println(" Motor0");
					tft.setCursor(122, 55);
					tft.fillRect(120, 55, 14, 14, HUI);
					tft.fillRect(204, 55, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 50, 55, 25, HUI);
					tft.setCursor(255, 55);
					tft.print("Stop");
					
					tft.setCursor(122, 85);
					tft.println(" Motor1");
					tft.setCursor(122, 105);
					tft.fillRect(120, 105, 14, 14, HUI);
					tft.fillRect(204, 105, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 100, 55, 25, HUI);
					tft.setCursor(255, 105);
					tft.print("Stop");
					
					tft.setCursor(122, 135);
					tft.println(" Motor2");
					tft.setCursor(122, 155);
					tft.fillRect(120, 155, 14, 14, HUI);
					tft.fillRect(204, 155, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 150, 55, 25, HUI);
					tft.setCursor(255, 155);
					tft.print("Stop");
					
					tft.setCursor(122, 185);
					tft.println(" Motor3");
					tft.setCursor(122, 205);
					tft.fillRect(120, 205, 14, 14, HUI);
					tft.fillRect(204, 205, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 200, 55, 25, HUI);
					tft.setCursor(255, 205);
					tft.print("Stop");
					
					tft.printNUM(147, 55,sd[0], YELLOW,  BLACK,3);
					tft.printNUM(147, 105,sd[1], YELLOW,  BLACK,3);
					tft.printNUM(147, 155,sd[2], YELLOW,  BLACK,3);
					tft.printNUM(147, 205,sd[3], YELLOW,  BLACK,3);
					}
				if (p.z > MINPRESSURE && p.z < MAXPRESSURE) //��������������
				{
					if ( t_y >40&&t_y<70) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							sd[0]--;
						}
						else if(t_x>180&&t_x<240)
						{
							sd[0]++;
						}
						else if(t_x>260&&t_x<302) 
						{
							sd[0]=0; 
							tft.fillRect(134, 55, 14, 14, BLACK);
						}
						if(sd[0]>=100) 
						{  
							sd[0]=100;
						}
						else if(sd[0]<=-100) 
						{
							sd[0]=-100;
						}
						tft.printNUM(147, 55,sd[0], YELLOW,  BLACK,3);
						motor(0 ,sd[0]) ;
					}
					else  if ( t_y >90&&t_y<120) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							sd[1]--;
						}
						else if(t_x>180&&t_x<240) 
						{
							sd[1]++;
						}
						else if(t_x>260&&t_x<302) 
						{
							sd[1]=0; 
							tft.fillRect(134, 105, 14, 14, BLACK);
						}
						if(sd[1]>100) 
						{
							sd[1]=100;
						}
						else if(sd[1]<-100) 
						{
							sd[1]=-100;
						}
						tft.printNUM(147, 105,sd[1], YELLOW,  BLACK,3);
						motor(1 ,sd[1]) ;
                    }
					else  if ( t_y >140&&t_y<170) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							sd[2]--;
						}
						else if(t_x>180&&t_x<240) 
						{
							sd[2]++;
						}
						else if(t_x>260&&t_x<302)
						{
							sd[2]=0; 
							tft.fillRect(134, 155, 14, 14, BLACK);
						}
						if(sd[2]>100) 
						{
							sd[2]=100;
						}
						else if(sd[2]<-100){
							sd[2]=-100;
						}
						tft.printNUM(147, 155,sd[2], YELLOW,  BLACK,3);
						motor(2 ,sd[2]) ;
                    }
					else  if ( t_y >190&&t_y<230) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							sd[3]--;
						}
						else if(t_x>180&&t_x<240) 
						{
							sd[3]++;
						}
						else if(t_x>260&&t_x<302) 
						{
							sd[3]=0; 
							tft.fillRect(134, 205, 14, 14, BLACK);
						}
						if(sd[3]>100) 
						{
							sd[3]=100;
						}
						else if(sd[3]<-100) 
						{
							sd[3]=-100;
						}
						tft.printNUM(147, 205,sd[3], YELLOW,  BLACK,3);
						motor(3 ,sd[3]) ;
					}
				}
				x_flag=1;
				break;
			}
			case 4: //�����������
			{    
				if(x_flag==0)
				{
					tft.setTextColor(WHITE);
					tft.setTextSize(2);
					tft.setCursor(122, 35);
					tft.println(" Servo0");
					tft.setCursor(122, 55);
					tft.fillRect(120, 55, 14, 14, HUI);
					tft.fillRect(204, 55, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 50, 55, 25, HUI);
					tft.setCursor(255, 55);
					tft.print(" GO");
					tft.setCursor(122, 85);
					tft.println(" Servo1");
					tft.setCursor(122, 105);
					tft.fillRect(120, 105, 14, 14, HUI);
					tft.fillRect(204, 105, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 100, 55, 25, HUI);
					tft.setCursor(255, 105);
					tft.print(" GO");
					tft.setCursor(122, 135);
					tft.println(" Servo2");
					tft.setCursor(122, 155);
					tft.fillRect(120, 155, 14, 14, HUI);
					tft.fillRect(204, 155, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 150, 55, 25, HUI);
					tft.setCursor(255, 155);
					tft.print(" GO");
					tft.setCursor(122, 185);
					tft.println(" Servo3");
					tft.setCursor(122, 205);
					tft.fillRect(120, 205, 14, 14, HUI);
					tft.fillRect(204, 205, 14, 14, HUI);
					tft.print("-      +");
					tft.fillRect(250, 200, 55, 25, HUI);
					tft.setCursor(255, 205);
					tft.print(" GO");
					tft.printNUM(147, 55,servo_angle[0], YELLOW,  BLACK,3);
					tft.printNUM(147, 105,servo_angle[1], YELLOW,  BLACK,3);
					tft.printNUM(147, 155,servo_angle[2], YELLOW,  BLACK,3);
					tft.printNUM(147, 205,servo_angle[3], YELLOW,  BLACK,3);
				}
				if (p.z > MINPRESSURE && p.z < MAXPRESSURE)  //��������������
				
				{
					if ( t_y >30&&t_y<75) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							servo_angle[0]--;
						}
						else if(t_x>180&&t_x<240) 
						{
							servo_angle[0]++;
						}
						else if(t_x>260&&t_x<302) 
						{ 
							set_servo_position(0, servo_angle[0]);
							EEPROM.write(50,  servo_angle[0]); 
						}
						if(servo_angle[0]>=180) 
						{
							servo_angle[0]=180;
						}
						else if(servo_angle[0]<0)
						{
							servo_angle[0]=0;
						}
						tft.printNUM(147, 55,servo_angle[0], YELLOW,  BLACK,3);
					}
					else  if ( t_y >80&&t_y<130) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							servo_angle[1]--;
						}
						else if(t_x>180&&t_x<240) 
						{
							servo_angle[1]++;
						}
						else if(t_x>260&&t_x<302) 
						{
							set_servo_position(1, servo_angle[1]);
							EEPROM.write(51,  servo_angle[1]);
						}
						if(servo_angle[1]>=180) 
						{
							servo_angle[1]=180;
						}	
						else if(servo_angle[1]<0) 
						{
							servo_angle[1]=0;
						}
						tft.printNUM(147, 105,servo_angle[1], YELLOW,  BLACK,3);
                            
					}
					else  if ( t_y >140&&t_y<180) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							servo_angle[2]--;
						}
                        else if(t_x>180&&t_x<240)
						{
							servo_angle[2]++;
						}
                        else if(t_x>260&&t_x<302) 
						{
							set_servo_position(2, servo_angle[2]);
							EEPROM.write(52,  servo_angle[2]);
						}
                        if(servo_angle[2]>=180) 
						{
							servo_angle[2]=180;
						}
                        else if(servo_angle[2]<0) 
						{
							servo_angle[2]=0;
						}
                        tft.printNUM(147, 155,servo_angle[2], YELLOW,  BLACK,3);

					}
					else  if ( t_y >190&&t_y<230) 
					{ 
						if (t_x>100&&t_x<150) 
						{
							servo_angle[3]--;
						}
						else if(t_x>180&&t_x<240) 
						{
							servo_angle[3]++;
						}
						else if(t_x>260&&t_x<302) 
						{
							set_servo_position(3, servo_angle[3]);
							EEPROM.write(53, servo_angle[3]);
						}
						if(servo_angle[3]>=180) 
						{
							servo_angle[3]=180;
						}
						else if(servo_angle[3]<0) 
						{
							servo_angle[3]=0;
						}
						tft.printNUM(147, 205,servo_angle[3], YELLOW,  BLACK,3);
                          
					}
				}
				x_flag=1;
				break;
			}
			case 7: 
			{  
				if(x_flag==0)
				{
					tft.setTextColor(WHITE);
					tft.setTextSize(2);
					tft.setCursor(117, 32);
					tft.println("Program Running");
				}
				x_flag=1;
				break;
			}
        }
		if(currentflag==7) 
		{
			motor(0,0);
			motor(1,0);
			motor(2,0);
			motor(3,0);
			break;
		}
	}
} 
void Plate_Setup() 
{
  Serial.begin(9600);
  delay(50);
  if(button(3)&&button(4))	Screen_Calibration();
  Main_Interface();
  ps2x.config_gamepad(port_clock,port_command,port_attention,port_data, true, true);
  ps2x.enableRumble();
}
void clear_gamepad()
{
  int button_green,button_red,button_blue,button_pink;
  int button_r1,button_r2,button_l1,button_l2;
  int button_pad_up,button_pad_down,button_pad_left,button_pad_right;
  for(int i=0;i<20;i++)
  {
    ps2x.read_gamepad();
	delay(10);
    button_green=ps2x.Analog(PSAB_GREEN);
    button_red=ps2x.Analog(PSAB_RED);
    button_blue=ps2x.Analog(PSAB_BLUE);
    button_pink=ps2x.Analog(PSAB_PINK);
	button_l1=ps2x.Button(PSAB_L1);
    button_l2=ps2x.Button(PSAB_L2);
    button_r1=ps2x.Button(PSAB_R1);
    button_r2=ps2x.Button(PSAB_R2);
    button_pad_up=ps2x.Button(PSB_PAD_UP);
    button_pad_down=ps2x.Button(PSB_PAD_DOWN);
    button_pad_left=ps2x.Button(PSB_PAD_LEFT);
    button_pad_right=ps2x.Button(PSB_PAD_RIGHT);
	}	
}

void end()
{
  while(1)
  {delay(1000);}
}
void run_gamepad(int speed,int pts)
{
  int bar_lx, bar_ly, bar_rx, bar_ry;
  unsigned long lastGreenPress = 0;
  unsigned long lastRedPress = 0;
  unsigned long lastBluePress = 0;
  unsigned long lastPinkPress = 0;
  unsigned long lastR1Press = 0;
  unsigned long lastR2Press = 0;
  unsigned long lastL1Press = 0;
  unsigned long lastL2Press = 0;
  unsigned long lastPadUpPress = 0;
  unsigned long lastPadDownPress = 0;
  unsigned long lastPadLeftPress = 0;
  unsigned long lastPadRightPress = 0;
  
  bool greenWasPressed = false;
  bool redWasPressed = false;
  bool blueWasPressed = false;
  bool pinkWasPressed = false;
  bool r1WasPressed = false;
  bool r2WasPressed = false;
  bool l1WasPressed = false;
  bool l2WasPressed = false;
  bool padUpWasPressed = false;
  bool padDownWasPressed = false;
  bool padLeftWasPressed = false;
  bool padRightWasPressed = false;
  
  unsigned long debounceDelay = 2000;  // 200 milliseconds
  msleep(500);
  
  while (1)
  {
    delay(50);
    ps2x.read_gamepad();
    bar_lx = ps2x.Analog(PSS_LX);
    bar_ly = ps2x.Analog(PSS_LY);
    bar_rx = ps2x.Analog(PSS_RX);
    bar_ry = ps2x.Analog(PSS_RY);

    unsigned long currentTime = millis();
	
    //Green button
    if (ps2x.Button(PSB_GREEN)) 
    {
      if (!greenWasPressed && currentTime - lastGreenPress > debounceDelay) 
      {
        green();
        lastGreenPress = currentTime;
		clear_gamepad();
      }
      greenWasPressed = true;
    }
    else 
    {
      greenWasPressed = false;
    }
  
    // Red button
    if (ps2x.Button(PSB_RED)) 
    {
      if (!redWasPressed && currentTime - lastRedPress > debounceDelay) 
      {
        red();
        lastBluePress = currentTime;
		clear_gamepad();
	  }
	  redWasPressed = true;
    } 
    else 
    {
      redWasPressed = false;
    }

    // Blue button
    if (ps2x.Button(PSB_BLUE)) 
    {
      if (!blueWasPressed && currentTime - lastBluePress > debounceDelay) 
      {
        blue();
        lastBluePress = currentTime;
		clear_gamepad();
      }
      blueWasPressed = true;
    } 
    else 
    {
      blueWasPressed = false;
    }

    // Pink button
    if (ps2x.Button(PSB_PINK)) 
    {
      if (!pinkWasPressed && currentTime - lastPinkPress > debounceDelay) 
      {
        pink();
        lastPinkPress = currentTime;
		clear_gamepad();
      }
      pinkWasPressed = true;
    } 
    else 
    {
      pinkWasPressed = false;
    }

    // R1 button
    if (ps2x.Button(PSB_R1)) 
    {
      if (!r1WasPressed && currentTime - lastR1Press > debounceDelay) 
      {
        r1();
        lastR1Press = currentTime;
		clear_gamepad();
      }
      r1WasPressed = true;
    } 
    else 
    {
      r1WasPressed = false;
    }

    // R2 button
    if (ps2x.Button(PSB_R2)) 
    {
      if (!r2WasPressed && currentTime - lastR2Press > debounceDelay) 
      {
        r2();
        lastR2Press = currentTime;
		clear_gamepad();
      }
      r2WasPressed = true;
    } 
    else 
    {
      r2WasPressed = false;
    }

    // L1 button
    if (ps2x.Button(PSB_L1)) 
    {
      if (!l1WasPressed && currentTime - lastL1Press > debounceDelay) 
      {
        l1();
        lastL1Press = currentTime;
		clear_gamepad();
      }
      l1WasPressed = true;
    } 
    else 
    {
      l1WasPressed = false;
    }

    // L2 button
    if (ps2x.Button(PSB_L2)) 
    {
      if (!l2WasPressed && currentTime - lastL2Press > debounceDelay) 
      {
        l2();
        lastL2Press = currentTime;
		clear_gamepad();
      }
      l2WasPressed = true;
    } 
    else 
    {
      l2WasPressed = false;
    }

    // Pad Up
    if (ps2x.Button(PSB_PAD_UP)) 
    {
      if (!padUpWasPressed && currentTime - lastPadUpPress > debounceDelay) 
      {
        up();
        lastPadUpPress = currentTime;
		clear_gamepad();
      }
      padUpWasPressed = true;
    } 
    else 
    {
      padUpWasPressed = false;
    }

    // Pad Down
    if (ps2x.Button(PSB_PAD_DOWN)) 
    {
      if (!padDownWasPressed && currentTime - lastPadDownPress > debounceDelay) 
      {
        down();
        lastPadDownPress = currentTime;
		clear_gamepad();
      }
      padDownWasPressed = true;
    } 
    else 
    {
      padDownWasPressed = false;
    }

    // Pad Left
    if (ps2x.Button(PSB_PAD_LEFT)) 
    {
      if (!padLeftWasPressed && currentTime - lastPadLeftPress > debounceDelay) 
      {
        left();
        lastPadLeftPress = currentTime;
		clear_gamepad();
      }
      padLeftWasPressed = true;
    } 
    else 
    {
      padLeftWasPressed = false;
    }

    // Pad Right
    if (ps2x.Button(PSB_PAD_RIGHT)) 
    {
      if (!padRightWasPressed && currentTime - lastPadRightPress > debounceDelay) 
      {
        right();
        lastPadRightPress = currentTime;
		clear_gamepad();
      }
      padRightWasPressed = true;
    } 
    else 
    {
      padRightWasPressed = false;
    }

    bar_ly = (bar_ly - 128);  
    bar_ly = -map(bar_ly, 0, 128, 0, 70);
    bar_rx = (bar_rx - 128);  
    bar_rx = map(bar_rx, 0, 128, 0, pts);
	float speed_l=0;
	float speed_r=0;
	if(speed>0)
	{
		speed_l = (float)speed/100*(bar_ly + bar_rx);
    	speed_r = (float)speed/100*(bar_ly - bar_rx);
	}
	else if(speed<0)
	{
		speed_l = (float)speed/100*(bar_ly - bar_rx);
    	speed_r = (float)speed/100*(bar_ly + bar_rx);
	}
    
    motor(1, speed_l); 
    motor(2, speed_r);
  }
}


void run_gamepad_mecanum() 
{
	unsigned long lastGreenPress = 0;
	unsigned long lastRedPress = 0;
	unsigned long lastBluePress = 0;
	unsigned long lastPinkPress = 0;
	unsigned long lastR2Press = 0;

	bool greenWasPressed = false;
	bool redWasPressed = false;
	bool blueWasPressed = false;
	bool pinkWasPressed = false;
	bool R2WasPressed = false;

	int reset_puncher=0;
	unsigned long debounceDelay = 200;  // 200 milliseconds
	int joystick_x, joystick_y, joystick_rx;
	int motor_fl, motor_fr, motor_bl, motor_br;
	int max_speed = 100;
	double tr0=millis();
	msleep(500);
  	while (1) 
	{
		delay(50);
		ps2x.read_gamepad();

		joystick_x = -(ps2x.Analog(PSS_LX) - 128);
		joystick_y = ps2x.Analog(PSS_LY) - 128;
		joystick_rx = -(ps2x.Analog(PSS_RX) - 128);

		unsigned long currentTime = millis();

    	if (ps2x.Analog(PSAB_GREEN) > 170) 
		{
      		if (!greenWasPressed && currentTime - lastGreenPress > debounceDelay) 
			{
				green();
				lastGreenPress = currentTime;
      		}
      		greenWasPressed = true;
    	}	 
		else 
		{
			greenWasPressed = false;
		}

    if (ps2x.Analog(PSAB_RED) > 170) 
	{
		if (!redWasPressed && currentTime - lastRedPress > debounceDelay) 
		{
			red();
			lastRedPress = currentTime;
		}
      	redWasPressed = true;
    } 
	else 
	{
      	redWasPressed = false;
    }

    if (ps2x.Analog(PSAB_BLUE) > 170) 
	{
      if (!blueWasPressed && currentTime - lastBluePress > debounceDelay) 
	  {
        blue();
        lastBluePress = currentTime;
      }
      blueWasPressed = true;
    } 
	else {
      blueWasPressed = false;
    }

    if (ps2x.Analog(PSAB_PINK) > 170) {
      if (!pinkWasPressed && currentTime - lastPinkPress > debounceDelay) {
        pink();
        lastPinkPress = currentTime;
      }
      pinkWasPressed = true;
    } else {
      pinkWasPressed = false;
    }

	if (ps2x.Analog(PSAB_R2) > 170) {
      if (!R2WasPressed && currentTime - lastR2Press > debounceDelay) {
		set_servo_position(3,138);
		set_servo_position(0,180);
		msleep(1000);
        reset_puncher = 1;
        lastR2Press = currentTime;
      }
      R2WasPressed = true;
    } else {
      R2WasPressed = false;
    }
	
	if(reset_puncher)
	{
		if(analog(0)<500)
		{
			set_servo_position(0,180);
			tr0=millis();
		}
		else
		{
			if(millis()-tr0>1000)
			{
				set_servo_position(0,0);
				reset_puncher=0;
			}
		}
		
	}
    // Calculate motor speeds based on joystick inputs
    motor_fl = joystick_y + joystick_x + joystick_rx;
    motor_fr = joystick_y - joystick_x - joystick_rx;
    motor_bl = joystick_y - joystick_x + joystick_rx;
    motor_br = joystick_y + joystick_x - joystick_rx;

    // Limit motor speeds to a suitable range
    motor_fl = constrain(motor_fl, -max_speed, max_speed);
    motor_fr = constrain(motor_fr, -max_speed, max_speed);
    motor_bl = constrain(motor_bl, -max_speed, max_speed);
    motor_br = constrain(motor_br, -max_speed, max_speed);

    // Set motor speeds for Mecanum drive
    // Replace motor() calls with your actual motor control functions
    motor(0, motor_fl);  // Front Left Motor
    motor(1, motor_fr);  // Front Right Motor
    motor(2, motor_bl);  // Back Left Motor
    motor(3, motor_br);  // Back Right Motor
  }
}
