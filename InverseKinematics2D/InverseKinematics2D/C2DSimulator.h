#pragma once
#include <vector>
#include <memory>
#include "CTimer.h"
#include "C2DCamera.h"

class C2DObject;

class C2DSimulator
{


public:
	// 시뮬레이터를 초기화한다.
	void Init(const HWND InhWnd);

	// 충돌체들의 갱신과 렌더를 처리한다.
	void Update();
	void Render();

	//윈도우의 메시지(키보드, 마우스 입력)를 처리하는 함수이다. 
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;

	CTimer Timer;
	C2DCamera Camera;
	std::vector<std::shared_ptr<C2DObject>> ObjectList;
};

