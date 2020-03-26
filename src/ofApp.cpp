#include "ofApp.h"
#include "ofxJSON.h"

#include <time.h>
using namespace std;
ofxJSONElement root;
float x = 0;
//--------------------------------------------------------------
void ofApp::setup(){

    
    
    std::string url = "https://api.darksky.net/forecast/5c68178780abb713f03251f8fb748e31/40.7128,-74.0059"

    // Now parse the JSON
    bool parsingSuccessful = root.open(url);

    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << root.getRawString(true);
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
   
    int sunriseTime = root["daily"]["data"][0]["sunriseTime"].asInt();
    int sunsetTime = root["daily"]["data"][0]["sunsetTime"].asInt();
     gui.setup();
  gui.add(windSpeed.setup("WindSpeed",root["currently"]["windSpeed"].asFloat(),0.0,10.0));

  gui.add(temperature.setup("Temperature",root["currently"]["temperature"].asFloat(),0.0,100.0));
    
    gui.add(daytime.setup("dayTime",sunriseTime,sunriseTime,sunsetTime));
    
}

//--------------------------------------------------------------
void ofApp::update(){

}
std::ostringstream text;
float lerpTemp;

//--------------------------------------------------------------
void ofApp::draw(){

    std::string summary = root["currently"]["summary"].asString();
    time_t sunriseTime = root["daily"]["data"][0]["sunriseTime"].asInt();
    int sunsetTime = root["daily"]["data"][0]["sunsetTime"].asInt();
    time_t currentEpoch = root["currently"]["time"].asInt(); // get sample epoch
    float temp = root["currently"]["temperature"].asFloat();
    float wind = root["currently"]["windSpeed"].asFloat();
    time_t current = time(NULL);  // get current epoch

    

     struct tm* currentTime = localtime(&sunriseTime);
     char usrdefFormat[50] = { 0 };
     strftime(usrdefFormat, 50, "%Y-%m-%d %H:%M:%S", currentTime);


    
    if (ofGetFrameNum() == 1) {
      text << summary <<"\n"<< "Current epoch: " << currentEpoch <<"\n"<< "Sunrise time:" << sunriseTime <<"\n"<<"Sunset time: " << sunsetTime <<"\n"<< "Temperature: " << temp << "\n"<<"WindSpeed:"<<wind<<"\n"<<"Current time:"<<usrdefFormat;
     
       
    }
     ofSetColor(255,255,255);
    ofDrawBitmapString(text.str(), 20, 40);
    
    
    //Use sunrise/sunset time to change the background color.
   
     ofColor c(68, 169, 255); // Bright blue ...
       c.setBrightness(ofMap(daytime,sunriseTime,sunsetTime,255,20));
  

  
 ofSetBackgroundColor(c); // greenish
    
//temperature controls the color of circle
    ofColor tempColor = ofColor::blue;
    ofColor yellow = ofColor::yellow;
    tempColor.lerp(yellow,  ofMap(temperature, 0.0, 100.0, 0.0, 1.0));
    ofSetColor(tempColor);
    
//wind speed controls the movement
    x+= windSpeed;
    if(x>ofGetWidth()){
        x=0.0;
    }
    ofDrawCircle(x, ofGetHeight()/2, 40);
    
    
    gui.draw();
    cout<<temp<<lerpTemp<<endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


void ofApp::unixTime2Str(int n, char strTime[], int bufLen)
{
    struct tm tm = *localtime((time_t *)&n);
    strftime(strTime, bufLen - 1, "%Y-%m-%d %H:%M:%S", &tm);
    strTime[bufLen - 1] = '\0';
}

