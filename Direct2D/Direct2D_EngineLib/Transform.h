#include <d2d1.h>
#include <vector>

class Transform
{
private:
    D2D1_POINT_2F position;
    float rotation;             // degrees
    D2D1_POINT_2F scale;

    Transform* parent = nullptr;
    std::vector<Transform*> children;

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
};