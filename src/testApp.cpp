#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    w = 1024;
    h = 768;
    
    bookStr = "";
    presentStr = "";
    
    ofBackground(0,0,0);
    
    start_index = 0;
    end_index = 420;
    
    select = 0;
    ofSetVerticalSync(true);
    gui = new ofxUICanvas();
    gui->addRangeSlider("DATERANGE", 0.0, 421.0, 0.0, 421.0, 1024, 30);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->loadSettings("settings.xml");
    
    displayFont.loadFont("AmericanTypewriter-Bold", 12);
    
    author = new string[421];
    title = new string[421];
    page = new int[421];
    read_day = new int[421];
    read_month = new int[421];
    read_year = new int[421];
    index = new int[421];
    img_index = new int[421];
    
    covers = new ofImage[18];
    img_on = new bool[18];
    bookStart_ind = new int[18];
    bookEnd_ind = new int[18];
    img_on_cnt = 0;
    
    
    string book = "default";
    int cur_img = -1;
    
    csv.loadFile(ofToDataPath("ReadingData5.csv"), ",");
    cout << csv.numRows << " " << csv.data.size() << endl;
    max_index = csv.numRows;
    
    for(int i=0; i < csv.numRows; i++){
        title[i] = csv.data[i][0];
        if(title[i].length() > 0){
            img_index[i] = cur_img;
        }else{
            img_index[i] = -1;
        }
        if((cur_img >= 0) && (!ofIsStringInString(title[i], book))){
            bookEnd_ind[cur_img] = i-1;
        }
        
        if((title[i].length() > 0) && (!ofIsStringInString(title[i],book))){
            cout << "new title: " << title[i] << endl;
            
            book = title[i];
            cur_img++;
            bookStart_ind[cur_img] = i;
            covers[cur_img].loadImage("images/" + title[i] + ".jpg");
            img_on[cur_img] = true;
            img_on_cnt++;
        }
        cout << "m: " << csv.data[i][3] << " d: " <<csv.data[i][4] << " y: " << csv.data[i][5] << endl;
        author[i] = csv.data[i][1];
        page[i] = ofToInt(csv.data[i][2]);
        read_month[i] = ofToInt(csv.data[i][3]);
        read_day[i] = ofToInt(csv.data[i][4]);
        read_year[i] = ofToInt(csv.data[i][5]);
        index[i] = i;
        
        cout << title[i] << " img #: " << img_index[i] << endl;
    }
    image_cnt = cur_img + 1;
    
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i = 0; i < image_cnt; i++){
        img_on[i] = false;
    }
    img_on_cnt = 0;
    for(int i = start_index; i < end_index; i++){
        img_on[img_index[i]] = true;
    }
    for(int i = 0; i < image_cnt; i++){
        if(img_on[i] == true){
            img_on_cnt++;
        }
    }
    cout << "num of images: " << img_on_cnt << endl;
    cout << "sel: " << select << "month: " << read_month[select] << " day: " << read_day[select] << " year " << read_year[select] << endl;
    string datestr = ofToString(read_month[select],2,'0') + ofToString(read_day[select],2,'0') + ofToString(read_year[select]);

    string fname = "sentences/nworkfile";
    cout << "open: " << fname << datestr << endl;
    ofFile newfile(ofToDataPath(fname + datestr + ".txt",ofFile::ReadOnly));
    if(newfile.exists()){
        ofBuffer buf = newfile.readToBuffer();
        bookStr = string(buf);
        cout << bookStr;
    }
    if( ofIsStringInString(bookStr, "no reading") || ofIsStringInString(bookStr, "no file") || ofIsStringInString(bookStr, "[blank]")){
        presentStr = "";
    }else{
        presentStr = bookStr;
    }
    
    if(presentStr.length() > 210){
        str4 = presentStr.substr(210,presentStr.length() > 279 ? 70 : presentStr.length() - 210);
        presentStr = presentStr.substr(0,210);
    }else{
        str4 = "";
    }
    if(presentStr.length() > 140){
        str3 = presentStr.substr(140,presentStr.length() > 209 ? 70 : presentStr.length() - 140);
        presentStr = presentStr.substr(0,140);
    }else{
        str3 = "";
    }
    if(presentStr.length() > 70){
        str2 = presentStr.substr(70,presentStr.length() > 139 ? 139 : presentStr.length() -70 );
        presentStr = presentStr.substr(0,70);
    }else{
        str2 = "";
    }
    
    //Calculate and label dates
    date1 = ofToString(read_month[start_index],2,'0') + "/" + ofToString(read_day[start_index],2,'0') + "/" + ofToString(read_year[start_index]);
    int ind2 = round((end_index - start_index)/3);
    int ind3 = round(2*(end_index - start_index)/3);
    date2 = ofToString(read_month[ind2],2,'0') + "/" + ofToString(read_day[ind2],2,'0') + "/" + ofToString(read_year[ind2]);
    date3 = ofToString(read_month[ind3],2,'0') + "/" + ofToString(read_day[ind3],2,'0') + "/" + ofToString(read_year[ind3]);
    if(end_index == max_index){
        date4 = ofToString(read_month[end_index-1],2,'0') + "/" + ofToString(read_day[end_index-1],2,'0') + "/" + ofToString(read_year[end_index-1]);
    }else{
        date4 = ofToString(read_month[end_index],2,'0') + "/" + ofToString(read_day[end_index],2,'0') + "/" + ofToString(read_year[end_index]);
    }
    cout << endl << date1 << " " << date2 << " " << date3 << " " << date4 << " " << end_index << endl;
}

//--------------------------------------------------------------
void testApp::draw(){
 //   ofPushStyle();
 //   ofSetColor(255, 255, 255);
 //   ofRect(0,30,200,40);
 //   ofPopStyle();
    
    int x0 = 0;
    int h_space = 50;
    if(img_on_cnt > 0){
        
        h_space = (w / img_on_cnt);
        cout << "image width: " << h_space << endl;
    }
    int img_w = h_space - 5;
    int img_h = (3*img_w/2);
    if(img_h > 500){
        img_h = 500;
        img_w = (2*img_h/3);
    }
    int balance_shift = round((w - (img_on_cnt*img_w))/(img_on_cnt + 1));
    int y0 = ((h - 30)/2) - (img_h / 2) + 20;
    for(int i=0; i < image_cnt; i++){
        if(img_on[i]){
            covers[i].draw(ofPoint(x0 + balance_shift,y0), img_w, img_h);
            ofLine(x0 + balance_shift, y0,  ofMap(bookStart_ind[i],start_index,end_index,0,w), 110);
            ofLine(ofMap(bookStart_ind[i],start_index,end_index,0,w), 110, ofMap(bookStart_ind[i],start_index,end_index,0,w), 90);
            ofLine(x0+img_w + balance_shift, y0,  ofMap(bookEnd_ind[i],start_index,end_index,0,w), 110);
            ofLine(ofMap(bookEnd_ind[i],start_index,end_index,0,w), 110, ofMap(bookEnd_ind[i],start_index,end_index,0,w), 90);
            x0 = x0 + h_space;
        }
    }
    ofLine(0,110,w,110);
    ofLine(0,80,w,80);
    for(int i=start_index; i < end_index; i++){
        if (read_day[i] == 1){
            ofLine(ofMap(i,start_index,end_index,0,w),80,ofMap(i,start_index,end_index,0,w),100);
        }
    }
    ofLine(ofMap(select,start_index,end_index,0,w),80,ofMap(select,start_index,end_index,0,w),110);
    
    displayFont.drawString(presentStr, 200, 690);
    displayFont.drawString(str2,200,705);
    displayFont.drawString(str3,200,720);
    displayFont.drawString(str4,200,735);
    
    displayFont.drawString(date1,(0)*w/4 + 20,70);
    ofLine(20,70,0,80);
  //  displayFont.drawString(date2,1*w/3 + 20,70);
  //  displayFont.drawString(date3,2*w/3 + 20,70);
    displayFont.drawString(date4,.89*w,70);
    ofLine(w-20,70,w,80);

    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    gui->toggleVisible();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    select = ofMap(x, 0, w, start_index, end_index);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::exit(){
    gui->saveSettings("settings.xml");
    delete gui;
}

void testApp::guiEvent(ofxUIEventArgs &e){
    string name = e.getName();
    int kind = e.getKind();
    cout << name << kind << endl;
    
    if(kind == OFX_UI_WIDGET_RSLIDER_H){
        ofxUIRangeSlider *n = (ofxUIRangeSlider *) e.widget;
        start_index = round(n->getNormalizedValueLow()*max_index);
        end_index = round(n->getNormalizedValueHigh()*max_index);
        cout << start_index << " to " << end_index << endl;
        cout << n->getNormalizedValueHigh() << " " << n->getNormalizedValueLow() << endl;
    }
    if(e.getName() == "DATERANGE"){
 //       ofxUIRangeSlider *slider = e.getSlider();
   //     ofxUISlider *slider = e.getSlider();
     //   slider->
     //   ofxUIRangeSlider *rslider = e.getRangeSlider();
//        ofxUISlider *slider = e.getSlider();
       // rslider->
      //  ofBackground(slider->getScaledValue());
    }else if(e.getName() == "FULLSCREEN"){
        ofxUIToggle *toggle = e.getToggle();
        ofSetFullscreen(toggle->getValue());
    }
}