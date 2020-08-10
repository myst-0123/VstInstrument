#include "MidiNoteData.h"

namespace Steinberg {
namespace Vst {

    bool MidiNoteData::operator==(const MidiNoteData& rhs) const
    {
        return noteNo == rhs.noteNo;
    }

} }