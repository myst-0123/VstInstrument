#include "public.sdk/source/main/pluginfactory.h"

#include "fuid.h"
#include "VstProcessor.h"

#define MYVST_SUBCATEGORIES Vst::PlugType::kInstrument

constexpr auto MYVST_VENDOR = "myst0123";
constexpr auto MYVST_URL = "https://twitter.com/myst_0123_";
constexpr auto MYVST_EMAIL = "myst0123@example.com";
constexpr auto MYVST_NAME = "Vst Instrument";
constexpr auto MYVST_VERSION = "0.0.0";

bool InitModule() { return true; }
bool DeinitModule() { return true; }

BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ProcessorUID),
           PClassInfo::kManyInstances,
           kVstAudioEffectClass,
           MYVST_NAME,
           Vst::kDistributable,
           MYVST_SUBCATEGORIES,
           MYVST_VERSION,
           kVstVersionString,
           Steinberg::Vst::VstProcessor::createInstance )

END_FACTORY