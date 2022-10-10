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
	// �浹ü���� ���Ű� ������ ó���Ѵ�.
	void Update(float DeltaTime);
	void Render();

	//�������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ��̴�. 
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

private:
	std::shared_ptr<C2DCamera> CameraPtr;
	std::shared_ptr<C2DObjectIK> ObjectIKPtr;
};

