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

ofVec2f tilePos(int xi, int yi) {
    int baseX = - (TILECOL * (TILESIZE + MARGIN) - MARGIN) / 2;
    int baseY = - (TILEROW * (TILESIZE + MARGIN) - MARGIN) / 2;
    return ofVec2f(baseX + xi * (TILESIZE + MARGIN) + TILESIZE/2, baseY + yi * (TILESIZE + MARGIN) + TILESIZE/2);
}

class GameTL : public TL {
    typedef TL base;
    
public:
    
    class InputWaitSeq : public Seq {
    public:
        typedef Seq base;
        InputWaitSeq(TL &phase, string seqId) : Seq(phase, seqId) {}

        virtual void keyPressed(int key) {
            GameTL &t = (GameTL &)tl();
            if(key == OF_KEY_UP   )t.pos.y ++;
            if(key == OF_KEY_DOWN )t.pos.y --;
            if(key == OF_KEY_LEFT )t.pos.x --;
            if(key == OF_KEY_RIGHT)t.pos.x ++;
        }
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
        
        this->addSequence(new InputWaitSeq(*this, "input"));
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
        
        
        // 移動先タイル描画
        //    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        ofSetColor(40,120,255,122);
        p = tilePos(pos.x-1, pos.y);
        ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
        p = tilePos(pos.x+1, pos.y);
        ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
        p = tilePos(pos.x  , pos.y-1);
        ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
        p = tilePos(pos.x  , pos.y+1);
        ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
        //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        
        
        // プレイヤー描画
        p = tilePos(pos.x, pos.y);
        ofSetColor(255,255,255,122);
        ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
        
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(p.x, p.y - TILESIZE/4, 0);
        ofRotate(20, 1, 0, 0);
        ofScale(1.5,1.5,1.5);
        player->draw(0,0);
        ofPopMatrix();
        
        // 敵描画
        p = tilePos(8, 2);
        ofSetColor(255,255,255,122);
        ofRect(p.x - TILESIZE/2, p.y - TILESIZE/2, 0, TILESIZE, TILESIZE);
        ofSetColor(255);
        
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
