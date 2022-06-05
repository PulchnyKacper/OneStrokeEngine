#pragma once
#include "ose_model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace ose {

    struct TransformComponent {
        glm::vec3 translation{};
        glm::vec3 scale{ 1.f, 1.f, 1.f };
        glm::vec3 rotation{};
        glm::mat4 mat4() {
            const float c3 = glm::cos(rotation.z);
            const float s3 = glm::sin(rotation.z);
            const float c2 = glm::cos(rotation.x);
            const float s2 = glm::sin(rotation.x);
            const float c1 = glm::cos(rotation.y);
            const float s1 = glm::sin(rotation.y);
            return glm::mat4{
                {
                    scale.x * (c1 * c3 + s1 * s2 * s3),
                    scale.x * (c2 * s3),
                    scale.x * (c1 * s2 * s3 - c3 * s1),
                    0.0f,
                },
                {
                    scale.y * (c3 * s1 * s2 - c1 * s3),
                    scale.y * (c2 * c3),
                    scale.y * (c1 * c3 * s2 + s1 * s3),
                    0.0f,
                },
                {
                    scale.z * (c2 * s1),
                    scale.z * (-s2),
                    scale.z * (c1 * c2),
                    0.0f,
                },
                {translation.x, translation.y, translation.z, 1.0f} };
        }
    };

    class OseGameObject {
    public:
        using id_t = unsigned int;

        static OseGameObject createGameObject() {
            static id_t currentId = 0;
            return OseGameObject{ currentId++ };
        }

        OseGameObject(const OseGameObject&) = delete;
        OseGameObject& operator=(const OseGameObject&) = delete;
        OseGameObject(OseGameObject&&) = default;
        OseGameObject& operator=(OseGameObject&&) = default;

        id_t getId() { return id; }

        std::shared_ptr<OseModel> model{};
        glm::vec3 color{};
        TransformComponent transform{};

    private:
        OseGameObject(id_t objId) : id{ objId } {}

        id_t id;
    };
}