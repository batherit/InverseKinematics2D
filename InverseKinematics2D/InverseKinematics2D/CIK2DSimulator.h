#pragma once
#include "C2DSimulator.h"
#include <memory>

class C2DCamera;
class C2DObjectIK;

class CIK2DSimulator : public C2DSimulator
{
public:
	CIK2DSimulator(HWND hWnd)
		:
		C2DSimulator(hWnd)
	{}

	void BuildEnvironment();
	// 충돌체들의 갱신과 렌더를 처리한다.
	void Update(float DeltaTime);
	void Render();

	//윈도우의 메시지(키보드, 마우스 입력)를 처리하는 함수이다. 
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	std::shared_ptr<C2DCamera> CameraPtr;
	std::shared_ptr<C2DObjectIK> ObjectIKPtr;
};

