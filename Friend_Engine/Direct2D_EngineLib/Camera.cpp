#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"

void Camera::OnEnable_Inner()
{
    CameraSystem::Get().Regist(this);
	transform = this->gameObject->transform;
    if (mainCamera == nullptr) mainCamera = this;
}   

void Camera::OnDisable_Inner()
{
	CameraSystem::Get().Unregist(this);
	transform = nullptr;
}

void Camera::Update()
{
    if (!transform) return;

    // shake
    if (isShaking)
    {
        shakeTime += Time::GetDeltaTime();
        shakeTimer += Time::GetDeltaTime();

        // ��鸲 ���� ���� ��� (1 �� 0���� �پ��)
        float progress = shakeTime / shakeDuration;
        float damping = 1.0f - progress;

        // �ұ�Ģ�� ���� (0~1), 0�� �ε巴�� 1�� ���� �ұ�Ģ
        const float roughness = 0.6f;

        // ����/�ڻ��� ������
        float baseX = sinf(shakeTimer * shakeFrequency * 2 * 3.14159f);
        float baseY = cosf(shakeTimer * shakeFrequency * 2 * 3.14159f);

        // �����Ӻ� ���� �� (-1 ~ 1)
        float randomX = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
        float randomY = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;

        // base ������ ���� ���� roughness�� ���� ���
        float offsetX = (baseX * (1.0f - roughness) + randomX * roughness) * shakeAmplitude * damping;
        float offsetY = (baseY * (1.0f - roughness) + randomY * roughness) * shakeAmplitude * damping;

        shakeOffset = Vector2(offsetX, offsetY);

        if (shakeTime >= shakeDuration)
        {
            isShaking = false;
            shakeOffset = Vector2::zero;
        }
    }
    else
    {
        shakeOffset = Vector2::zero;
    }
    transform->Translate(shakeOffset);

    // zoom
    Vector2 camPos = transform->GetWorldPosition();
    float scale = 1.0f / zoom;

    D2D1::Matrix3x2F zoomMatrix =
        D2D1::Matrix3x2F::Translation(-camPos.x, -camPos.y) *
        D2D1::Matrix3x2F::Scale(scale, scale) *
        D2D1::Matrix3x2F::Translation(camPos.x, camPos.y);

    // target trace
    TargetTrace();

    // map boundary condition
    if (useMapCondition)
        MapBoundaryCondition();

    // maxtrix update
    worldMatrix = zoomMatrix * transform->GetWorldMatrix();
    inverseMatrix = worldMatrix;
    inverseMatrix.Invert();  
}

void Camera::OnDestroy_Inner()
{
    CameraSystem::Get().Unregist(this);
    if (mainCamera == this) mainCamera = nullptr;
}

// static
// main camera
Camera* Camera::mainCamera = nullptr;

void Camera::SetMainCamera(Camera* cam)
{
	mainCamera = cam;
}

Camera* Camera::GetMainCamera()
{
	return mainCamera;
}

const D2D1::Matrix3x2F& Camera::GetMainInverseMatrix()
{
    return mainCamera->inverseMatrix;
}

// Culling
bool Camera::IsInView(const Vector2& worldPos, const Vector2& boundSize) const
{
    if (!transform) return false;

    Vector2 cameraPos = transform->GetWorldPosition();
    Vector2 viewPos = worldPos - cameraPos;

    float halfW = viewSize.x * 0.5f;
    float halfH = viewSize.y * 0.5f;

    return !(viewPos.x + boundSize.x < -halfW ||
        viewPos.x - boundSize.x >  halfW ||
        viewPos.y + boundSize.y < -halfH ||
        viewPos.y - boundSize.y >  halfH);
}

// Target Trace
void Camera::TargetTrace()
{
    if (target && useTargetTrace)
    {
        Vector2 targetPos = target->GetWorldPosition();
        Vector2 currentPos = transform->GetWorldPosition();
        Vector2 dist = targetPos - currentPos;

        // trace limit
        if (std::abs(dist.x) <= targetTraceLimitX) dist.x = 0;
        if (std::abs(dist.y) <= targetTraceLimitY) dist.y = 0;

        // trace
        if (dist.x != 0 || dist.y != 0)
        {
            Vector2 dir = dist.Normalized();

            // move
            float moveX = dir.x * targetTraceXSpeed * Time::GetDeltaTime();
            float moveY = dir.y * targetTraceYSpeed * Time::GetDeltaTime();

            // �������� ����
            if (std::abs(moveX) > std::abs(dist.x)) moveX = dist.x;
            if (std::abs(moveY) > std::abs(dist.y)) moveY = dist.y;

            transform->Translate(moveX, moveY);
        }
    }
}

// Map Boundary Condition
void Camera::MapBoundaryCondition()
{
    Vector2 cameraPos = transform->GetWorldPosition();
    Vector2 halfSize = viewSize * 0.5f;

    // mab boundary
    float minX = mapRect.Left() + halfSize.x;
    float maxX = mapRect.Right() - halfSize.x;
    float minY = mapRect.Bottom() + halfSize.y;
    float maxY = mapRect.Top() - halfSize.y;

    // Clamp
    if (cameraPos.x < minX) cameraPos.x = minX;
    if (cameraPos.x > maxX) cameraPos.x = maxX;
    if (cameraPos.y < minY) cameraPos.y = minY;
    if (cameraPos.y > maxY) cameraPos.y = maxY;

    // condition
    transform->SetPosition(cameraPos);
}

// Camera Shake
// ����, �ֱ�, ���ӽð�, �ұ�Ģ����(��ĥ��)
void Camera::Shake(float amplitude, float frequency, float duration, float roughness)
{
    isShaking = true;
    shakeAmplitude = amplitude;
    shakeFrequency = frequency;
    shakeDuration = duration;
    shakeTime = 0.0f;
    shakeTimer = 0.0f;
    shakeRoughness = roughness;
}

/*   Screen->World ��ȯ   */
// screenPos(unity style) -> worldPos(unity style)
Vector2 Camera::GetScreenToWorldPosition(Vector2 screenPos_unity)
{
    Vector2 camPos = mainCamera->transform->GetWorldPosition();

    float worldX = screenPos_unity.x + camPos.x;
    float worldY = screenPos_unity.y + camPos.y;

    return { worldX, worldY };
}

// screenPos(d2d style) -> worldPos(unity style)
Vector2 Camera::GetScreenToWorldPosition_D2D(Vector2 screenPos_d2d, Vector2 viewSize)
{
    Vector2 camPos = mainCamera->transform->GetWorldPosition();

    float worldX = screenPos_d2d.x + viewSize.x - 1920 / 2.0f;
    float worldY = (viewSize.y / 2.0f - screenPos_d2d.y) + camPos.y;

    return { worldX, worldY };
}