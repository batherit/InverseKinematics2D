#include "stdafx.h"
#include "C2DSimulator.h"
#include "C2DObject.h"
#include "C2DObjectIK.h"
#include "C2DMesh.h"
#include "Macro.h"

void C2DSimulator::Init(const HWND InhWnd)
{
	hWnd = InhWnd;

	Camera.GenerateView(C2DVector(0.0f, 0.0f), C2DVector(0.0f, 1.0f));
	Camera.GenerateProj(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
	Camera.GenerateScreen(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);

	ObjectList.push_back(std::make_shared<C2DObjectIK>());
}

void C2DSimulator::Update()
{
	Timer.Tick();

	for (std::shared_ptr<C2DObject>& object : ObjectList)
	{
		object->Update(Timer.GetTimeElapsed());
	}
}

void C2DSimulator::Render()
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	HDC hdc = GetDC(hWnd); // �׸� �׸� �������� DC ��������
	HDC hMemdc = CreateCompatibleDC(hdc); // ȭ��dc(�׸� ������) ��� �޸� DC���� 
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom); // ��Ʈ�� ����
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemdc, hBitmap); // ��Ʈ�� ����

	::PatBlt(hMemdc, 0, 0, rect.right, rect.bottom, WHITENESS);
	for (auto& object : ObjectList)
	{
		object->Render(hMemdc, Camera);
	}
	::BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemdc, 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hMemdc, hOldBitmap));
	DeleteDC(hMemdc); // �޸� dc ����
	ReleaseDC(hWnd, hdc); // ȭ�� dc ����
}

//�������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ��̴�. 
void C2DSimulator::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	static POINT oldClicked;
	static bool bDrag = false;

	int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

	switch (nMessageID)
	{
	case WM_MOUSEWHEEL:
		switch (zDelta)
		{
		case 120:
			Camera.ZoomInOrOut(1.0f / 2.0f);
			break;
		case -120:
			Camera.ZoomInOrOut(2.0f);
			break;
		}
		break;
	case WM_RBUTTONDOWN:
		oldClicked.x = LOWORD(lParam);       // ���콺�� x, y �� �޾� ����
		oldClicked.y = HIWORD(lParam);
		bDrag = true;
		break;
	case WM_MOUSEMOVE:
		if (bDrag)
		{
			const float deltaX = oldClicked.x - static_cast<float>(LOWORD(lParam));
			const float deltaY = -(oldClicked.y - static_cast<float>(HIWORD(lParam)));
			Camera.Move(C2DVector(deltaX, deltaY) * 1.0f / Camera.GetZoomScale());
			oldClicked.x = LOWORD(lParam);
			oldClicked.y = HIWORD(lParam);
		}
		break;
	case WM_RBUTTONUP:
		oldClicked.x = 0;
		oldClicked.y = 0;
		bDrag = false;
		break;
	}
}

void C2DSimulator::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	}
}

LRESULT CALLBACK C2DSimulator::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}

	return 0;
}
