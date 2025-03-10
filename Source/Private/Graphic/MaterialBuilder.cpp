#include "MaterialBuilder.h"
#include "DirectXColors.h"
#include <vector>

std::unordered_map<EMaterialType, std::unique_ptr<Material>> MaterialBuilder::CreateMaterials()
{
    using namespace DirectX;

    std::vector<MaterialInfo> materialsInfo{};

    MaterialInfo grassInfo{.Type = EMaterialType::GRASS,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.01f, 0.01f, 0.01f),
        .Roughness = 0.5f};
    materialsInfo.push_back(grassInfo);

    MaterialInfo grassxInfo{.Type = EMaterialType::GRASSX,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.01f, 0.01f, 0.01f),
        .Roughness = 0.5f};
    materialsInfo.push_back(grassxInfo);

        MaterialInfo grassyInfo{.Type = EMaterialType::GRASSY,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.01f, 0.01f, 0.01f),
        .Roughness = 0.5f};
    materialsInfo.push_back(grassyInfo);

    MaterialInfo waterInfo{.Type = EMaterialType::WATER,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.6f),
        .Fresnel = XMFLOAT3(0.1f, 0.1f, 0.1f),
        .Roughness = 0.0f};
    materialsInfo.push_back(waterInfo);

    MaterialInfo bricksInfo{.Type = EMaterialType::BRICKS,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.02f, 0.02f, 0.02f),
        .Roughness = 0.5f};
    materialsInfo.push_back(bricksInfo);

    MaterialInfo stoneInfo{.Type = EMaterialType::STONE,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.05f, 0.05f, 0.05f),
        .Roughness = 0.3f};
    materialsInfo.push_back(stoneInfo);

        MaterialInfo tileInfo{.Type = EMaterialType::TILE,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.02f, 0.02f, 0.02f),
        .Roughness = 0.2f};
    materialsInfo.push_back(tileInfo);

         MaterialInfo skullInfo{.Type = EMaterialType::SKULLMAT,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.05f, 0.05f, 0.05),
        .Roughness = 0.3f};
    materialsInfo.push_back(skullInfo);


     MaterialInfo fireball{.Type = EMaterialType::FIREBALL,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.05f, 0.05f, 0.05),
        .Roughness = 0.3f};
    materialsInfo.push_back(fireball);

    MaterialInfo coldfire{.Type = EMaterialType::COLDFIRE,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.05f, 0.05f, 0.05),
        .Roughness = 0.3f};
    materialsInfo.push_back(coldfire);

    MaterialInfo metall{.Type = EMaterialType::METALL,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.05f, 0.05f, 0.05),
        .Roughness = 0.3f};
    materialsInfo.push_back(metall);

    MaterialInfo droneBaseColor{.Type = EMaterialType::DRONEBASECOLOR,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.05f, 0.05f, 0.05),
        .Roughness = 0.3f};
    materialsInfo.push_back(droneBaseColor);

     MaterialInfo wireFence{.Type = EMaterialType::WIREFENCE,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        .Fresnel = XMFLOAT3(0.05f, 0.05f, 0.05),
        .Roughness = 0.3f};
    materialsInfo.push_back(wireFence);

    MaterialInfo mirror{.Type = EMaterialType::MIRROR,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.3f),
        .Fresnel = XMFLOAT3(0.1f, 0.1f, 0.1),
        .Roughness = 0.5f};
    materialsInfo.push_back(mirror);

        MaterialInfo shadow{.Type = EMaterialType::SHADOW,
        .DiffuseAlbedo = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f),
        .Fresnel = XMFLOAT3(0.001f, 0.001f, 0.001),
        .Roughness = 0.0f};
    materialsInfo.push_back(shadow);

          MaterialInfo three{.Type = EMaterialType::TREES,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.f),
        .Fresnel = XMFLOAT3(0.01f, 0.01f, 0.01),
        .Roughness = 0.125f};
    materialsInfo.push_back(three);

      // RED
    MaterialInfo redMaterial{.Type = EMaterialType::RED,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(redMaterial);

    // GREEN
    MaterialInfo greenMaterial{.Type = EMaterialType::GREEN,
        .DiffuseAlbedo = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(greenMaterial);

    // BLUE
    MaterialInfo blueMaterial{.Type = EMaterialType::BLUE,
        .DiffuseAlbedo = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(blueMaterial);

    // YELLOW
    MaterialInfo yellowMaterial{.Type = EMaterialType::YELLOW,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(yellowMaterial);

    // PURPLE
    MaterialInfo purpleMaterial{.Type = EMaterialType::PURPLE,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(purpleMaterial);

   // CYAN
    MaterialInfo cyanMaterial{.Type = EMaterialType::CYAN,
        .DiffuseAlbedo = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(cyanMaterial);

    // ORANGE
    MaterialInfo orangeMaterial{.Type = EMaterialType::ORANGE,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 0.5f, 0.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(orangeMaterial);

    // PINK
    MaterialInfo pinkMaterial{.Type = EMaterialType::PINK,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 0.0f, 0.5f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(pinkMaterial);

    // GRAY
    MaterialInfo grayMaterial{.Type = EMaterialType::GRAY,
        .DiffuseAlbedo = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(grayMaterial);

    // WHITE
    MaterialInfo whiteMaterial{.Type = EMaterialType::WHITE,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.f),
        .Fresnel = XMFLOAT3(0.0001f, 0.0001f, 0.0001f),
        .Roughness = 0.001f};
    materialsInfo.push_back(whiteMaterial);

    //SKYBOX
    MaterialInfo skyBox{.Type = EMaterialType::SKYBOX,
        .DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.f),
        .Fresnel = XMFLOAT3(0.1f, 0.1f, 0.1f),
        .Roughness = 1.0f};
    materialsInfo.push_back(skyBox);



    std::unordered_map<EMaterialType, std::unique_ptr<Material>> result{};

    for (const auto& matInfo : materialsInfo)
    {

        if (result.contains(matInfo.Type))
        {
            assert(false); // material type allready on container
            continue;
        }
        result[matInfo.Type] = MakeMaterial(matInfo);

        ++mCurrentMatCBIndex;
    }

    return result;
}

std::unique_ptr<Material> MaterialBuilder::MakeMaterial(const MaterialInfo& matInfo)
{
    std::unique_ptr<Material> result = std::make_unique<Material>();
    result->Type = matInfo.Type;
    result->DiffuseAlbedo = matInfo.DiffuseAlbedo;
    result->FresnelR0 = matInfo.Fresnel;
    result->Roughness = matInfo.Roughness;
    result->MatCBIndex = mCurrentMatCBIndex;
    return result;
}
