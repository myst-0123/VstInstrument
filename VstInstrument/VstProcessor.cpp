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
            noteNoList.clear();
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
            float pitch = 0.0f;

            if (!noteNoList.empty())
                pitch = (440.0f * powf(2.0f, (float)(noteNoList.back() - (69)) / 12.0f));

            Sample32 sound = makeSound(pitch);

            outL[i] = volume * sound;
            outR[i] = volume * sound;
        }

        return kResultTrue;
    }

    void VstProcessor::onNoteOn(int channel, int note, float velocity)
    {
        noteNoList.push_back(note);
        volume = 0.5f;
    }

    void VstProcessor::onNoteOff(int channel, int note, float velocity)
    {
        auto noteNoListItr = find(noteNoList.begin(), noteNoList.end(), note);
        
        if (noteNoListItr != noteNoList.end()) {
            noteNoList.erase(noteNoListItr);
        }

        if (noteNoList.empty()) 
            volume = 0.0f;

    }

    Sample32 VstProcessor::makeSound(float pitch)
    {
        const float PI = 3.1415926f;

        Sample32 madeSound = 0.0f;
        std::vector<float> pitchs{pitch, pitch * 2, pitch * 3, pitch * 4, pitch * 5};
        std::vector<float> env{1.0f, 0.7f, 0.3f, 0.5f, 0.2f};
        static float prePitch = 0;
        static std::vector<float> thetas(pitchs.size(), 0.0f);

        if (pitch != prePitch) {
            thetas.assign(pitchs.size(), 0.0f);
            prePitch = pitch;
        }

        for (int i = 0; i < pitchs.size(); i++) {
            thetas[i] += (2.0f * PI * pitchs[i] / 48000.0f);
            madeSound += env[i] * sin(thetas[i]);
        }

        return madeSound;
    }

} }