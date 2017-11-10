#include "ofApp.h"
#include <CoreServices/CoreServices.h>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <vector>
#include <condition_variable>
#include <atomic>

#include <strings.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "socket_t.h"

#include <ctime>

#include "InterValue.h"

static std::string run_cmd(const std::string& cmd) {
    FILE* fd = popen(cmd.c_str(), "r");
    if (!fd) throw std::runtime_error("Failed to popen");
    std::string result;
    while (true) {
        char buf[1024];
        buf[0] = 0;
        if (!fgets(buf, sizeof(buf), fd)) {
            break;
        }
        result += buf;
    }
    pclose(fd);
    return result;
}

struct tlv {
    uint8_t type;
    uint32_t len;
    uint8_t* data;
    
    void read(socket_t& socket) {
        int n = ::read(socket.get(), (char*)&type, sizeof(type));
        if (n != sizeof(type)) throw std::runtime_error("Unable to read type");
        
        n = ::read(socket.get(), (char*)&len, sizeof(len));
        if (n != sizeof(len)) throw std::runtime_error("Unable to read length");
        
        n = 0;
        while (n < len) {
            int r = ::read(socket.get(), data + n, len - n);
            if (r < 0) throw std::runtime_error("Unable to read value");
            n += r;
        }
    }
    
    void write(socket_t& socket) {
        int n = ::send(socket.get(), (char*)&type, sizeof(type), 0);
        if (n != sizeof(type)) throw std::runtime_error("Unable to write");
        
        n = ::send(socket.get(), (char*)&len, sizeof(len), 0);
        if (n != sizeof(len)) throw std::runtime_error("Unable to write");
        
        n = 0;
        while (n < len) {
            int w = ::send(socket.get(), data + n, len - n, 0);
            if (w < 0) throw std::runtime_error("Unable to write");
            n += w;
        }
    }
    
};

socket_t server_sock;
socket_t client_sock;
std::thread server_thread;
std::vector<tlv> tx_queue;
std::mutex tx_queue_mtx;
std::condition_variable tx_queue_nonempty;
std::atomic<bool> tx_queue_alive{true};
std::vector<tlv> rx_queue;
std::mutex rx_queue_mtx;
std::condition_variable rx_queue_nonempty;
std::atomic<bool> run_randomizer;//TODO remove
std::thread randomizer_thread;//TODO remove

static const std::vector<std::string> words_list = {"Optimism", "Action", "Inaction", "Abundance", "Structure", "Sexuality", "Movement", "Courage", "Meditation", "Cycles", "Fairness", "Surrender", "Endings", "Balance", "Destructive", "Collapse", "Hope", "Mystery", "Success", "Rebirth", "Completion", "Serious", "Intelligent", "Fierce", "Unstable", "Clarity", "Indecision", "Heartbreak", "Meditation", "Hostility", "Leaving", "Abandon", "Stuck", "Anxiety", "Sabotage", "Repression", "Intuitive", "Romantic", "Creative", "Joy", "Partnership", "Celebration", "Boredom", "Self-pity", "Kindness", "Indecision", "Abandon", "Indulgence", "Attainment", "Passionate", "Confidant", "Adventurous", "Inspired", "Fertile", "Contemplation", "Reward", "Celebration", "Competition", "Success", "Defensive", "Speedy", "Pessimism", "Exhaustion", "Secure", "Healthy", "Cautious", "Student", "Clarity", "Balance", "Work", "Hoarding", "Petty", "Charity", "Patience", "Focused", "Luxury", "Success"};

//--------------------------------------------------------------

ofApp *mainApp = NULL;
InterValue __emotion(0.1, 0.4, 0.3);
InterValue __height(0.2, 0.4, 0.3);
InterValue __width(0.2, 0.4, 0.3);

InterValue __startLength1(1, 0.4, 0.3);
InterValue __startSlope1(0.1, 0.4, 0.3);

InterValue __emotion2(0.1, 0.4, 0.3);
InterValue __height2(0.2, 0.4, 0.3);
InterValue __width2(0.2, 0.4, 0.3);

void ofApp::setup(){
    mainApp = this;
    //it's in reproducing the art that I realize that I am about to get my ass kicked and that the work I need to focus on is my emotional state of being and how attempting to reproduce mastery makes me feel
    
    //how do I feel about the piece currently? Its still not human enough

    // Drawing 0
    ofBackground(250);
    gui.setup();
    
    emotion = 0;
    height = 0;
    width = 0;
//    gui.add(emotion.setup("emotion", 0.5,0,20));
//    gui.add(height.setup("height",5,1,20));
//    gui.add(width.setup("width",20,10,200));
    
    // Drawing 1
    pen1.set(0,0);
    nextPen1.set(0,0);
    penSwitch1 = true;
    emotion1 = 10;
    startLength1 = 0;
    startSlope1 = 0.0;
    angle1 = 0;
    margin1 = 0;
    origin1.set(margin1,margin1*3);
    
    // Drawing 2
    emotion2 = 0;
    height2 = 0;
    width2 = 0;
//    gui.add(emotion2.setup("emotion2", 0.5,0,20));
//    gui.add(height2.setup("height2",5,1,20));
//    gui.add(width2.setup("width2",20,10,200));
    
    __emotion.setTarget(emotion);
    __height.setTarget(height);
    __width.setTarget(width);
    
    __startLength1.setTarget(startLength1);
    __startSlope1.setTarget(startSlope1);
    
    __emotion2.setTarget(emotion2);
    __height2.setTarget(height2);
    __width2.setTarget(width2);
    
    font.load("Lucida-Blackletter.ttf", 20, true, true);
    
    this->wordsSet[0] = "";
    this->wordsSet[1] = "";
    this->wordsSet[2] = "";

    //TODO: remove this word randomizer
    srand(time(nullptr));
    ofApp& thiz = *this;
    run_randomizer = true;
    randomizer_thread = std::thread([&]{
        while (run_randomizer == true) {
//            srand(time(NULL));
//            int r0 = rand();
//            int r1 = rand();
//            int r2 = rand();
            auto w0 = thiz.wordsSet[0];//words_list[r0 % words_list.size()];
            auto w1 = thiz.wordsSet[1];//words_list[r1 % words_list.size()];
            auto w2 = thiz.wordsSet[2];//words_list[r2 % words_list.size()];
            thiz.setWord(0, w0);
            thiz.setWord(1, w1);
            thiz.setWord(2, w2);
            sleep(1);
        }
    });
    ////////////
    
    setUpServer();
}

//--------------------------------------------------------------
void ofApp::update(){
//    printf("frame time %d\n", time(0));
//    clock_t begin = clock();
    reactToFaceValues();
//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    printf("reacted in %f seconds\n", elapsed_secs);
    
    __emotion.approachTarget();
    __height.approachTarget();
    __width.approachTarget();
    
    __startLength1.approachTarget();
    __startSlope1.approachTarget();
    
    __emotion2.approachTarget();
    __height2.approachTarget();
    __width2.approachTarget();
    
    emotion = __emotion.current;
    height = __height.current;
    width = __width.current;
//    emotion.setup("emotion", __emotion.current,0,20);
//    height.setup("height",__height.current,30,200);
//    width.setup("width",__width.current,10,200);
    
    startLength1 = __startLength1.current;
    startSlope1 = __startSlope1.current;
    
    emotion2 = __emotion2.current;
    height2 = __height2.current;
    width2 = __width2.current;
//    emotion2.setup("emotion2", __emotion2.current,0,20);
//    height2.setup("height2",__height2.current,30,200);
//    width2.setup("width2",__width2.current,10,200);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float wordsCurrentAlpha[3];
    {
        std::unique_lock<std::mutex> lock(wordsMtx);
        for (int i = 0; i < 3; ++i) {
            wordsTime[i] += ofGetLastFrameTime();
            if (wordsTargetAlpha[i]) {
                wordsCurrentAlpha[i] = ofLerp(0, 1, ofClamp(wordsTime[i], 0, fadeTime) / fadeTime);
            } else {
                wordsCurrentAlpha[i] = 1 - ofLerp(0, 1, ofClamp(wordsTime[i], 0, fadeTime) / fadeTime);
                if (wordsCurrentAlpha[i] < 0.001f) {
                    words[i] = wordsNext[i];
                    wordsTargetAlpha[i] = true;
                    wordsTime[i] = 0;
                }
            }
        }
    }
    
    int fullWidth = ofGetWidth();
    int fullHeight = ofGetHeight();

    // Spacing between canvases
    int spacing = 50;
    // Assuming the three of them have the same width and height
    int canvasWidth = 200;
    int canvasHeight = ofGetHeight();
    
    // Calculations
    int canvasY = (fullHeight - canvasHeight) / 2;
    int canvas1X = (fullWidth - canvasWidth) / 2;
    int canvas0X = canvas1X - canvasWidth - spacing;
    int canvas2X = canvas1X + canvasWidth + spacing;
    
    ofSetColor(0, 0, 0, (int)(wordsCurrentAlpha[0] * 255));
    drawTextCentered(getWord(0), canvas0X + canvasWidth / 2, canvasHeight / 2);
    ofSetColor(0, 0, 0, (int)(wordsCurrentAlpha[1] * 255));
    drawTextCentered(getWord(1), canvas1X + canvasWidth / 2, canvasHeight / 2);
    ofSetColor(0, 0, 0, (int)(wordsCurrentAlpha[2] * 255));
    drawTextCentered(getWord(2), canvas2X + canvasWidth / 2, canvasHeight / 2);
    
    // Placement
    ofApp::draw0(canvas0X, canvasY, canvasWidth, canvasHeight);
    ofApp::draw1(canvas1X, canvasY, canvasWidth, canvasHeight);
    ofApp::draw2(canvas2X, canvasY, canvasWidth, canvasHeight);
}

void ofApp::draw0(int canvasX, int canvasY, int canvasWidth, int canvasHeight) {
    ofSeedRandom(0); // put this in to fix the emotional scale of response
    
    ofSetColor(0);
    
    float vertSpacer = 40;
    float horStep = 20;
    
    float centerSpace = 100;
    float centerStart = (canvasHeight - centerSpace) / 2.0;
    float centerEnd = (canvasHeight + centerSpace) / 2.0;
    
    //line drawing
    
    for (int h = 0; h * vertSpacer <= canvasHeight; h++){
        if (h * vertSpacer >= centerStart && h * vertSpacer <= centerEnd) { continue; }
        ofPolyline myLine;
        for (int i = 0; i * horStep <= canvasWidth; i++){
            //            float yDown = ofRandom(20,40);
            float yDown = ofRandom(height);
            float yUp = ofRandom(20);
            float xForward = ofRandom(width);
            float xBack = ofRandom(10);
            
            //what this is does is take a percentage of the range to map and create more chaos later in the function. Is this linear?
            //            float pct = ofMap(i, 0, 20, 0, 1); //the more the second value is increased, the more controlled this gets
            
            float pct = ofMap(i*(h*mouseX*0.01), 0, 1000, 0, 1); //the more the second value is increased, the less jagged the line gets
            
            if (i % 2 == 0){
                //                float x = 10 + i * 20 + ofRandom(-pct*10, pct*10);//                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = canvasX + xBack + i * horStep + ofRandom(-emotion*10, emotion*10);
                // one thing with this param being coded in this way is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = canvasY - yDown + (i*0) + h * vertSpacer;
                myLine.addVertex(x,y);
            } else {
                //                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = canvasX + xBack + xForward + i * 20 + ofRandom(-emotion*10, emotion*10); // one thing with this param is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = canvasY + yDown + (i*0) +  h * vertSpacer;
                myLine.addVertex(x,y);
            }
            myLine.draw();
        }
        
        gui.draw();
    }
    //}
}

void ofApp::draw1(int canvasX, int canvasY, int canvasWidth, int canvasHeight){
    
    float centerSpace = 100;
    float centerStart = (canvasHeight - centerSpace) / 2.0;
    float centerEnd = (canvasHeight + centerSpace) / 2.0;
    float vertSpace = 60;
    
    ofSetColor(0);
    ofSeedRandom(1);
    while (origin1.y < canvasHeight - margin1){
        if (origin1.y >= centerStart && origin1.y <= centerEnd) {
            origin1.y += vertSpace;
            continue;
        }
        pen1.x = origin1.x;
        pen1.y = origin1.y;
        //  ofPolyline line;
        
        while (origin1.x < canvasWidth - margin1){
            float length;
            float slope;
            if (!penSwitch1){
                slope = startSlope1 - ofRandom(10)/20;
            }
            else {
                slope = startSlope1 + ofRandom(10)/20;
            }
            angle1 = atan(slope);
//            printf("%f,", angle1);
            length = ofRandom(startLength1) + 5;
            
            if ((origin1.y - pen1.y) > 10){
                if (!penSwitch1){
                    length *= 2;
                }
                else {
                    length *=0.5;
                }
            }
            
            if ((origin1.y - pen1.y) < -10) {
                if (!penSwitch1){
                    length *= 2;
                }
                else{
                    length *=0.5;
                }
            }
            
            float xChange = 0;
            float yChange = 0;
            if (!penSwitch1){
                xChange = cos(angle1)*length;
            }
            else{
                xChange  = -cos(angle1)*length;
            }
            
            if (!penSwitch1){
                yChange = sin(angle1)*length * 0.5;
            }
            else{
                yChange  = -sin(angle1)*length * 0.5;
            }
            
            nextPen1.x = pen1.x + xChange;
            nextPen1.y = pen1.y + yChange;
            ofDrawLine(canvasX + pen1.x, canvasY + pen1.y, canvasX + nextPen1.x, canvasY + nextPen1.y);
            // line.addVertex(pen.x, pen.y);
            //line.addVertex(nextPen.x, nextPen.y);
            
            pen1.x = nextPen1.x;
            pen1.y = nextPen1.y;
            penSwitch1 = !penSwitch1;
            origin1.x += xChange;
            
            
        }
        origin1.x = margin1;
        origin1.y += vertSpace;
        // line.draw();
    }
    origin1.y = margin1*3;
}

void ofApp::draw2(int canvasX, int canvasY, int canvasWidth, int canvasHeight){
    
    float centerSpace = 100;
    float centerStart = (canvasHeight - centerSpace) / 2.0;
    float centerEnd = (canvasHeight + centerSpace) / 2.0;
    
    ofSeedRandom(0); // put this in to fix the emotional scale of response
    
    ofSetColor(0);
    float vertSpacer = 40;
    float horStep = 20;
    
    //line drawing
    
    for (int h = 0; h * vertSpacer <= canvasHeight; h++){
        if (h * vertSpacer >= centerStart && h * vertSpacer <= centerEnd) { continue; }
        ofPolyline myLine;
        for (int i = 0; i * horStep <= canvasWidth; i++){
            
            //            float yDown = ofRandom(20,40);
            float yDown = ofRandom(height2);
            float yUp = ofRandom(20);
            float xForward = ofRandom(width2);
            float xBack = ofRandom(10);
            
            //what this is does is take a percentage of the range to map and create more chaos later in the function. Is this linear?
            //            float pct = ofMap(i, 0, 20, 0, 1); //the more the second value is increased, the more controlled this gets
            
            float pct = ofMap(i*(h*500*0.01), 0, 1000, 0, 1); //the more the second value is increased, the less jagged the line gets
            
            if (i % 2 == 0){
                //                float x = 10 + i * 20 + ofRandom(-pct*10, pct*10);//                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = canvasX + xBack + i * horStep + ofRandom(-emotion2*10, emotion2*10);
                // one thing with this param being coded in this way is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = canvasY - yDown + (i*0) + h * vertSpacer;
                myLine.addVertex(x,y);
            } else {
                //                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = canvasX + xBack + xForward + i * 20 + ofRandom(-emotion2*10, emotion2*10); // one thing with this param is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = canvasY + yDown + (i*0) +  h * vertSpacer;
                myLine.addVertex(x,y);
            }
            myLine.draw();
        }
        
        gui.draw();
    }
    //}
    
    
}

void ofApp::setWord(int i, const std::string& word) {
    std::unique_lock<std::mutex> lock{wordsMtx};
    if (wordsNext[i] == word) return;
    wordsNext[i] = word;
    wordsTime[i] = 0;
    wordsTargetAlpha[i] = false;
}

std::string ofApp::getWord(int i) {
    std::unique_lock<std::mutex> lock{wordsMtx};
    return words[i];
}

void ofApp::drawTextCentered(const std::string& text, float x, float y) {
    auto bbox = font.getStringBoundingBox(text, 0, 0);
    font.drawString(text, x - bbox.getCenter().x, y);
}

void ofApp::exit(){
    {
        std::unique_lock<std::mutex> lock{tx_queue_mtx};
        tx_queue_alive = false;
        tx_queue_nonempty.notify_all();
    }
    client_sock.close();
    server_sock.close();
    server_thread.join();
    run_randomizer = false;
    randomizer_thread.join();
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

//------------------------------------------------

void ofApp::setUpServer() {
    server_thread = std::thread([] {
        server_sock = socket_t{socket_domain_t::inet, socket_type_t::stream};
        sockaddr_in serv_addr;
        bzero(&serv_addr, sizeof(serv_addr));
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(12345);
        
        server_sock.bind((sockaddr*)&serv_addr, sizeof(serv_addr));//TODO catch address in use
        server_sock.listen(5);
        
        sockaddr_in cli_addr;
        socklen_t cli_addr_len = sizeof(cli_addr);
        try {
            client_sock = server_sock.accept((sockaddr *) &cli_addr, &cli_addr_len);
        } catch (std::runtime_error& e) {
            std::cout << "Accept error: " << e.what() << std::endl;
        }
        std::string cli_host = inet_ntoa(cli_addr.sin_addr);
        int cli_port = ntohs(cli_addr.sin_port);
        std::cout << "Connection from: " << cli_host << " port " << cli_port << std::endl;
        
        std::thread writer([&] {
            while (tx_queue_alive) {
                std::vector<tlv> txq;
                {
                    std::unique_lock<std::mutex> lock{tx_queue_mtx};
                    while (tx_queue.empty() && tx_queue_alive) {
                        tx_queue_nonempty.wait(lock);
                    }
                    if (!tx_queue_alive) goto done_tx;
                    txq = std::vector<tlv>{tx_queue};
                    tx_queue.clear();
                }
                for (auto& tx : txq) {
                    try {
                        tx.write(client_sock);
                        delete [] tx.data;
                    } catch (...) {
                        goto done_tx;
                    }
                }
            }
        done_tx:
            std::cout << "TX closed" << std::endl;
        });
        
        char rx_buf[1024 * 32];
        tlv rx{0, 0, (uint8_t*)rx_buf};
        while (true) {
            try {
                rx.read(client_sock);
            } catch (std::runtime_error& e) {
                std::cout << "Read error: " << e.what() << std::endl;
                break;
            }
            rx.data = new uint8_t[rx.len];
            memcpy(rx.data, rx_buf, rx.len);
            std::unique_lock<std::mutex> lock{rx_queue_mtx};
            rx_queue.push_back(rx);
            rx.data = (uint8_t*)rx_buf;
            rx_queue_nonempty.notify_all();
        }
        std::cout << "RX closed" << std::endl;
        
        writer.join();
        
        client_sock.close();
        server_sock.close();
        
        std::cout << "Sockets closed" << std::endl;
    });
}

static void send(const tlv& data) {
    std::unique_lock<std::mutex> lock{tx_queue_mtx};
    tx_queue.push_back(data);
    tx_queue_nonempty.notify_all();
}

static tlv recv_one() {
    std::unique_lock<std::mutex> lock{rx_queue_mtx};
    while (rx_queue.empty()) {
        rx_queue_nonempty.wait(lock);
    }
    tlv ret = rx_queue.front();
    rx_queue.erase(rx_queue.begin());
    return ret;
}

static tlv try_recv_one() {
    std::unique_lock<std::mutex> lock{rx_queue_mtx};
    if (rx_queue.empty()) return {0, 0, nullptr};
    tlv ret = rx_queue.front();
    rx_queue.erase(rx_queue.begin());
    return ret;
}

void ofApp::reactToFaceValues() {
    while (true) {
        auto rx = try_recv_one();
        if (!rx.data) break;
        switch (rx.type) {
            case 200:
                std::cout << "Debug: " << std::string((char*)rx.data, rx.len) << std::endl;
                break;
            case 1:
            {
                int n = rx.len / sizeof(float);
                float array[n];
                memcpy(&array, rx.data, sizeof(float) * n);
                //                std::cout << "Got face ID:" << array[0] << "," << array[1] << "," << array[2] << std::endl;
                
                if (n == 1) {
//                    printf("No face!\n");
                    mainApp->updateValues(-1, 0, 0, 0, 0, 0, 0, 0, 0);
                    return;
                }
                
//                printf("%f\n", array[0]);
                
                float _emotion = array[1] * 20.0;
                float _height = 30.0 + array[2] * (200.0 - 30.0);
                float _width = 10.0 + array[3] * (200.0 - 10.0);
                
                float _startLength1 = 35 + array[4] * 10;
                float _startSlope1 = 0.5 + array[5] * 0.5;
                
                float _emotion2 = array[6] * 20.0;
                float _height2 = 30.0 + array[7] * (200.0 - 30.0);
                float _width2 = 10.0 + array[8] * (200.0 - 10.0);
                
                mainApp->updateValues((int)floor(array[0]), _emotion, _height, _width, _startLength1, _startSlope1, _emotion2, _height2, _width2);
            }
                break;
            default:
                std::cout << "Unknown message ID: " << rx.type << std::endl;
                break;
        }
        delete [] rx.data;
    }
}

bool wordsCanChange = true;

void ofApp::updateValues(int wordIndex, float _emotion, float _height, float _width, float _startLength1, float _startSlope1, float _emotion2, float _height2, float _width2) {
    __emotion.setTarget(_emotion);
    __height.setTarget(_height);
    __width.setTarget(_width);
    
    __startLength1.setTarget(_startLength1);
    __startSlope1.setTarget(_startSlope1);
    
    __emotion2.setTarget(_emotion2);
    __height2.setTarget(_height2);
    __width2.setTarget(_width2);
    
    if (wordIndex < 0) {
        this->wordsSet[0] = "";
        this->wordsSet[1] = "";
        this->wordsSet[2] = "";
        wordsCanChange = true;
    } else if (wordsCanChange) {
        this->wordsSet[0] = words_list[wordIndex % words_list.size()];
        this->wordsSet[1] = words_list[wordIndex + 323 % words_list.size()];
        this->wordsSet[2] = words_list[wordIndex + 1428 % words_list.size()];
        wordsCanChange = false;
    }
    
}
