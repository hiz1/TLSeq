//
//  Timeline.h
//  katamichi001
//
//  Created by hiz on 2014/12/03.
//
//

#ifndef katamichi001_Timeline_h
#define katamichi001_Timeline_h

class Timeline;

// DONE:Sequenceを順番に実行
// TODO:入力処理
// TODO:Sequenceの途中で別Sequenceに移行
// TODO:Timelineの並列実行
// TODO:Timeline間のメッセージング
// TODO:Sequenceの返値（必要？）
// TODO:Sequenceの親子関係（必要？）

class Seq {
public:
    Seq(Timeline &tl) : _tl(tl){
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
    Timeline &tl() { return _tl;}
    virtual void keyPressed(int key) {}
    virtual void keyReleased(int key) {}
    virtual void mouseMoved(int x, int y ) {}
    virtual void mouseDragged(int x, int y, int button) {}
    virtual void mousePressed(int x, int y, int button) {}
    virtual void mouseReleased(int x, int y, int button) {}
    virtual void gotMessage(ofMessage msg) {}
private:
    int    _frame;
    Timeline &_tl;
};

class Timeline {
public:
    // 指定フレーム数だけウエイトするSeq
    class WaitSeq : public Seq {
    public:
        typedef Seq base;
        
        WaitSeq(Timeline &phase, int waitFrame)
        : Seq(phase), waitFrame(waitFrame) {}
        
        virtual bool update() {
            base::update();
            if(frame() >= waitFrame)return true;
            return false;
        }
    private:
        const int waitFrame;
    };
    
    // キー入力待ちするSeq
    class InputSeq : public Seq {
    public:
        typedef Seq base;
        
        InputSeq(Timeline &phase, vector<int> acceptKeys, int waitFrame = -1)
        : Seq(phase),acceptKeys(acceptKeys), waitFrame(waitFrame) {}
        
        virtual void setup() {
            base::setup();
            inputed = false;
        }
        
        virtual bool update() {
            base::update();
            if(inputed) return true;
            if(waitFrame >= 0 && frame() >= waitFrame)return true;
            return false;
        }
        
        virtual void keyPressed(int key) {
            vector< int >::iterator cIter = find( acceptKeys.begin(),acceptKeys.end() , key );
            if(cIter != acceptKeys.end()) inputed = true;
        }
    private:
        int waitFrame;
        vector<int> acceptKeys;
        bool inputed;
    };
    
    Timeline() {
        currentSeq  = NULL;
        frameCount = 0;
        
        
    }
    ~Timeline() {
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
    Seq *getSeq() {
        return currentSeq;
    }
    virtual void keyPressed(int key) {
        currentSeq->keyPressed(key);
    }
    virtual void keyReleased(int key) {
        currentSeq->keyReleased(key);
    }
    virtual void mouseMoved(int x, int y ) {
        currentSeq->mouseMoved(x, y);
    }
    virtual void mouseDragged(int x, int y, int button) {
        currentSeq->mouseDragged(x,y,button);
    }
    virtual void mousePressed(int x, int y, int button) {
        currentSeq->mousePressed(x,y,button);
    }
    virtual void mouseReleased(int x, int y, int button) {
        currentSeq->mouseReleased(x,y,button);
    }
    virtual void gotMessage(ofMessage msg) {
        currentSeq->gotMessage(msg);
    }
private:
    int   frameCount;
    vector<Seq*> sequences;
    int   seqIdx;
    Seq  *currentSeq;
};


#endif

