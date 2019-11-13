
#include "irender.h"

class CharRender : public IRender {
public:

    struct CreateConf {
       IntRect outBox = {20, 10};
    };
    CharRender(const CreateConf& conf);

    void render(const World& world) override;

private:
    IntRect outBox;
};