
//мотор
#define DRU A2 //16
#define DRD A3 //17
#define DLU A0 //14
#define DLD A1 //15
//рулевое
#define RRU 10
#define RRD 11
#define RLU 13
#define RLD 12

#define RRU_Out DDRB |=B00000100
#define RRD_Out DDRB |=B10001000
#define RLD_Out DDRB |=B00010000
#define RLU_Out DDRB |=B00100000

#define DLU_Out DDRC |=B00000001
#define DLD_Out DDRC |=B00000010
#define DRU_Out DDRC |=B00000100
#define DRD_Out DDRC |=B00001000

#define RRU_High PORTB|=B00000100     
#define RRD_High PORTB|=B00001000   
#define RLD_High PORTB|=B00010000   
#define RLU_High PORTB|=B00100000   
  
#define DLU_High PORTC |=B00000001   
#define DLD_High PORTC |=B00000010    
#define DRU_High PORTC |=B00000100   
#define DRD_High PORTC |=B00001000  

#define RRU_Low PORTB &=B11111011 
#define RRD_Low PORTB &=B11110111 
#define RLD_Low PORTB &=B11101111 
#define RLU_Low PORTB &=B11011111 

#define DLU_Low PORTC &= B11111110  
#define DLD_Low PORTC &= B11111101 
#define DRU_Low PORTC &= B11111011 
#define DRD_Low PORTC &= B11110111

void driveOff();
void driveStop();
void driveFrw();
void driveRew();
void initDrive();
void steerOff();
void steerLeft();
void steerRight();
void steerFrw();
void setMotors(int dir, int steer);
void move_back(int dir, int steer);