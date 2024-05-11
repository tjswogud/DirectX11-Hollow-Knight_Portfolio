#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	MatrixBuffer()
		: ConstantBuffer(&data, sizeof(data))
	{
		data.matrix = XMMatrixIdentity(); // matrix�� �����ڿ��� ������ �ʱ�ȭ ������Ѵ�.
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
		// ConstantBuffer�� 16byte ������ �Ѱ�����Ѵ�. �� byte�� ����ٸ� ������ ä���� �ڷ��� ���̸� ����������Ѵ�.
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