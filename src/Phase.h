//
//  Phase.h
//  katamichi001
//
//  Created by hiz on 2014/12/03.
//
//

#ifndef katamichi001_Phase_h
#define katamichi001_Phase_h

class Phase;

// DONE:Sequenceを順番に実行
// TODO:入力処理
// TODO:Sequenceの途中で別Sequenceに移行
// TODO:Sequenceの返値（必要？）
// TODO:Phaseの並列実行
// TODO:Phase間のメッセージング

class Seq {
public:
    Seq(Phase &phase) : _phase(phase){
        setup();
    }
    virtual void setup() {
        _frame = 0;
    }
    virtual bool update() {
        _frame ++;
        return false;
    }
    int    frame() { return _frame;}
    Phase &phase() { return _phase;}
private:
    int    _frame;
    Phase &_phase;
};

class Phase {
public:
    // 指定フレーム数だけウエイトするSeq
    class WaitSeq : public Seq {
    public:
        typedef Seq base;
        
        WaitSeq(Phase &phase, int waitFrame) : Seq(phase) {
            setup(waitFrame);
        }
        virtual void setup(int waitFrame) {
            base::setup();
            this->waitFrame = waitFrame;
        }
        
        virtual bool update() {
            base::update();
            if(frame() >= waitFrame)return true;
            return false;
        }
    private:
        int waitFrame;
    };
    
    // キー入力待ちするSeq
    
    
    Phase() {
        currentSeq  = NULL;
        frameCount = 0;
    }
    ~Phase() {
        for(vector<Seq*>::iterator it=sequences.begin();it!=sequences.end();it++) {
            delete *it;
        }
    }
    virtual bool update() {
        frameCount ++;
        if(currentSeq != NULL) {
            bool finish = currentSeq->update();
            if(finish) {
                int nextSeq = seqIdx + 1;
                if(nextSeq >= sequences.size()) nextSeq = 0;
                setSeqIdx(nextSeq);
            }
        }
        return false;
    }
    virtual void draw() {}
    int getFrameCount() {
        return frameCount;
    }
    void addSequence(Seq *seq) {
        sequences.push_back(seq);
    }
    void setSeqIdx(int idx) {
        seqIdx = idx;
        currentSeq = sequences[idx];
        currentSeq->setup();
    }
//    void setSeq(Seq *seq) {
//        if(this->seq != NULL) delete this->seq;
//        this->seq = seq;
//    }
    Seq *getSeq() {
        return currentSeq;
    }
private:
    int   frameCount;
    vector<Seq*> sequences;
    int   seqIdx;
    Seq  *currentSeq;
};


#endif

