//url from the tutorial : https://www.youtube.com/watch?v=Sb08leLWOgA

//camera used : ESP32-CAM
//esp32cam Arduino Library on git hub
//https://github.com/yoursunny/esp32cam

#include <esp32cam.h> // camera library
#include <WebServer.h> //server library
#include <Wifi.h> //wifi librairy

//this programm will put the camera module in Wifi access point mode so that extern devices (phone or 
//laptop) can connect directly to it. Then they will be able to open up a browser and view the captured images.
//in that wahy the program is more portable than if it was connect to the home wifi

#define AP_SSID "AP_SS1D" //SSID for the access point
#define AP_PASS "Passw0rd!" //password for the access point

WebServer server(80); //instance for the web server using port 80 which is standart HTTP port

//request handler colled to captured images
void handleCapture(){
  auto img = esp32cam::capture(); //library to capture an image
  if (img==nullptr){
    server.send(500, "", "");
    return;
  }
  //if the pointer return a null array then the browser answer a 500 status which is the generic internal server error code
  //otherwhise it send the image from the camera module to HTTP
  server.setContentLength(img->size());
  server.send(200, "image/jpeg");
  WifiClient client = server.client();
  img->writeTo(client);
}

void setup() {
  auto res = esp32cam::Resolution::find(1024, 728); //resolution wanted
  esp32cam::Config cfg;
  cfg.setPins(esp32cam::pins::AiThinker); //pin configuration //maybe the mmodule will have a different version ... to verify
  cfg.setResolution(res); //resolution
  cfg.setJpeg(80); //JPEG image quality
  esp32cam::Camera.begin(cfg); //starting the camera module
  Wifi.softAP(AP_SSID, AP_PASS); // starting wifi access point
  server.on("/capture.jpg", handleCapture);
  server.begin();
}

void loop() {
  server.handleclient();
}
