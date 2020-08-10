namespace Steinberg {
namespace Vst {

    class MidiNoteData {
    public:
        int noteNo;
        float theta;

        MidiNoteData(int note) : noteNo(note), theta(0) { }

        bool operator==(const MidiNoteData& rhs) const;
    };

} }