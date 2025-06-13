#include <d2d1.h>
#include <vector>

/* Transform Component*/
// World = this->local * parent->world
// Screen = this->world * camera 역행렬

// Uniny Style Screen position
// 좌표계 - 중앙 (0,0), 왼쪽위(-, +), 오른쪽 아래(+, -)
// D2D에서 유니티 좌표계처럼 사용하려면 꼼수가 필요함
// Screen position = renderMatrix * this->world * camera 역행렬 * unity matrix
//  renderMatrix는 unity matrix에 대응하기 위해 y scale에 -1을 준 행렬
//  transform멤버에 저장하면 자식까지 누적 영향을 미치기 때문에 World 계산 직전에 연산만 해야한다.

class Transform
{
private:
    // transform
    D2D1_POINT_2F position;
    float rotation;
    D2D1_POINT_2F scale;

    // parent, child
    Transform* parent = nullptr;
    std::vector<Transform*> children;

public:
    // matrix
    static D2D1_MATRIX_3X2_F cameraInversMatrix;
    static D2D1_MATRIX_3X2_F unityMatrix;
    static D2D1_MATRIX_3X2_F renderMatrix;

public:
    Transform() : position{ 0.0f, 0.0f }, rotation(0.0f), 
        scale{ 1.0f, 1.0f }, parent(nullptr) {}

    void SetPosition(float x, float y) { position = { x, y }; }
    void SetRotation(float angle) { rotation = angle; }
    void SetScale(float scaleX, float scaleY) { scale = { scaleX, scaleY }; }
    D2D1_POINT_2F GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    D2D1_POINT_2F GetScale() const { return scale; }

    void SetParent(Transform* newParent);
    D2D1_MATRIX_3X2_F GetLocalMatrix() const;
    D2D1_MATRIX_3X2_F GetWorldMatrix() const;
    D2D1_MATRIX_3X2_F GetScreenMatrix() const;
};