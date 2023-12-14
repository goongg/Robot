- [**Robot**](#robot)
  - [**Motor Control**](#motor-control)
      - [**23.12.08 기본 GPIO 제어 및 PWM 제어**](#231208-기본-gpio-제어-및-pwm-제어)
        - [**GPIO TEST**](#gpio-test)
        - [**PWM TEST**](#pwm-test)
      - [**23.12.13 라즈베리파이 Interface 설계**](#231213-라즈베리파이-interface-설계)
  - [Coding Rule](#coding-rule)
      - [**23.12.13 로봇 Class Architecture 재 설계**](#231213-로봇-class-architecture-재-설계)
  - [Controller](#controller)
  - [Pan Tilt Camera](#pan-tilt-camera)

# **Robot**
라즈베리파이 4B를 사용한 로봇 개발


## **Motor Control**
#### **23.12.08 기본 GPIO 제어 및 PWM 제어**

##### **GPIO TEST**
WiringPi는 이제 더 이상 지원되지 않음으로 사용할 수 없다.
libgpiod 등 다양한 방법이 있으나, <br>
어쨌거나 이번 프로젝트에서 PWM 등 다양한 로직을 같이 써야되므로 결국 sysfs를 사용하는것으로 결정하자. (추후 MCU처럼 레지스터를 직접 제어하는 방법도 시도해보자)

우선 /sys/class/gpio/ 에 파일스크립터를 통해서 제어해보자.

```
goong_pi@raspberrypi:~/Desktop/Robot $ echo "21" > /sys/class/gpio/export
goong_pi@raspberrypi:~/Desktop/Robot $ echo "out" > /sys/class/gpio/gpio21/direction
goong_pi@raspberrypi:~/Desktop/Robot $ echo "1" > /sys/class/gpio/gpio21/value
```
잘 된다. 

유닉스에서는 echo 명령어를 이용하면 파일이나 디바이스에 원하는 값을 출력할 수 있다.
PitOut 에서 Pin Map을 보고 pin 40에 해당하는 GPIO21 Class 폴더를 생성하고,
방향과 값을 입력한 것이다.

기본적으로 L298N 2ch DC Motor 드라이버 모듈을 사용하기 위해서는
4개의 GPIO OutPut이 필요하다. 우선 기본적으로 각 모터에 AB가 있고 논리표는 아래와 같다. 이걸 컨트롤러 인풋에 따라 적절하게 조정해야 한다.
A | B <br>
L | L : 전원연결 X <br>
L | H : 역방향 회전 <br>
H | L : 정방향 회전 <br>
H | H : 브레이크 <br>


##### **PWM TEST**

라즈베리파이의 출력전압은 3.3V 이고, 모터드라이버의 입력 전원은 5v이다. 모터드러이버 논리 H에 3.3V 사용가능하기 때문에 모터드라이버에 각 라인을 할당에서 그냥 넣어주면 된다.

핀할당은 32번과 33번을 사용하기로 하자. <br>
- **IN_A1 GPIO 18 (PWM0) Port 12.**<br>
- **IN_A2 GPIO 17        Port 11.**<br>
<br>
- **IN_B1 GPIO 13 (PWM1) Port 33.** <br>
- **IN_B2 GPIO 19        Port 35.** <br>
<br>


일단 boot config에 PWM Chip을 활성화 해야한다.
활성화 하는 방법은 아래와 같음.
```
Now its just a matter of putting the appropriate dtoverlay line into /boot/config.txt:

A single PWM uses a command like ‘dtoverlay=pwm,pin=#,func=#’
eg PWM0 on GPIO18 for a rPi A

dtoverlay=pwm,pin=18,func=2
To setup 2 PWMs use a command like ‘dtoverlay=pwm-2chan,pin=#,func=#,pin2=#,func2=#’
eg PWM0 on GPIO12 & PWM1 on GPIO13 for a rPi2 B

dtoverlay=pwm-2chan,pin=12,func=4,pin2=13,func2=4
FYI: This is all documented in /boot/overlays/README.
```
이걸 하면
/sys/class/pwm/ 에 pwmchip0이 생긴걸 확인할 수 있다.

이제 expert 명령어로 pwm 체널에 대한 세팅을 할 수 있음.
```
root@raspberrypi:/# cd/sys/class/pwm/pwmchip0/
root@raspberrypi:/sys/class/pwm/pwmchip0/# echo 0 > export
root@raspberrypi:/sys/class/pwm/pwmchip0/# cd pwm0
root@raspberrypi:/sys/class/pwm/pwmchip0/pwm0# echo 1000000 > period
root@raspberrypi:/sys/class/pwm/pwmchip0/pwm0# echo 1000000 > duty_cycle 
root@raspberrypi:/sys/class/pwm/pwmchip0/pwm0# echo 1 > enable
```
OK.

#### **23.12.13 라즈베리파이 Interface 설계**
우선 기능을 모두 cpp로 구현하기로 하자. 공부한 SOLID 원칙을 최대한 적용하고 실습해보자.

우선 파일 / 폴더구조와 함수명 규칙을 정해보자

## Coding Rule
[파일명]
1. 파일명은 모두 소문자로
2. 프로젝트의 소스코드는 프로젝트와 동일한 이름의 디렉토리에 배치
3. #include 는 모두 <>로 쓰고 인크루드 페스를
4. 컴파일 옵션에 인크루드 페쓰 추가

[타입명]
1. 타입명은 모두 대문자로
2. 새 단어마다 대문자 사용
3. 언더스코어는 사용하지 않음
4. 모든 타입은 동일한 명명법 사용
5. 굳이 축약어 쓰진 말자

[일단 만들어야 하는 Class]
1. 라즈베리파이 sysfs 컨트롤 gpio / pwm  등.
2. 모터제어 알고리즘
3. Xinput 등 컨트롤러 제어
4. 카메라 모션 제어 알고리즘
5. 동영상 스트리밍 


그리고 여기서 모터제어 Class의 경우 플랫폼의 GPIO 세팅에 의존해야한다.<br>
**이걸 추상화 클레스와 인터페이스로 설계하도록하자.**

우선 폴더 트리를 만들었다.<br>
-- /Camera/Camera.cpp & h <br>
-- /Motor/Motor.cpp & h <br>
-- /RaspSysfs/RaspSysfs.cpp & h <br>
-- /Controller/Controller.cpp & h <br>

-- ../Main.cpp<br>

여기서 모터제어와 카메라제어 그리고 컨트롤러 인풋 체크는
주기적으로 수행되어야 하므로 생성자에 주기 thread를 생성.

우선 설계된 클레스는 아래와 같다.

```c++
class RaspSysfs
{
    public:
        RaspSysfs();
        ~RaspSysfs();    
        void setGPIOValue(int pin, int value);
        void setPwmDutyCycle(int pwm, int dutyCycle);

    private:
        void initPort(void);
        void exportGPIO(int pin);
        void setGPIODirection(int pin, const char *direction);
        void setPWMPeriod(int pwm, int period);
        void exportPWM(int pwm);
        void enablePWM(int pwm);
};


class Motor
{
    public:
        Motor();
        Motor(void (*_setPinVal)(int,int), void (*_setPwmDutyCycle)(int,int));
        ~Motor();
        void move(int direct[8], int Speed);
        void *setPinValue(int pin, int value);
        void *setPwmDutyCycle(int pwm, int dutyCycle);
};

class Controller {
public:
    Controller();
    ~Controller();
    void getKeystate(int *output);
private:
    int ButtonState[4];
    pthread_t thread_;
    static void* thread_Controller1ms(void* arg);
};

```

#### **23.12.13 로봇 Class Architecture 재 설계**

음 이렇게 설계를 하고 보니 의존성 관계와 이름이 애매해 졌다.
우선 기본적으로 Motor는 라즈베리파이를 의존해야 한다.
그리고 Controller하고도 데이터 송수신이 이루어 져야 한다.
그래서 대폭 수정한다.







## Controller
- usblib Test
- 8bitdo HID, Data Input Test
- Make Controller Reciver Task

## Pan Tilt Camera
우선 라즈베리파이 4에는 PWM Out이 없어서 Pan Tilt 메라의 사용이 불가능하다. 보류로 해둔다.카
