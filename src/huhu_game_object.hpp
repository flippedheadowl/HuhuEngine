#pragma once

#include "huhu_model.hpp"

// libs
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>
#include <unordered_map>

namespace huhu
{
    struct TransformComponent
    {
        glm::vec3 translation{}; // (position offset)
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation;

        // Matrix corresponds to translate * Ry * Rx * Rz * scale transform
        // Rotation order uses Tait-Bryan angles with axis order Y(1), X(2), Y(3)
        // https:/en/wikipedia.org/wiki/Euler_angles#Rotation_matrix
        glm::mat4 mat4();
        glm::mat3 normalMatrix();
    };

    class HuhuGameObject
    {
    public:
        using id_t = unsigned int;
        using Map = std::unordered_map<id_t, HuhuGameObject>;

        static HuhuGameObject createGameObject()
        {
            static id_t currentId = 0;
            return HuhuGameObject(currentId++);
        }

        HuhuGameObject(const HuhuGameObject &) = delete;
        HuhuGameObject &operator=(const HuhuGameObject &) = delete;
        HuhuGameObject(HuhuGameObject &&) = default;
        HuhuGameObject &operator=(HuhuGameObject &&) = default;

        const id_t getId() { return id; };

        std::shared_ptr<HuhuModel> model{};
        glm::vec3 color{};
        TransformComponent transform{};

    private:
        HuhuGameObject(id_t objId) : id{objId} {};

        id_t id;
    };
}