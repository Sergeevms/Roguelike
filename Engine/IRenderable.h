#pragma once
#include "EngineAPI.h"
namespace MaxrEngine {
class IRenderable {
   public:
    ENGINE_API explicit IRenderable(const int layer = 0);
    virtual ~IRenderable() = default;
    virtual void Render() = 0;

    ENGINE_API const int& GetLayer() const;
    ENGINE_API void SetLayer(const int newLayer);

   protected:
    int layer;
};
}  // namespace MaxrEngine
