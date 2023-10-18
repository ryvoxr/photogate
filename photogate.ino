#define MAXLEN 100
#define BLOCKERWIDTH 0.007

enum {
    GATEOUT = 3,
    SIGNAL = 4,
    VCC = 12,
    GATE = 13,
} Pins;

typedef enum GateState {
    BLOCKED,
    OPEN,
} GateState;

struct {
    int num;
    GateState gate;
    GateState lastgate;
    unsigned long starttime;
} state;

void setup() {
    Serial.begin(9600);
    pinMode(GATE, INPUT);
    pinMode(VCC, OUTPUT);
    pinMode(GATEOUT, OUTPUT);
    pinMode(SIGNAL, INPUT);
    state.gate = OPEN;
    digitalWrite(VCC, HIGH);
}

void loop() {
    digitalWrite(GATEOUT, digitalRead(GATE));
    updatestate();
    if (state.gate != state.lastgate)
        state.gate == BLOCKED ? gateblocked() : gateopen();
}

void gateblocked() {
    state.starttime = millis();
}

void gateopen() {
    unsigned long duration = millis() - state.starttime;
    Serial.println(BLOCKERWIDTH / (duration / 1000.0));
}

/* updatestate: update the program state with board state */
void updatestate() {
    state.lastgate = state.gate;
    if (digitalRead(SIGNAL))
        state.gate = OPEN;
    else
        state.gate = BLOCKED;
}

