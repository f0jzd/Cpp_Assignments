//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "RenderTexture.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    void PostProcess();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    std::unique_ptr<DirectX::BasicEffect> basicEffect;

    std::unique_ptr<DirectX::CommonStates> m_states;
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
    std::unique_ptr<DirectX::GeometricPrimitive> m_shape;

    DirectX::GeometricPrimitive::VertexCollection vertices;
    DirectX::GeometricPrimitive::IndexCollection indices;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;

    DirectX::SimpleMath::Matrix m_world;
    DirectX::SimpleMath::Matrix m_view;
    DirectX::SimpleMath::Matrix m_projection;

    RECT m_fullscreenRect;

    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_bloomExtractPS;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_bloomCombinePS;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_gaussianBlurPS;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_blackWhitePS;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> m_chromAbberation;

    Microsoft::WRL::ComPtr<ID3D11Buffer> m_blackWhiteParam;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_bloomParams;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_blurParamsWidth;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_blurParamsHeight;
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_chromAbberationParam;

    std::unique_ptr<DX::RenderTexture> m_offscreenTexture;
    std::unique_ptr<DX::RenderTexture> m_renderTarget1;
    std::unique_ptr<DX::RenderTexture> m_renderTarget2;

    RECT m_bloomRect;


    CD3D11_BUFFER_DESC cbDesc;

    ID3D11Buffer* constBuffer;

    
};
