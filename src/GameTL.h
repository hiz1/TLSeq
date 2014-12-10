//
//  GameTL.h
//  katamichi001
//
//  Created by hiz on 2014/12/10.
//
//

#ifndef katamichi001_GameTL_h
#define katamichi001_GameTL_h

#define TILESIZE 80
#define MARGIN   4
#define TILECOL  12
#define TILEROW  7

#include "TL.h"
#include "ofMain.h"

ofVec2f charaPos(float xi, float yi) {
    int baseX = - (TILECOL * (TILESIZE + MARGIN) - MARGIN) / 2;
    int baseY = - (TILEROW * (TILESIZE + MARGIN) - MARGIN) / 2;
    return ofVec2f(baseX + xi * (TILESIZE + MARGIN) + TILESIZE/2, baseY + yi * (TILESIZE + MARGIN) + TILESIZE/2);
}

ofVec2f tilePos(int xi, int yi) {
    int baseX = - (TILECOL * (TILESIZE + MARGIN) - MARGIN) / 2;
    int baseY = - (TILEROW * (TILESIZE + MARGIN) - MARGIN) / 2;
    return ofVec2f(baseX + xi * (TILESIZE + MARGIN) + TILESIZE/2, baseY + yi * (TILESIZE + MARGIN) + TILESIZE/2);
}

class GameTL : public TL {
    typedef TL base;
    
public:
    
    class MoveSeq : public Seq {
    public:
        typedef Seq base;
        MoveSeq(TL &phase, string seqId) : Seq(phase, seqId) {}
        
        virtual void setup(const ofParameterGroup *parm) {
            base::setup(parm);
            GameTL &t = (GameTL &)tl();
            
            maxFrame = 10;
            prePos = t.pos;
            
            int key = parm->get<int>("key");
            if(key == OF_KEY_UP   )nextPos = t.pos + ofVec2f( 0, 1);
            if(key == OF_KEY_DOWN )nextPos = t.pos + ofVec2f( 0,-1);
            if(key == OF_KEY_LEFT )nextPos = t.pos + ofVec2f(-1,0);
            if(key == OF_KEY_RIGHT)nextPos = t.pos + ofVec2f( 1,0);
            
        }
        
        virtual bool update(ofParameterGroup *parm) {
            base::update(parm);
            GameTL &t = (GameTL &)tl();
            
            t.pos = ofVec2f(ofMap(frame(), 0, maxFrame, t.pos.x, nextPos.x),
                            ofMap(frame(), 0, maxFrame, t.pos.y, nextPos.y));
            
            if(frame() >= maxFrame) {
                t.pos = nextPos;
                return true;
            }
            return false;
            
        }

        virtual void keyPressed(int key) {
            GameTL &t = (GameTL &)tl();
            
        }
    private:
        int     maxFrame;
        ofVec2f prePos;
        ofVec2f nextPos;
    };
    
    GameTL() : TL() {
        ofBackground(0);
        camera.setPosition(0, 0, 700);
        pos = ofVec2f(int(TILEROW/2), 3);
        bg = new ofImage();
        bg->loadImage("t_sand.png");
        player = new ofImage();
        player->loadImage("mon_217.png");
        player->setAnchorPercent(0.5, 0.0);
        enemy = new ofImage();
        enemy->loadImage("mon_139.png");
        enemy->setAnchorPercent(0.5, 0.0);
        
        vector<int> keys;
        keys.push_back(OF_KEY_UP);
        keys.push_back(OF_KEY_DOWN);
        keys.push_back(OF_KEY_LEFT);
        keys.push_back(OF_KEY_RIGHT);
        
        this->addSequence(new InputSeq(*this, "input", keys));
        this->addSequence(new MoveSeq( *this, "move"));
        this->setSeqIdx(0, NULL);
    }
    virtual bool update() {
        camera.lookAt(ofVec3f::zero());
        base::update();
    }
    virtual void draw() {
        camera.begin();
        
        // タイル描画
        ofPushMatrix();
        ofRotate(-20, 1, 0, 0);
        int baseX = - (TILECOL * (TILESIZE + MARGIN) - MARGIN) / 2;
        int baseY = - (TILEROW * (TILESIZE + MARGIN) - MARGIN) / 2;
        
        for(int xi=0;xi<TILECOL;xi++) {
            for(int yi=0;yi<TILEROW;yi++) {
                int x = xi * (TILESIZE + MARGIN);
                int y = yi * (TILESIZE + MARGIN);
                ofSetColor(122);
                ofFill();
                ofVec2f pos = tilePos(xi, yi);
                bg->draw(pos.x - TILESIZE/2, pos.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            }
        }
        
        ofVec2f p;
        
        
        if(getSeq().seqId() == "input") {
            // プレイヤー位置タイル描画
            p = charaPos(pos.x, pos.y);
            ofSetColor(255,255,255,122);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            
            // 敵位置タイル描画
            p = tilePos(8, 2);
            ofSetColor(255,255,255,122);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            ofSetColor(255);
            
            // 移動先タイル描画
            //    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            
            // プレイヤー移動先
            ofSetColor(40,120,255,122);
            p = tilePos(pos.x-1, pos.y);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            p = tilePos(pos.x+1, pos.y);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            p = tilePos(pos.x  , pos.y-1);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            p = tilePos(pos.x  , pos.y+1);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            
            // 敵移動先
            ofSetColor(255,255,40,122);
//            p = tilePos(8-1, 2);
//            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            p = tilePos(8+1, 2);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            p = tilePos(8  , 2-1);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            p = tilePos(8  , 2+1);
            ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
            
            // 攻撃先タイル描画
            ofNoFill();
            int lineWidth = 10;
            ofSetLineWidth(lineWidth);
            
            // 敵攻撃先
            ofSetColor(255,40,40,180);
            p = tilePos(8-1, 2);
            ofRect(p.x - TILESIZE/2+lineWidth/4, p.y - TILESIZE/2+lineWidth/4, 0, TILESIZE-lineWidth/2, TILESIZE-lineWidth/2);
            p = tilePos(8-2, 2);
            ofRect(p.x - TILESIZE/2+lineWidth/4, p.y - TILESIZE/2+lineWidth/4, 0, TILESIZE-lineWidth/2, TILESIZE-lineWidth/2);
            
            // プレイヤー攻撃先
            ofSetLineWidth(lineWidth/2);
            ofSetColor(40,255,180,140);
            p = tilePos(pos.x+1, pos.y);
            ofRect(p.x - TILESIZE/2+lineWidth/4, p.y - TILESIZE/2+lineWidth/4, 0, TILESIZE-lineWidth/2, TILESIZE-lineWidth/2);
            p = tilePos(pos.x+1, pos.y+1);
            ofRect(p.x - TILESIZE/2+lineWidth/4, p.y - TILESIZE/2+lineWidth/4, 0, TILESIZE-lineWidth/2, TILESIZE-lineWidth/2);
            p = tilePos(pos.x+1, pos.y-1);
            ofRect(p.x - TILESIZE/2+lineWidth/4, p.y - TILESIZE/2+lineWidth/4, 0, TILESIZE-lineWidth/2, TILESIZE-lineWidth/2);
            
            ofSetLineWidth(1);
            ofFill();
        }
        
        
        
        // プレイヤー描画
        p = charaPos(pos.x, pos.y);
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(p.x, p.y - TILESIZE/4, 0);
        ofRotate(20, 1, 0, 0);
        ofScale(1.5,1.5,1.5);
        player->draw(0,0);
        ofPopMatrix();
        
        // 敵描画
        p = tilePos(8, 2);
        ofPushMatrix();
        ofTranslate(p.x, p.y - TILESIZE/4, 0);
        ofRotate(20, 1, 0, 0);
        ofRotate(180, 0, 1, 0);
        ofScale(1.5,1.5,1.5);
        enemy->draw(0,0);
        ofPopMatrix();
        
        ofPopMatrix();
        camera.end();
    }
private:
    ofCamera camera;
    ofVec2f  pos;
    ofImage *bg;
    ofImage *player;
    ofImage *enemy;
};

#endif
