#include "GpuResource.h"
#include "cassert"

GpuResource::GpuResource(ID3D12Device* device, UINT width, UINT height, std::wstring name, D3D12_RESOURCE_STATES createState, DXGI_FORMAT format)
{
    mDevice = device;
    mWidth = width;
    mHeight = height;
    mFormat = format;
    mCurrenState = createState;
    mName = std::move(name);

    BuildResource();
}

ID3D12Resource* GpuResource::GetResource()
{
    return mResource.Get();
}

void GpuResource::OnResize(UINT newWidth, UINT newHeight) 
{
    if ((mWidth != newWidth) || (mHeight != newHeight))
    {
        mWidth = newWidth;
        mHeight = newHeight;
        BuildResource();
    }
}

bool GpuResource::ChangeState(ID3D12GraphicsCommandList* cmdList, D3D12_RESOURCE_STATES newState)
{
    if ( newState == mCurrenState)
    {
        assert(0, "the new state is the same as the old state ");
        return false;
    }

    auto ResBar = CD3DX12_RESOURCE_BARRIER::Transition(mResource.Get(), mCurrenState, newState);
    cmdList->ResourceBarrier(1, &ResBar);
    mCurrenState = newState;
    return true;
}

bool GpuResource::ChangeState(ID3D12GraphicsCommandList* cmdList, D3D12_RESOURCE_STATES oldState, D3D12_RESOURCE_STATES newState)
{
    if (oldState != mCurrenState)
    {
        assert(0, "the current state is not equal to the argument of the old state ");
        return false;
    }
    return ChangeState(cmdList, newState);
}

D3D12_RESOURCE_STATES GpuResource::GetCurrentState()
{
    return mCurrenState;
}

void GpuResource::BuildResource()
{
    D3D12_CLEAR_VALUE optimizedClearValue = {};
    optimizedClearValue.Format = mFormat;

    D3D12_RESOURCE_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(D3D12_RESOURCE_DESC));
    texDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    texDesc.Alignment = 0;
    texDesc.Width = mWidth;
    texDesc.Height = mHeight;
    texDesc.DepthOrArraySize = 1;
    texDesc.MipLevels = 1;
    texDesc.Format = mFormat;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    texDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    auto HeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

    mDevice->CreateCommittedResource(&HeapProp, D3D12_HEAP_FLAG_NONE, &texDesc, mCurrenState, &optimizedClearValue, IID_PPV_ARGS(&mResource)) >> Kds::App::Check;

    mResource->SetName(mName.c_str()) >> Kds::App::Check;
}
