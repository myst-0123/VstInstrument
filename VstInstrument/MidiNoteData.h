namespace Steinberg {
namespace Vst {

    class MidiNoteData {
        int noteNo;
        float theta;
    public:
        MidiNoteData(int note) : noteNo(note), theta(0) { }
    };

} }