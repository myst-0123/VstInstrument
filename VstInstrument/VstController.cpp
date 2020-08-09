#include "VstController.h"
#include "VstTagDefine.h"

namespace Steinberg {
namespace Vst {

    tresult PLUGIN_API VstController::initialize(FUnknown* context)
    {
        tresult result = EditController::initialize(context);
        if (result == kResultTrue) {
            parameters.addParameter(STR16("Volume"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, VOLUME_TAG);
        }
    }

} }