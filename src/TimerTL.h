//
//  TimerTL.h
//  katamichi001
//
//  Created by hiz on 2014/12/03.
//
//

#ifndef katamichi001_TimerTL_h
#define katamichi001_TimerTL_h

#include "Timeline.h"
#include "ofMain.h"



class TimerTL : public Timeline {
    typedef Timeline base;
    
public:
    class TimerSeq : public Seq {
    public:
        typedef Seq base;
        
        TimerSeq(Timeline &phase, int waitFrame) : Seq(phase) {
            setup(waitFrame);
        }
        
        virtual void setup(int waitFrame) {
            base::setup();
            this->waitFrame = waitFrame;
        }
        
        virtual bool update() {
            base::update();
            TimerTL &t = (TimerTL &)tl();
            t.x = ofMap(frame(), 0, waitFrame-1, 0, t.width, true);
            if(frame() >= waitFrame)return true;
            return false;
        }
    private:
        int waitFrame;
    };
    
    TimerTL() : Timeline() {
    }
    
    TimerTL(ofVec2f pos, int width, int frameLength) : Timeline() {
        this->pos = pos;
        this->width = width;
        this->frameLength = frameLength;
        
        vector<int> keys;
        keys.push_back('z');
        keys.push_back('Z');
        
        this->addSequence(new TimerSeq(*this, frameLength));
        this->addSequence(new InputSeq(*this, keys, -1));
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
//    Sequence<TimerTL> *seq;
};

#endif
