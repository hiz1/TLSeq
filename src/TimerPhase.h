//
//  TimerPhase.h
//  katamichi001
//
//  Created by hiz on 2014/12/03.
//
//

#ifndef katamichi001_TimerPhase_h
#define katamichi001_TimerPhase_h

#include "Phase.h"
#include "ofMain.h"



class TimerPhase : public Phase {
    typedef Phase base;
    
public:
    class TimerSeq : public Seq {
    public:
        typedef Seq base;
        
        TimerSeq(Phase &phase, int waitFrame) : Seq(phase) {
            setup(waitFrame);
        }
        
        virtual void setup(int waitFrame) {
            base::setup();
            this->waitFrame = waitFrame;
        }
        
        virtual bool update() {
            base::update();
            TimerPhase &p = (TimerPhase &)phase();
            p.x = ofMap(frame(), 0, waitFrame-1, 0, p.width, true);
            if(frame() >= waitFrame)return true;
            return false;
        }
    private:
        int waitFrame;
    };
    
    TimerPhase() : Phase() {
    }
    
    TimerPhase(ofVec2f pos, int width, int frameLength) : Phase() {
        this->pos = pos;
        this->width = width;
        this->frameLength = frameLength;
        this->addSequence(new TimerSeq(*this, frameLength));
        this->addSequence(new WaitSeq(*this, 60));
        this->addSequence(new TimerSeq(*this, frameLength*2));
        this->setSeqIdx(0);
        this->x  = 0;
        
    }
    virtual bool update() {
        return base::update();
    }
    virtual void draw() {
        ofSetColor(122);
        ofLine(pos, pos + ofVec2f(width, 0));
        ofVec2f cpos = pos + ofVec2f(x, 0);
        ofCircle(cpos.x, cpos.y, 10);
    }
private:
    ofVec2f pos;
    int    x;
    int    width;
    int    frameLength;
//    Sequence<TimerPhase> *seq;
};

#endif
