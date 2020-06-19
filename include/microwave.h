#ifndef CEREAL_ADVENTURE_MICROWAVE_H
#define CEREAL_ADVENTURE_MICROWAVE_H

#include "game_object.h"

namespace c_adv {

    class Microwave : public GameObject {
    public:
        Microwave();
        ~Microwave();

        virtual void initialize();

        virtual void render();
        virtual void process();

        // Assets ----
    public:
        static void configureAssets(dbasic::AssetManager *am);

    protected:
        static dbasic::ModelAsset *m_microwaveAsset;
    };

} /* namespace c_adv */

#endif /* CEREAL_ADVENTURE_MICROWAVE_H */

