#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* SSID = "Enter your WiFi SSID";      //Changeable (Optional)
const char* password = "Enter your WiFi password";    
IPAddress static_IP(192, 168, 0, 2);    //static IP Adress set for the device
IPAddress gateway(192, 168, 0, 1);      //router gateway for DHCP and ICMP pings
IPAddress subnet(255, 255, 255, 0);     //Local IP address based on private IP