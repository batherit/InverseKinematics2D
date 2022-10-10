#pragma once

class C2DSimulator
{
public:
	C2DSimulator(const HWND InhWnd) 
		:
		hWnd(InhWnd)
	{}
	// 시뮬레이터를 초기화한다.
	virtual void BuildEnvironment() {};
	// 충돌체들의 갱신과 렌더를 처리한다.
	virtual void Update(float DeltaTime) {};
	virtual void Render() {};

	//윈도우의 메시지(키보드, 마우스 입력)를 처리하는 함수이다. 
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {}
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {}
	virtual LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) { return LRESULT(); }

	inline HWND GetWnd() const { return hWnd; }

private:
	HWND hWnd;
};

