// DX12Tutorial1DirectXMath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <DirectXMath.h>

using namespace std;
using namespace DirectX;

void PrintVector(XMVECTOR p);

void PrintMatrix(XMMATRIX *m);
void PrintMatrixRow(XMVECTOR p);

void InputToExit();


int main()
{
	XMVECTOR a = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR b = XMVectorSet(0.0f, 2.0f, 0.0f, 0.0f);
	XMVECTOR c = XMVectorSet(0.0f, 0.0f, 3.0f, 0.0f);
	XMVECTOR d = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);

	XMVECTOR r1 = a + b;
	XMVECTOR r2 = b - d;
	XMVECTOR r3 = c * 5.0f;


	cout << "a + b = ";
	PrintVector(r1);
	
	cout << "b - d = ";
	PrintVector(r2);
	
	cout << "c * 5.0 = ";
	PrintVector(r3);


	XMVECTOR aDotd = XMVector3Dot(a, d);
	XMVECTOR aCrossb = XMVector3Cross(a, b);
	XMVECTOR lengthOfd = XMVector3Length(d);
	XMVECTOR dNormalized = XMVector3Normalize(d);

	cout << "a . d = ";
	PrintVector(aDotd);

	cout << "a x b = ";
	PrintVector(aCrossb);

	cout << "|d| = ";
	PrintVector(lengthOfd);

	cout << "d normalized = ";
	PrintVector(dNormalized);


	XMMATRIX mA(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 1.0f, 0.0f,
				2.0f, 2.0f, 2.0f, 0.0f,
				1.0f, 1.0f, 1.0f, 1.0f);


	XMMATRIX mB(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 2.0f, 0.0f,
				2.0f, 2.0f, 2.0f, 1.0f);

	XMMATRIX AxB = mA * mB;
	XMMATRIX mIdent = XMMatrixIdentity();
	XMMATRIX ATranpose = XMMatrixTranspose(mB);


	cout << endl << "mA = " << endl;
	PrintMatrix(&mA);

	cout << endl << "AxB = " << endl;
	PrintMatrix(&AxB);

	cout << endl << "mIdent = " << endl;
	PrintMatrix(&mIdent);

	cout << endl << "ATranpose = " << endl;
	PrintMatrix(&ATranpose);

	XMMATRIX trans = XMMatrixTranslation(10.0f, 5.0f, 1.0f);
	XMMATRIX scale = XMMatrixScaling(2.0f, 2.0f, 2.0f);
	XMMATRIX rotX = XMMatrixRotationX(45.0f);
	XMMATRIX world = rotX * scale * trans;

	cout << endl << "world = " << endl;
	PrintMatrix(&world);


	InputToExit();


	return 0;
}

void PrintVector(XMVECTOR p)
{
	XMFLOAT3 c;
	XMStoreFloat3(&c, p);

	cout << "(" << c.x << ", " << c.y << ", " << c.z << ")" << endl;
}

void PrintMatrix(XMMATRIX *m)
{
	for (int i = 0; i < 4; i++)
	{
		PrintMatrixRow(m->r[i]);
	}
}

void PrintMatrixRow(XMVECTOR p)
{
	XMFLOAT4 c;
	XMStoreFloat4(&c, p);

	cout << "[" << c.x << "\t" << c.y << "\t" << c.z << "\t" << c.w << "]" << endl;
}

void InputToExit()
{
	cout << "Press ENTER to quit";
	cin.ignore();
}