#pragma once

class C2DSimulator
{
public:
	C2DSimulator(const HWND InhWnd) 
		:
		hWnd(InhWnd)
	{}
	// �ùķ����͸� �ʱ�ȭ�Ѵ�.
	virtual void BuildEnvironment() {};
	// �浹ü���� ���Ű� ������ ó���Ѵ�.
	virtual void Update(float DeltaTime) {};
	virtual void Render() {};

	//�������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ��̴�. 
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {}
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {}
	virtual LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) { return LRESULT(); }

	inline HWND GetWnd() const { return hWnd; }

private:
	HWND hWnd;
};

