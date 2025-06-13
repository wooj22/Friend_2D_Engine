// World = local * parent->world
// Screen = world * camera 역행렬

// Uniny Style Screen position
// 좌표계 - 중앙 (0,0), 왼쪽위(-, +), 오른쪽 아래(+, -)
// D2D에서 유니티 좌표계처럼 사용하려면 꼼수가 필요함
// Screen = renderMatrix * world * camera 역행렬 * unity matrix
//  unity matrix는 중심 이동과 y 반전에 대항 행렬값을 가지고 있다.
//  renderMatrix는 unity matrix에 대응하기 위해 y scale에 -1을 준 행렬
//  transform 멤버에 저장하면 자식까지 누적 영향을 미치기 때문에 연산에만 사용해야한다.

// Dirty 패턴
// transform이 변경에 대한 flag를 활용하여 
// 매 프레임마다 불필요하게 행렬을 다시 계산하지 않도록 하는 방식

#include <d2d1_1.h>
#include <vector>

/* Transform Component*/
class Transform
{
private:
    // transform
    D2D1_POINT_2F position;
    float rotation;
    D2D1_POINT_2F scale;


    // parent, child
    Transform* parent = nullptr;
    //std::vector<Transform*> children;

    // dirty patten
    bool isDirty = true;
    D2D1::Matrix3x2F localMatrix;

public:
    // matrix
    static D2D1::Matrix3x2F cameraInversMatrix;   // screen size 필요
    static D2D1::Matrix3x2F unityMatrix;          // screen size 필요
    static D2D1::Matrix3x2F renderMatrix;

public:
    Transform() : position{ 0.0f, 0.0f }, rotation(0.0f), 
        scale{ 1.0f, 1.0f }, parent(nullptr) { localMatrix = D2D1::Matrix3x2F::Identity(); }

    void SetParent(Transform* newParent);
    void ResetTransform();

    // set
    void SetPosition(float x, float y) { isDirty = true; position = { x, y }; }
    void SetRotation(float angle) { isDirty = true; rotation = angle; }
    void SetScale(float scaleX, float scaleY) { isDirty = true; scale = { scaleX, scaleY }; }
    
    // add
    void AddPosition(float x, float y) { isDirty = true; position.x += x; position.y += y; }
    void AddRotation(float angle) { isDirty = true; rotation += angle; }
    void AddScale(float scaleX, float scaleY) { isDirty = true; scale.x += scaleX; scale.y += scaleY; }
    
    // get
    D2D1_POINT_2F GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    D2D1_POINT_2F GetScale() const { return scale; }

    // get matrix
    D2D1::Matrix3x2F GetLocalMatrix();
    D2D1::Matrix3x2F GetWorldMatrix();
    D2D1::Matrix3x2F GetScreenMatrix();
};