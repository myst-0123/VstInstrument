#include "VstController.h"
#include "VstTagDefine.h"

namespace Steinberg {
namespace Vst {

    tresult PLUGIN_API VstController::initialize(FUnknown* context)
    {
        tresult result = EditController::initialize(context);
        if (result == kResultTrue) {
            parameters.addParameter(STR16("Volume"), STR16("%"), 0, 100, ParameterInfo::kCanAutomate, VOLUME_TAG);
            parameters.addParameter(STR16("Attack"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, ATTACK_TAG);
            parameters.addParameter(STR16("Decay"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, DECAY_TAG);
            parameters.addParameter(STR16("Sustain"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, SUSTAIN_TAG);
            parameters.addParameter(STR16("Release"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, RELEASE_TAG);
        }

        return kResultTrue;
    }

} }
