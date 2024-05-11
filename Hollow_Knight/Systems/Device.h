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
	ID3D11Device *        device;			  //CPU를 다루는 객체 - 무언가를 만들 때 사용
	ID3D11DeviceContext* deviceContext; 	  //GPU를 다루는 객체 - 무언가를 그릴 때 사용

	IDXGISwapChain* swapChain;       		  //더블버퍼링에 관여하는 객체
	ID3D11RenderTargetView* renderTargetView; //백버퍼를 관리하는 객체  
};
