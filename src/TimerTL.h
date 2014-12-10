//
//  TimerTL.h
//  katamichi001
//
//  Created by hiz on 2014/12/03.
//
//

#ifndef katamichi001_TimerTL_h
#define katamichi001_TimerTL_h

#include "TL.h"
#include "ofMain.h"



class TimerTL : public TL {
    typedef TL base;
    
public:
    class TimerSeq : public Seq {
    public:
        typedef Seq base;
        
        TimerSeq(TL &phase, string seqId, int waitFrame) : Seq(phase, seqId) {
            setup(NULL);
            this->waitFrame = waitFrame;
        }
        
        virtual void setup(const ofParameterGroup *parm) {
            base::setup(parm);
        }
        
        virtual bool update(ofParameterGroup *parm) {
            base::update(parm);
            TimerTL &t = (TimerTL &)tl();
            t.x = ofMap(frame(), 0, waitFrame-1, 0, t.width, true);
            if(frame() >= waitFrame)return new string("");
            return NULL;
        }
    private:
        int waitFrame;
    };
    
    TimerTL() : TL() {
    }
    
    TimerTL(ofVec2f pos, int width, int frameLength) : TL() {
        this->pos = pos;
        this->width = width;
        this->frameLength = frameLength;
        
        vector<int> keys;
        keys.push_back('z');
        keys.push_back('Z');
        
        
        this->addSequence(new TimerSeq(*this, "move1", frameLength));
        this->addSequence(new InputSeq(*this, "input", keys, 60));
        this->addSequence(new TimerSeq(*this, "move2", frameLength*2));
        this->setSeqIdx(0, NULL);
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
    virtual int getNextSeqIdx(Seq *seq, ofParameterGroup *parm) {
        if(instanceof<InputSeq>(seq)) {
            if(parm != NULL && parm->contains("key")) {
                int key = parm->get<int>("key");
                if('z' == key || 'Z' == key) return getSeqIdxWithId("move1");
            }
        }
        return base::getNextSeqIdx(seq, parm);
    }
private:
    ofVec2f pos;
    int    x;
    int    width;
    int    frameLength;
//    Sequence<TimerTL> *seq;
};

#endif
