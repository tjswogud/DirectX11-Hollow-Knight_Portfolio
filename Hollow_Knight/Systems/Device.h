#pragma once

class Device : public Singleton<Device>
{
public:
	Device();
	~Device();

private:
	void InitDevice();

public:
	void Clear();
	void Present();

	ID3D11Device *        GetDevice() { return device; }
	ID3D11DeviceContext * GetDC()     { return deviceContext; }

private:
	ID3D11Device *        device;			  //CPU�� �ٷ�� ��ü - ���𰡸� ���� �� ���
	ID3D11DeviceContext* deviceContext; 	  //GPU�� �ٷ�� ��ü - ���𰡸� �׸� �� ���

	IDXGISwapChain* swapChain;       		  //������۸��� �����ϴ� ��ü
	ID3D11RenderTargetView* renderTargetView; //����۸� �����ϴ� ��ü  
};
