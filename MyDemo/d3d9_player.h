#pragma once

#include <cstdint>
#include <d3d9.h>

enum PixFormat {
    I420,
    NV12,
    NV21
};

class D3D9Player {
public:
    D3D9Player();

    ~D3D9Player();

    void Init(uint32_t width, uint32_t height, PixFormat pix_format);

    void CreateRenderWindow();

    void SetWindow(void* handle);

    void Render(uint8_t* data);

    void SetRenderPos(uint32_t x, uint32_t y);

private:
    void InitRender();

    void CreateSurface();

    void DesrtoySurface();

    void Cleanup();

private:
    uint32_t width_{};
    uint32_t height_{};
    PixFormat pix_format_ = I420;

    CRITICAL_SECTION critical_{};
    IDirect3D9* d3d9_{};
    IDirect3DDevice9* d3d9_device_{};
    IDirect3DSurface9* d3d9_surface_{};
    RECT view_rect_{};
    HWND render_window_{};

    uint32_t _renderX{};
    uint32_t _renderY{};
};