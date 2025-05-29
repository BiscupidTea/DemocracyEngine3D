#pragma once
#include <vector>
#include <string>
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"

namespace DemoEngine_Renderer
{
    struct DirLight
    {
        glm::vec3 direction;
        glm::vec3 color;
    };

    struct PointLight
    {
        glm::vec3 position;
        glm::vec3 color;
    };

    struct SpotLight
    {
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 color;
        float cutOff;
        float outerCutOff;
    };

    class LightManager {
    public:
        std::vector<DirLight> directionalLights;
        std::vector<PointLight> pointLights;
        std::vector<SpotLight> spotLights;

        void UploadToShader(Shader* shader);
    };
}
