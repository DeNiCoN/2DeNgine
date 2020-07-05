#include "render/SpriteComponent.hpp"
#include "resource/ShaderResourceLoader.hpp"

namespace DeNgine
{

void SpriteCM::VOnAddedTo(Scene& p_scene)
{
    //Ah shit, we need ShaderResource also...
    p_scene.addToUpdate([](double delta)
    {
        //TODO Update
    });

    p_scene.addToRender([](double delay)
    {
        //TODO Set shader
            //TODO Render

    });
}
}
