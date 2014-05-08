#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxCsv.h"

using namespace wng;




class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxCsv csv;
    ofxCsv csvRecorder;
    
    ofxUICanvas *gui;
    
    
    ofTrueTypeFont displayFont;
    
    void exit();
    void guiEvent(ofxUIEventArgs &e);
    int startDate;
    int endDate;
int w;
int h;
    int start_index;
    int end_index;
    int max_index;
    
    string* title;
    string* author;
    int* page;
    int* read_year;
    int* read_month;
    int* read_day;
    int* index;
    int* img_index;
	string bookStr;
    string presentStr;
    string str2, str3, str4;
    string date1, date2, date3,date4;
    
    ofImage* covers;
    bool* img_on;
    int* bookStart_ind;
    int* bookEnd_ind;
    int image_cnt;
    int img_on_cnt;
    int select;
};
