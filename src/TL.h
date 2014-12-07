//
//  TL.h
//  katamichi001
//
//  Created by hiz on 2014/12/03.
//
//

#ifndef katamichi001_TL_h
#define katamichi001_TL_h

class TL;

// DONE:Sequenceを順番に実行
// DONE:入力処理
// DONE:Sequenceの返値。Seq終了時に値を返す
// DONE:Sequenceの途中で別Sequenceに移行←返値によってTL側で次のSeqを決める
// TODO:Sequence終了時の処理をSeqと戻り値によって変更
// TODO:TLの並列実行
// TODO:TL間のメッセージング
// TODO:Sequenceの親子関係（必要？）

class Seq {
public:
    Seq(TL &tl) : _tl(tl){
        setup();
    }
    virtual void setup() {
        _frame = 0;
    }
    virtual string* update() {
        _frame ++;
        return NULL;
    }
    int    frame() { return _frame;}
    TL &tl() { return _tl;}
    virtual void keyPressed(int key) {}
    virtual void keyReleased(int key) {}
    virtual void mouseMoved(int x, int y ) {}
    virtual void mouseDragged(int x, int y, int button) {}
    virtual void mousePressed(int x, int y, int button) {}
    virtual void mouseReleased(int x, int y, int button) {}
    virtual void gotMessage(ofMessage msg) {}
private:
    int    _frame;
    TL &_tl;
};

class TL {
public:
    // 指定フレーム数だけウエイトするSeq
    class WaitSeq : public Seq {
    public:
        typedef Seq base;
        
        WaitSeq(TL &phase, int waitFrame)
        : Seq(phase), waitFrame(waitFrame) {}
        
        virtual string* update() {
            base::update();
            if(frame() >= waitFrame)return new string;
            return NULL;
        }
    private:
        const int waitFrame;
    };
    
    // キー入力待ちするSeq
    class InputSeq : public Seq {
    public:
        typedef Seq base;
        
        InputSeq(TL &phase, vector<int> acceptKeys, int waitFrame = -1)
        : Seq(phase),acceptKeys(acceptKeys), waitFrame(waitFrame) {}
        
        virtual void setup() {
            base::setup();
            inputedKey = -1;
        }
        
        virtual string* update() {
            base::update();
            if(inputedKey >= 0) {
                char result[1] = {char(inputedKey)};
                return new string(result);
            }
            if(waitFrame >= 0 && frame() >= waitFrame)return new string();
            return NULL;
        }
        
        virtual void keyPressed(int key) {
            vector< int >::iterator cIter = find( acceptKeys.begin(),acceptKeys.end() , key );
            if(cIter != acceptKeys.end()) inputedKey = key;
        }
    private:
        int waitFrame;
        vector<int> acceptKeys;
        int  inputedKey;
    };
    
    TL() {
        currentSeq  = NULL;
        frameCount = 0;
        
        
    }
    ~TL() {
        for(vector<Seq*>::iterator it=sequences.begin();it!=sequences.end();it++) {
            delete *it;
        }
    }
    virtual bool update() {
        frameCount ++;
        if(currentSeq != NULL) {
            string *result = currentSeq->update();
            if(result != NULL) {
                setSeqIdx(getNextSeqIdx(result));
                delete result;
            }
        }
        return false;
    }
    virtual void draw() {}
    virtual int getNextSeqIdx(string *result) {
        int nextSeq = seqIdx + 1;
        if(nextSeq >= sequences.size()) nextSeq = 0;
        return nextSeq;
    }
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

