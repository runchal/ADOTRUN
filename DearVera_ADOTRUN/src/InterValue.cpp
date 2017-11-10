//
//  InterValue.cpp
//  DearVera_ADOTRUN
//
//  Created by Adolfo Rodriguez on 2017-11-10.
//

#include <math.h>
#include "InterValue.h"

void InterValue::setTarget(float t) {
    this->target = t;
    this->hasTarget = true;
}

void InterValue::approachTarget() {
    if (!this->hasTarget) { return; }
    if (!this->hasValues) {
        this->current = this->target;
        this->previous = this->target;
        this->hasValues = true;
        return;
    }
    float movement = this->multiplier * ((this->target - this->current) * (1 - this->resistanceWeight) + (this->current - this->previous) * this->resistanceWeight);
    float fmov = fabs(movement);
    if (fmov > this->maxChange) { movement *= this->maxChange / fmov; }
    this->previous = current;
    this->current += movement;
}
