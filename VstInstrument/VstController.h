#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
namespace Vst {

    class VstController : public EditController {
    public:
        tresult PLUGIN_API initialize(FUnknown* context);

        static FUnknown* createInstance(void*) { return (IEditController*)new VstController(); }
    };

} }