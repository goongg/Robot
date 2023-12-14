#include <Xinput.h>
#include <iostream>

int main() {
    // XInput 초기화

    // 루프에서 컨트롤러 상태 읽기
    int cnt;
    while (true) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
            std::cout << cnt++ <<std::endl;
        // 첫 번째 컨트롤러 읽기
        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            // 여기에서 state 구조체의 멤버를 사용하여 컨트롤러 값에 접근할 수 있습니다.
            // 예: state.Gamepad.sThumbLX는 왼쪽 써클 패드의 X 축 값입니다.

            std::cout << "Left Thumbstick X: " << state.Gamepad.sThumbLX << std::endl;
        }

        // 잠시 기다리기
        Sleep(100);
    }

    return 0;
}