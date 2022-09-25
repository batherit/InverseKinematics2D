#pragma once
#include <vector>
#include <memory>
#include "CTimer.h"
#include "C2DCamera.h"

class C2DObject;

class C2DSimulator
{


public:
	// �ùķ����͸� �ʱ�ȭ�Ѵ�.
	void Init(const HWND InhWnd);

	// �浹ü���� ���Ű� ������ ó���Ѵ�.
	void Update();
	void Render();

	//�������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ��̴�. 
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;

	CTimer Timer;
	C2DCamera Camera;
	std::vector<std::shared_ptr<C2DObject>> ObjectList;
};

