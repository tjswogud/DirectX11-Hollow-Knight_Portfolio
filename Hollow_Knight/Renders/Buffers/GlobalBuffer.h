#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	MatrixBuffer()
		: ConstantBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity(); // matrix는 생성자에서 무조건 초기화 해줘야한다.
	}

	void Set(Matrix matrix) 
	{
		data.matrix = XMMatrixTranspose(matrix);
	}

private:
	struct Data
	{
		Matrix matrix;
	};

	Data data;
};

class ColorBuffer : public ConstantBuffer
{
public:
	ColorBuffer()
		// ConstantBuffer은 16byte 단위로 넘겨줘야한다. 빈 byte가 생긴다면 나머지 채워줄 자료형 더미를 생성해줘야한다.
		: ConstantBuffer(&data, sizeof(data))
	{
		data.color = Vector4(1, 1, 1, 1);
	}

	void Set(Vector4 color) 
	{
		data.color = color;
	}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		data.color = Vector4(r, g, b, a);
	}

private:
	struct Data
	{
		Vector4 color;
	};

	Data data;
};