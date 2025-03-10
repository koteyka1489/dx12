#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <directx/d3dx12.h>
#include "GraphicError.h"
#include "string"

class GpuResource
{
    ID3D12Device* mDevice = nullptr;
    UINT mWidth = 0;
    UINT mHeight = 0;
    std::wstring mName;
    D3D12_RESOURCE_STATES mCurrenState = D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON;
    DXGI_FORMAT mFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

    Microsoft::WRL::ComPtr<ID3D12Resource> mResource = nullptr;

public:
    GpuResource(ID3D12Device* device, UINT width, UINT height, std::wstring name, D3D12_RESOURCE_STATES createState = D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_COMMON,
        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);
    GpuResource(const GpuResource& rhs) = delete;
    GpuResource& operator=(const GpuResource& rhs) = delete;
    ~GpuResource() = default;

    ID3D12Resource* GetResource();
    void OnResize(UINT newWidth, UINT newHeight);
    bool ChangeState(ID3D12GraphicsCommandList* cmdList, D3D12_RESOURCE_STATES newState);
    bool ChangeState(ID3D12GraphicsCommandList* cmdList, D3D12_RESOURCE_STATES oldState, D3D12_RESOURCE_STATES newState);

    D3D12_RESOURCE_STATES GetCurrentState();

private:
    void BuildResource();
};