enum DetectorState{ACTIVE, INACTIVE};
enum DetectorState eReadDetector(void);
void ServoGoTo(unsigned int uiPosition);
void ServoShift(unsigned int uiStep);
void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
