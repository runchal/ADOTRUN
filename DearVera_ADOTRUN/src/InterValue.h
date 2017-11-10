//
//  InterValue.h
//  DearVera_ADOTRUN
//
//  Created by Adolfo Rodriguez on 2017-11-10.
//


class InterValue {
public:
    float current;
    float previous;
    float target = 0;
    bool hasTarget = false;
    bool hasValues = false;
    void setTarget(float target);
    void approachTarget();
    
    float maxChange;
    float resistanceWeight;
    float multiplier;
    
    InterValue(float maxChange, float multiplier, float resistanceWeight): maxChange(maxChange), multiplier(multiplier), resistanceWeight(resistanceWeight) { }
};
