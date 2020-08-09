#include "VstProcessor.h"

namespace Steinberg {
namespace Vst {

    VstProcessor::VstProcessor()
    {

    }

    tresult PLUGIN_API VstProcessor::initialize(FUnknown* context)
    {
        tresult result = AudioEffect::initialize(context);
        if (result == kResultTrue) {
            addEventInput(STR16("MIDI Input"), 1);
            addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);
        
            pitchList.clear();
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

            if (!pitchList.empty())
                pitch = pitchList.back();


            outL[i] = makeSound(pitch);
            outR[i] = makeSound(pitch);
        }

        return kResultTrue;
    }

    void VstProcessor::onNoteOn(int channel, int note, float velocity)
    {
        float pitch = (440.0f * powf(2.0f, (float)(note - (69)) / 12.0f));
        pitchList.push_back(pitch);
    }

    void VstProcessor::onNoteOff(int channel, int note, float velocity)
    {
        float pitch = (440.0f * powf(2.0f, (float)(note - (69)) / 12.0f));

        auto pitchListItr = find(pitchList.begin(), pitchList.end(), pitch);
        
        if (pitchListItr != pitchList.end()) {
            pitchList.erase(pitchListItr);
        }

    }

    Sample32 VstProcessor::makeSound(float pitch)
    {

    }

} }