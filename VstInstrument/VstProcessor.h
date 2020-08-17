#include <vector>

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "VoiceManager.h"

namespace Steinberg {
namespace Vst {

    class VstProcessor : public AudioEffect {
    private:
        VoiceManager voiceManager;
        ParamValue volume;
    public:
        VstProcessor();

        tresult PLUGIN_API initialize(FUnknown* context);

        tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

        tresult PLUGIN_API process(ProcessData& data);

        virtual void onNoteOn(int channel, int note, float velocity);

        virtual void onNoteOff(int channel, int note, float velocity);

        static FUnknown* createInstance(void*) { return (IAudioProcessor*)new VstProcessor(); }
    };

} }