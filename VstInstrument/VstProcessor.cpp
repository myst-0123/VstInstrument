#include "VstProcessor.h"

#include "VstTagDefine.h"
#include "fuid.h"

namespace Steinberg {
namespace Vst {

    VstProcessor::VstProcessor()
    {
        setControllerClass(ControllerUID);
    }

    tresult PLUGIN_API VstProcessor::initialize(FUnknown* context)
    {
        tresult result = AudioEffect::initialize(context);
        if (result == kResultTrue) {
            addEventInput(STR16("MIDI Input"), 1);
            addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
        
            volume = 0.5f;
        }

        return result;
    }

    tresult PLUGIN_API VstProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
    {
        if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
                return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
    
        return kResultFalse;
    }

    tresult PLUGIN_API VstProcessor::process(ProcessData& data)
    {
        //パラメーター変更の処理
        if (data.inputParameterChanges != NULL) {
            int32 paramChangeCount = data.inputParameterChanges->getParameterCount();
            for (int32 i = 0; i < paramChangeCount; i++) {
                IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);
                if (queue != NULL) {
                    int32 tag = queue->getParameterId();
                    int32 valueChangeCount = queue->getPointCount();
                    ParamValue value;
                    int32 sampleOffset;

                    if (queue->getPoint(valueChangeCount - 1, sampleOffset, value) == kResultTrue) {
                        switch (tag) {
                        case VOLUME_TAG:
                            volume = value;
                            break;
                        }
                    }
                }
            }
        }

        //MIDIの処理
        IEventList* eventList = data.inputEvents;
        if (eventList != NULL) {
            int32 numEvent = eventList->getEventCount();
            for (int32 i = 0; i < numEvent; i++) {
                Event event;
                if (eventList->getEvent(i, event) == kResultOk) {
                    int16 channel;
                    int16 noteNo;
                    int16 velocity;

                    switch (event.type) {
                    case Event::kNoteOnEvent:
                        channel = event.noteOn.channel;
                        noteNo = event.noteOn.pitch;
                        velocity = event.noteOn.velocity;

                        onNoteOn(channel, noteNo, velocity);

                        break;
                    case Event::kNoteOffEvent:
                        channel = event.noteOff.channel;
                        noteNo = event.noteOff.pitch;
                        velocity = event.noteOff.velocity;

                        onNoteOff(channel, noteNo, velocity);

                        break;
                    }
                }
            }
        }

        Sample32* outL = data.outputs[0].channelBuffers32[0];
        Sample32* outR = data.outputs[0].channelBuffers32[1];

        for (int32 i = 0; i < data.numSamples; i++) {
            Sample32 sound = voiceManager.process();
            voiceManager.update();

            outL[i] = sound;
            outR[i] = sound;
        }

        return kResultTrue;
    }

    void VstProcessor::onNoteOn(int channel, int note, float velocity)
    {
        voiceManager.noteOn(channel, note, velocity);
    }

    void VstProcessor::onNoteOff(int channel, int note, float velocity)
    {
        voiceManager.noteOff(note);
    }

} }