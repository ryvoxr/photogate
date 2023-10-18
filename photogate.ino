#define SIGNAL 4
#define MAXLEN 100
#define BLOCKERWIDTH 0.01

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
    pinMode(SIGNAL, INPUT);
    state.gate = OPEN;
}

void loop() {
    updatestate();
    if (state.gate != state.lastgate)
        state.gate == BLOCKED ? gateblocked() : gateopen();
    delay(10);
}

void gateblocked() {
    state.starttime = millis();
}

void gateopen() {
    unsigned long duration = millis() - state.starttime;
    Serial.println(duration);
}

/* updatestate: update the program state with board state */
void updatestate() {
    state.lastgate = state.gate;
    if (digitalRead(SIGNAL))
        state.gate = OPEN;
    else
        state.gate = BLOCKED;
}

