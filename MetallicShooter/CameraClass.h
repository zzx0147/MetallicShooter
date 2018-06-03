#pragma once
class CameraClass : public AlignedAllocationPolicy<16>
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();
	void Render();
	void GetViewMatrix(XMMATRIX&);

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix;
};

