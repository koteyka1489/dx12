#include "BaseSceneObject.h"
#include "PixProfile.h"


#if defined PIXPROFILE
#define USE_PIX
#include <pix3.h>
#endif

void BaseSceneObject::Update(float dt)
{
#if defined PIXPROFILE
    PIXScopedEvent(PIX_COLOR(60, 150, 60), L"Update Objcet");
#endif

    mMovementComponent.Update(dt);
    UpdateReflectedMatrix();
    UpdateShadowMatrix();
}

void BaseSceneObject::SetContiniusRotation(Rotator rot)
{
    mMovementComponent.SetContinuesRotation(rot);
}

void BaseSceneObject::SetMaterialTransformation(Transform trs) noexcept 
{
    DirectX::XMStoreFloat4x4(&mRenderItem->Mat->MatTransform, trs.GetWorldMatrix());
}

void BaseSceneObject::SetMaterialTranslation(Vector vec) noexcept 
{
    Transform trs(vec, Rotator::Zero(), Vector::One());
    DirectX::XMStoreFloat4x4(&mRenderItem->Mat->MatTransform, trs.GetWorldMatrix());
}

void BaseSceneObject::SetMaterialRotation(Rotator rot) noexcept 
{
    Transform trs(Vector::Zero(), rot, Vector::One());
    DirectX::XMStoreFloat4x4(&mRenderItem->Mat->MatTransform, trs.GetWorldMatrix());
}

void BaseSceneObject::SetMaterialScale(Vector scale) noexcept 
{
    Transform trs(Vector::Zero(), Rotator::Zero(), scale);
    DirectX::XMStoreFloat4x4(&mRenderItem->Mat->MatTransform, trs.GetWorldMatrix());
}

void BaseSceneObject::SetTextureTransformation(Transform trs) noexcept 
{
    DirectX::XMStoreFloat4x4(&mRenderItem->TexTransform, trs.GetWorldMatrix());
}

void BaseSceneObject::SetTextureTranslation(Vector vec) noexcept 
{
    Transform trs(vec, Rotator::Zero(), Vector::One());
    DirectX::XMStoreFloat4x4(&mRenderItem->TexTransform, trs.GetWorldMatrix());
}

void BaseSceneObject::SetTextureRotation(Rotator rot) noexcept 
{
    Transform trs(Vector::Zero(), rot, Vector::One());
    DirectX::XMStoreFloat4x4(&mRenderItem->TexTransform, trs.GetWorldMatrix());
}

void BaseSceneObject::SetTextureScale(Vector scale) noexcept 
{
    Transform trs(Vector::Zero(), Rotator::Zero(), scale);
    DirectX::XMStoreFloat4x4(&mRenderItem->TexTransform, trs.GetWorldMatrix());
}

ERenderLayer& BaseSceneObject::GetRenderLayer() noexcept
{
    return mRenderLayer;
}

void BaseSceneObject::UpdateReflectedMatrix() 
{
    DirectX::XMVECTOR plane = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 75.5f);
    DirectX::XMMATRIX reflectionMatrix = DirectX::XMMatrixReflect(plane);

    DirectX::XMStoreFloat4x4(&mMatrixReflectedObject, mSceneComponent.GetWorldMatrix() * reflectionMatrix);

}

void BaseSceneObject::UpdateShadowMatrix() 
{
    DirectX::XMVECTOR shadowPlane = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);  // xz plane
    auto LightDirection = DirectX::XMFLOAT3{-0.57735f, 0.57735f, 0.57735f};
    DirectX::XMVECTOR toMainLight = DirectX::XMLoadFloat3(&LightDirection);
    DirectX::XMMATRIX S = DirectX::XMMatrixShadow(shadowPlane, toMainLight);
    DirectX::XMMATRIX shadowOffsetY = DirectX::XMMatrixTranslation(0.0f, 0.01f, 0.0f);
    DirectX::XMStoreFloat4x4(&mMatrixShadowObject, mSceneComponent.GetWorldMatrix() * S * shadowOffsetY);
}
