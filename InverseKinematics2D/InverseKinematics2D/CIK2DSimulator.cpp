#include "stdafx.h"
#include "CIK2DSimulator.h"
#include "stdafx.h"
#include "C2DCamera.h"
#include "C2DObjectIK.h"
#include "C2DMesh.h"
#include "Macro.h"
#include <assert.h>

void CIK2DSimulator::BuildEnvironment()
{
	CameraPtr = std::make_shared<C2DCamera>();
	ObjectIKPtr = std::make_shared<C2DObjectIK>();

	assert(CameraPtr);
	assert(ObjectIKPtr);

	CameraPtr->GenerateView(C2DVector(0.0f, 0.0f), C2DVector(0.0f, 1.0f));
	CameraPtr->GenerateProj(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
	CameraPtr->GenerateScreen(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
}

void CIK2DSimulator::Update(float DeltaTime)
{
	ObjectIKPtr->Update(DeltaTime);
}

void CIK2DSimulator::Render()
{
	RECT rect;
	GetClientRect(GetWnd(), &rect);
	HDC hdc = GetDC(GetWnd()); // 그림 그릴 윈도우의 DC 가져오기
	HDC hMemdc = CreateCompatibleDC(hdc); // 화면dc(그릴 윈도우) 기반 메모리 DC생성 
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom); // 비트맵 생성
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemdc, hBitmap); // 비트맵 선택

	::PatBlt(hMemdc, 0, 0, rect.right, rect.bottom, WHITENESS);
	//for (auto& object : ObjectList)
	//{
	//	object->Render(hMemdc, Camera);
	//}
	ObjectIKPtr->Render(hMemdc, *CameraPtr);
	::BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemdc, 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hMemdc, hOldBitmap));
	DeleteDC(hMemdc); // 메모리 dc 해제
	ReleaseDC(GetWnd(), hdc); // 화면 dc 해제
}

//윈도우의 메시지(키보드, 마우스 입력)를 처리하는 함수이다. 
void CIK2DSimulator::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
			CameraPtr->ZoomInOrOut(1.0f / 2.0f);
			break;
		case -120:
			CameraPtr->ZoomInOrOut(2.0f);
			break;
		}
		break;
	case WM_RBUTTONDOWN:
		oldClicked.x = LOWORD(lParam);       // 마우스의 x, y 를 받아 오고
		oldClicked.y = HIWORD(lParam);
		bDrag = true;
		break;
	case WM_MOUSEMOVE:
		if (bDrag)
		{
			const float deltaX = oldClicked.x - static_cast<float>(LOWORD(lParam));
			const float deltaY = -(oldClicked.y - static_cast<float>(HIWORD(lParam)));
			CameraPtr->Move(C2DVector(deltaX, deltaY) * 1.0f / CameraPtr->GetZoomScale());
			oldClicked.x = LOWORD(lParam);
			oldClicked.y = HIWORD(lParam);
		}
		break;
	case WM_LBUTTONDOWN:
	{
		C2DVector curClickedPoint(static_cast<float>(LOWORD(lParam)), static_cast<float>(HIWORD(lParam)));
		C2DMatrix mtxToWorld = CameraPtr->GetFromScreenToWorld();
		CVectorOperation::C2DTransform(&curClickedPoint, &curClickedPoint, &mtxToWorld);
		ObjectIKPtr->SetTargetPosition(curClickedPoint);
		oldClicked.x = LOWORD(lParam);
		oldClicked.y = HIWORD(lParam);
		break;
	}
	case WM_RBUTTONUP:
		oldClicked.x = 0;
		oldClicked.y = 0;
		bDrag = false;
		break;
	}
}

void CIK2DSimulator::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	}
}

LRESULT CALLBACK CIK2DSimulator::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}

	return 0;
}
