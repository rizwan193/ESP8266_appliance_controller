#include <Config.h>
#include <CountDown.h>

WiFiServer server (80);
CountDown timer (CountDown::MINUTES);

String val, head;
#define output 2

void setup()
{
    Serial.begin(115200);
    pinMode(output, OUTPUT);
    digitalWrite(output, HIGH);
    WiFi.config(static_IP, gateway, subnet);
    WiFi.begin(SSID, password);
    Serial.println();
    Serial.println();
    Serial.println("Connecting");
    
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(300);
        Serial.print("*");
    }
    Serial.println("Connected");
    Serial.println("Local IP: ");
    Serial.println(WiFi.localIP());
    server.begin();
    Serial.println("Server Connected");
}


void loop()
{
    WiFiClient client = server.available();
    if (!client)
    {
        return;
    }
    head = client.readStringUntil('\r');
    Serial.println(head);
    client.flush();
    
    if (head.indexOf("/10") != -1)
    {
        timer.start(10);
        val = "10";
        while(timer.remaining() != 0)
        {
            Serial.println(timer.remaining());
            digitalWrite(output, LOW);
            if (timer.remaining() == 0)
            {
                timer.stop();
                digitalWrite(output, HIGH);
            }
        }
    }
    else if (head.indexOf("/20") != -1)
    {
        Serial.println("20 minutes selected");
        timer.start(20);
        val = "20";
        while(timer.remaining() != 0)
        {
            Serial.print("Remaining minutes: ");
            Serial.println(timer.remaining());
            digitalWrite(output, LOW);
            if (timer.remaining() == 0)
            {
                timer.stop();
                digitalWrite(output, HIGH);
            }
        }
    }
    else if (head.indexOf("/30") != -1)
    {
        Serial.println("30 minutes selected");
        timer.start(30);
        val = "30";
        while (timer.remaining() != 0)
        {
            Serial.print("Remaining minutes: ");
            Serial.println(timer.remaining());
            digitalWrite(output, LOW);
            if(timer.remaining() == 0)
            {
                timer.stop();
                digitalWrite(output, HIGH);
            }
        }
    }
    else if (head.indexOf("/40") != -1)
    {
        Serial.println("40 minutes selected");
        timer.start(40);
        val = "40";
        while (timer.remaining() != 0)
        {
            Serial.print("Remaining minutes: ");
            Serial.println(timer.remaining());
            digitalWrite(output, LOW);
            if(timer.remaining() == 0)
            {
                timer.stop();
                digitalWrite(output, HIGH);
            }
        }
    }
    else if (head.indexOf("/reset") != -1)
    {
        Serial.print("resetting");
        delay(100);
        ESP.reset();
    }
    else if (head.indexOf("/stop") != -1)
    {
        digitalWrite(output, HIGH);
        val = "stop";
    }
    String s = "HTTP/1.1 200 OK\r\n";
    s += "Content-Type: application/json\r\n\r\n";
    s += "{\"data\":{\"message\":\"success\",\"value\":\"";
    s += val;
    s += "\"}}\r\n";
    s += "\n";

    client.print(s);
    delay(1);
    Serial.println("Client Disconnected");
}