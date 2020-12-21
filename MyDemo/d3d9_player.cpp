#include "d3d9_player.h"

#include <iostream>

#pragma comment(lib, "d3d9.lib")

D3D9Player::D3D9Player() {

}

D3D9Player::~D3D9Player() {
    DesrtoySurface();
    Cleanup();
}

void D3D9Player::Init(uint32_t width, uint32_t height, PixFormat pix_format) {
    width_ = width;
    height_ = height;
    pix_format_ = pix_format;

    view_rect_.left = 0;
    view_rect_.top = 0;
    view_rect_.right = width;
    view_rect_.bottom = height;
}

void D3D9Player::CreateRenderWindow() {

}

void D3D9Player::SetWindow(void* handle) {
    render_window_ = (HWND)(handle);
    InitRender();
    CreateSurface();
}

void D3D9Player::Render(uint8_t* data) {
    D3DLOCKED_RECT d3d_rect;
    if (d3d9_surface_ == nullptr) {
        return;
    }
    auto hr = d3d9_surface_->LockRect(&d3d_rect, NULL, D3DLOCK_DONOTWAIT);
    if (FAILED(hr)) {
        std::cout << "lock rect error" << std::endl;
        return;
    }

    int y_stride = d3d_rect.Pitch;
    int v_stride = y_stride / 2;
    int u_stride = y_stride / 2;

    uint8_t* y_dest = (uint8_t*)d3d_rect.pBits;
    uint8_t* v_dest = y_dest + height_ * y_stride;
    uint8_t* u_dest = v_dest + height_ / 2 * v_stride;

    for (uint32_t i = 0; i < height_; i++) {
        memcpy(y_dest + i * y_stride, data + i * width_, width_);
    }

    for (uint32_t i = 0; i < height_ / 2; i++) {
        memcpy(v_dest + i * v_stride, data + width_ * height_ + i * width_ / 2,
            width_ / 2);
    }

    for (uint32_t i = 0; i < height_ / 2; i++) {
        memcpy(u_dest + i * u_stride, data + width_ * height_ * 5 / 4 + i * width_ / 2,
            width_ / 2);
    }

    hr = d3d9_surface_->UnlockRect();
    if (FAILED(hr)) {
        std::cout << "unlock rect error" << std::endl;
        return;
    }
    d3d9_device_->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0),
        1.0f, 0);
    d3d9_device_->BeginScene();

    IDirect3DSurface9* d3d_surface = NULL;
    d3d9_device_->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
        &d3d_surface);

    d3d9_device_->StretchRect(d3d9_surface_, NULL, d3d_surface, &view_rect_,
        D3DTEXF_LINEAR);
    d3d9_device_->EndScene();
    // RECT rect{ _renderX, _renderY, _renderX + 480, _renderY + 272 };
    d3d9_device_->Present(NULL, NULL, NULL, NULL);
    d3d_surface->Release();
}

void D3D9Player::SetRenderPos(uint32_t x, uint32_t y)
{
    _renderX = x;
    _renderY = y;
}

void D3D9Player::InitRender() {
    std::cout << "init render" << std::endl;
    InitializeCriticalSection(&critical_);
    Cleanup();

    d3d9_ = Direct3DCreate9(D3D_SDK_VERSION);
    if (d3d9_ == nullptr) {
        return;
    }

    /*RECT r;
    GetClientRect(render_window_, &r);
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);*/

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.hDeviceWindow = (HWND)render_window_;
    d3dpp.Flags = D3DPRESENTFLAG_VIDEO;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferWidth = width_;
    d3dpp.BackBufferHeight = height_;

    HRESULT hr = d3d9_->CreateDevice(
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, render_window_,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3d9_device_);
}

void D3D9Player::Cleanup() {
    EnterCriticalSection(&critical_);
    if (d3d9_surface_) {
        d3d9_surface_->Release();
        d3d9_surface_ = nullptr;
    }
    if (d3d9_device_) {
        d3d9_device_->Release();
        d3d9_device_ = nullptr;
    }
    if (d3d9_) {
        d3d9_->Release();
        d3d9_ = nullptr;
    }
    LeaveCriticalSection(&critical_);
}

void D3D9Player::CreateSurface() {
    if (d3d9_device_ == nullptr) {
        return;
    }
    HRESULT hr = d3d9_device_->CreateOffscreenPlainSurface(
        width_, height_, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'),
        D3DPOOL_DEFAULT, &d3d9_surface_, NULL);
    if (FAILED(hr)) {
        std::cout << "create plain surface error" << std::endl;
        return;
    }
    std::cout << "create surface" << std::endl;
}

void D3D9Player::DesrtoySurface() {
    EnterCriticalSection(&critical_);
    if (d3d9_surface_) {
        d3d9_surface_->Release();
        d3d9_surface_ = nullptr;
    }
    LeaveCriticalSection(&critical_);
}