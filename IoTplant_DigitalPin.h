

  
int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value,0, 800, 0, 100);
  return percentValue;
}
class DigitalPin
{
public:
	DigitalPin(int pin);
	void begin();
	void on();
	void off();
private:
    int _pin;	
};
DigitalPin::DigitalPin(int pin){
	_pin = pin;
}
void DigitalPin::begin(){
	  pinMode(_pin, OUTPUT);
}

void DigitalPin::on(){
	   digitalWrite(_pin, HIGH);     
}
void DigitalPin::off(){
	   digitalWrite(_pin,LOW);     
}



