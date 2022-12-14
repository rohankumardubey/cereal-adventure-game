#ifndef CEREAL_ADVENTURE_SHADER_CONTROLS_H
#define CEREAL_ADVENTURE_SHADER_CONTROLS_H

#include "delta.h"

namespace c_adv {

    struct ShadowMapScreenVariables {
        ysMatrix CameraView = ysMath::Constants::Identity;
        ysMatrix Projection = ysMath::Constants::Identity;
    };

    struct AllShadowMapScreenVariables {
        ShadowMapScreenVariables ScreenVariables[8];
    };

    struct ShadowMapObjectVariables {
        ysMatrix Transform = ysMath::Constants::Identity;
        float Scale[4] = { 1.0f, 1.0f, 1.0f };
    };

    struct ShaderObjectVariables {
        ysMatrix Transform = ysMath::Constants::Identity;

        float TexOffset[2] = { 0.0f, 0.0f };
        float TexScale[2] = { 1.0f, 1.0f };
        float Scale[4] = { 1.0f, 1.0f, 1.0f };

        ysVector4 BaseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        ysVector4 Emission = { 0.0f, 0.0f, 0.0f, 0.0f };
        float SpecularMix = 1.0f;
        float DiffuseMix = 1.0f;
        float Metallic = 0.0f;
        float DiffuseRoughness = 0.5f;
        float SpecularPower = 4.0f;
        float IncidentSpecular = 1.0f;
        float FogEffect = 1.0f;

        int ColorReplace = 0;
        int AoMap = 0;
        int Lit = 1;

        int Padding[2];
    };

    struct ShaderScreenVariables {
        ysMatrix CameraView = ysMath::Constants::Identity;
        ysMatrix Projection = ysMath::Constants::Identity;

        ysMatrix Shadow0CameraView = ysMath::Constants::Identity;
        ysMatrix Shadow0Projection = ysMath::Constants::Identity;

        ysVector4 Eye = { 0.0f, 0.0f, 0.0f };

        ysVector4 FogColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        float FogNear = 10.0f;
        float FogFar = 100.0f;

        float AmbientDiffuseAmount = 1.0f;
        float AmbientSpecularAmount = 1.0f;
        float SsaoAmount = 1.0f;
        float BakedAoAmount = 1.0f;
        float DiffuseAmount = 1.0f;
        float SpecularAmount = 1.0f;
        float ShadowAmount = 1.0f;
        float DebugSsao = 0.0f;
        float DebugBloom = 0.0f;

        int Padding[2];
    };

    struct Light {
        ysVector4 Position = { 0.0f, 0.0f, 0.0f, 1.0f };
        ysVector4 Color = { 0.0f, 0.0f, 0.0f, 1.0f };
        ysVector4 Direction = { 0.0f, 0.0f, -1.0f, 1.0f };
        float Attenuation0 = -1.0f;
        float Attenuation1 = 0.0f;
        float FalloffStart = 0.0f;
        float FalloffScale = 1.0f;
        int FalloffEnabled = 1;
        int Active = 0;
        int ShadowMap = -1;
        
        int Padding[1];
    };

    struct LightingControls {
        static constexpr int MaxLights = 32;

        Light Lights[MaxLights];
        ysVector4 AmbientLighting;
    };
    
    struct SsaoControls {
        static constexpr int MaxKernelSize = 128;

        ysMatrix Projection;
        ysVector4 Kernel[MaxKernelSize];
        float SampleRadius;
    };

    struct BlurControls {
        int Horizontal;
        int Padding[3];
    };

    struct BloomControls {
        float BloomAmount = 1.0f;
        float DitherAmount = 1.0f;
        float DebugBlackAndWhite = 0.0f;
    };

} /* namespace c_adv */

#endif /* CEREAL_ADVENTURE_SHADER_CONTROLS_H */
