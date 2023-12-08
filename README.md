- [**Robot**](#robot)
  - [**Motor Control**](#motor-control)
      - [**23.12.08 기본 GPIO 제어 및 PWM 제어**](#231208-기본-gpio-제어-및-pwm-제어)
        - [**GPIO TEST**](#gpio-test)
        - [**PWM TEST**](#pwm-test)
  - [Controller](#controller)
  - [Pan Tilt Camera](#pan-tilt-camera)

# **Robot**
라즈베리파이 4B를 사용한 로봇 개발


## **Motor Control**
#### **23.12.08 기본 GPIO 제어 및 PWM 제어**

##### **GPIO TEST**
WiringPi를 사용하는것에 대해서는 많은 예제가 있지만 MCU에서처럼 직접 레지스터를 제어하거나, 파일 디스크립터에 접근해서 수정하여 제어하는 방법에 대해서는 그닥 많은정보가 있진 않은것 같다.

게다가 구글링을 좀 해보니 Arm 64 아키텍쳐에서는 Wiring pi를 제공하지 않는것 같다.
cat /proc/device-tree/model 을 치면 모델명이 확인 가능하다. <BR> <br>
내가 가진 모델은: Raspberry Pi 4 Model B Rev 1.2

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

아근데 아쉬운게 PWM 포트가 두개 뿐이다.
아쉽지만, 후진의 경우 GPIO O으로 자체 PWM을 만든다음.. 느리게 구현해야할지도 모르겠다. 일단 TBD로 남겨두자. <br>

핀할당은 32번과 33번을 사용하기로 하자. <br>
- **IN_A1 GPIO 18 (PWM0) Port 12.**<br>
- **IN_A2 GPIO 17        Port 11.**<br>
<br>
- **IN_B1 GPIO 13 (PWM1) Port 33.**<br>
- **IN_B2 GPIO 19        Port 35.**<br>
<br>


아래 명령어로 활성화된 PWM 포트를 확인하고 node를 통해 접근할 수 있도록 export 해보자




- PWM Output
- Robot Platform DC Modoter Driver Conect
- Make Motor Control Task


## Controller
- usblib Test
- 8bitdo HID, Data Input Test
- Make Controller Reciver Task

## Pan Tilt Camera
우선 라즈베리파이 4에는 PWM Out이 없어서 Pan Tilt 카메라의 사용이 불가능하다. 보류로 해둔다.
